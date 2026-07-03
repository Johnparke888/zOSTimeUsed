/*
 * zosTimeUsed.cpp
 *
 * Retrieve information from z/OS control blocks pertaining to product and sysplex information.
 *
 *     PSA (addr 0) -> FLCCVT at offset x'10' -> CVT
 *
 *
 * Notes:
 *   - The PSA, CVT, and ECVT all live in 31-bit storage. In a 64-bit
 *     (LP64) program, ordinary pointers are 64-bit, so we MUST use
 *     __ptr32 to declare pointers to / inside these blocks. Without
 *     __ptr32 the compiler would sign-extend the 31-bit value or
 *     read 8 bytes instead of 4 and you would chase garbage.
 *
 *   - String fields in these blocks are EBCDIC. We convert any input_field
 *     we want to display with __e2a_l() (a no-op on EBCDIC builds;
 *     a real conversion on ASCII builds).
 */

#include "psa.h"
#include "cvt.h"
#include "ecvt.h"
#include "cct.h"
#include "rmct.h"
#include "pcca.h"
#include "pccavt.h"
#include "rce.h"
#include "csd.h"
#include "ascb.h"
#include "zosTimeUsed.h"

#include <cstdio>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

#if defined(__MVS__)
#include <unistd.h> /* __e2a_l() */
#endif

#define cct_length 0x0190
#define csd_length 0x0200
#define cvt_length 0x0500
#define ecvt_length 0x0438
#define pcca_length 0x0248
#define pccavt_length 0x0200
#define psa_length 0x1000
#define rce_length 0x0580
#define rmct_length 0x0400
#define ascb_length 0x0180
// Control block eye-catchers (acronyms) in EBCDIC. These are not necessarily at the start of the
// block, so we will check them at their documented offsets.

static const unsigned char CVT_ACRONYM[4] = {0x40, 0xC3, 0xE5, 0xE3};
static const unsigned char ECVT_ACRONYM[4] = {0xC5, 0xC3, 0xE5, 0xE3};
static const unsigned char RMCT_ACRONYM[4] = {0xD9, 0xD4, 0xC3, 0xE3};
static const unsigned char CCT_ACRONYM[4] = {0xC3, 0xC3, 0xE3, 0x40};
static const unsigned char PCCA_ACRONYM[4] = {0xD7, 0xC3, 0xC3, 0xC1};
static const unsigned char RCE_ACRONYM[4] = {0xD9, 0xC3, 0xC5, 0x40};
static const unsigned char CSD_ACRONYM[4] = {0xC3, 0xE2, 0xC4, 0x40};
static const unsigned char ASCB_ACRONYM[4] = {0xC1, 0xE2, 0xC3, 0xC2};
/*
 *  Helper: copy a fixed-length EBCDIC input_field into a NUL-terminated
 *  buffer, convert to ASCII for display, and trim trailing blanks.
 *  "input_field" need not be NUL-terminated; "field_length" is its declared length.
 *
 */

void ebcdic_field_to_ascii (const unsigned char *input_field, std::size_t field_length, char *output_buffer, std::size_t output_buffer_size)
{

   if (output_buffer_size == 0)
   {
      return;
   }

   std::size_t bytes_to_copy = (field_length < output_buffer_size - 1) ? field_length : output_buffer_size - 1;
   std::memcpy (output_buffer, input_field, bytes_to_copy);
   output_buffer[bytes_to_copy] = '\0';

#if defined(__MVS__)
   /* Convert in place from EBCDIC (IBM-1047) to ASCII (ISO8859-1).
    * If the source file is compiled in EBCDIC mode, __e2a_l is still
    * safe to call; the result for a pure-EBCDIC build will look
    * unchanged because stdio is also EBCDIC. */

   __e2a_l (output_buffer, bytes_to_copy);
#endif

   /* Trim trailing blanks (and the now-EBCDIC-or-ASCII space byte). */
   while (bytes_to_copy > 0 && (output_buffer[bytes_to_copy - 1] == ' ' || output_buffer[bytes_to_copy - 1] == '\0'))
   {
      output_buffer[--bytes_to_copy] = '\0';
   }
}


void ebcdic_field_to_ascii (const unsigned char *input_field, std::size_t field_length, std::string &output)
{
   // Copy the raw EBCDIC bytes into the string (length-based, no null-termination assumption).
   output.assign (reinterpret_cast<const char *> (input_field), field_length);

#if defined(__MVS__)
   // Convert in place IBM-1047 -> ISO8859-1. Operates on the string's buffer.
   if (!output.empty ())
   {
      __e2a_l (&output[0], output.size ());
   }
#endif

   // Trim trailing ASCII blanks (0x20). In ASCII-mode compilation ' ' == 0x20,
   // which matches the post-conversion padding bytes.

   std::size_t trimmed_length = output.size ();

   while (trimmed_length > 0 && output[trimmed_length - 1] == ' ')
   {
      --trimmed_length;
   }

   output.resize (trimmed_length);
}


int get_zos_time_used (zOS_TimeUsed &zos_time_used, std::string &error_message, bool areTesting)
{

   /*
    * Step 1: get the CVT pointer from PSA.flccvt.
    * PSA - Prefixed Save Area
    *
    */
   std::ostringstream message;

   error_message.clear ();

   psa *__ptr32 psa_ptr = 0;                  /* PSA is always at virtual address 0. */
   ascb *__ptr32 ascb_ptr = psa_ptr->psaaold; /* - Pointer to the home (current) ASCB.  @LQC */
   cvt *__ptr32 cvt_ptr = static_cast<cvt *__ptr32> (psa_ptr->flccvt);


   // If we're in testing mode, display the pointers we just read and the sizes of the blocks they point to, so we can verify that our offsets and
   // lengths match reality.

   if (areTesting)
   {
      auto display_pointer = [] (const char *name, const void *ptr) { std::cout << name << "=" << ptr << '\n'; };

      auto display_size = [] (const char *name, std::size_t actual, std::size_t expected)
      {
         std::cout << std::hex << "size of " << name << "=0x" << actual << " " << name << "_length=0x" << expected
                   << " match=" << (actual == expected ? "yes" : "no") << std::dec << '\n';
      };

      auto display_offset = [] (const char *field_name, const char *struct_name, std::size_t actual, std::size_t expected)
      {
         std::cout << std::hex << "offset of " << field_name << " in " << struct_name << "=0x" << actual << " expected=0x" << expected
                   << " match=" << (actual == expected ? "yes" : "no") << std::dec << '\n';
      };

      display_pointer ("psa_ptr", static_cast<void *> (psa_ptr));
      display_pointer ("ascb_ptr", static_cast<void *> (ascb_ptr));
      display_pointer ("cvt_ptr", static_cast<void *> (cvt_ptr));
      std::cout << '\n';


      display_size ("cvt", sizeof (cvt), cvt_length);
      display_size ("psa", sizeof (psa), psa_length);
      display_size ("ascb", sizeof (ascb), ascb_length);

      std::cout << '\n';

      display_offset ("cvtecvt", "cvt", offsetof (cvt, cvtecvt), 0x8c);
      display_offset ("ascbejst", "ascb", offsetof (ascb, ascbejst), 0x40);        // Elapsed Job Step Timing Unsigned 64 Bit Binary Number
      display_offset ("ascbsrbt", "ascb", offsetof (ascb, ascbsrbt), 0xc8);        // Accumulated Srb Time
      display_offset ("ascbasid", "ascb", offsetof (ascb, ascbasid), 0x24);        // Address Space Identifier For The Ascb
      display_offset ("ascbxcnt", "ascb", offsetof (ascb, ascbxcnt), 0x146);       // Excp Count Field.
      display_offset ("ascbjbni", "ascb", offsetof (ascb, ascbjbni), 0xac);        // Pointer To Jobname Field For Initiated Programs Or Zero
      display_offset ("ascbjbns", "ascb", offsetof (ascb, ascbjbns), 0xb0);        // - Pointer To Jobname Field For Start/Mount/Logon Or Zero
      std::cout << std::endl;
   }

   // At this point we have pointers to all the main control blocks we want to read.
   // We will validate that they look plausible before we trust them.
   // Validate that the pointers we just read from the CVT look plausible (non-null and point to blocks with the expected eye-catchers).

   auto validate_pointer = [&message, &error_message] (const void *ptr, const char *block_name, const char *pointer_name) -> bool
   {
      if (ptr == nullptr)
      {
         message.str ("");
         message.clear ();

         message << pointer_name << " is zero - cannot locate " << block_name << ".";

         error_message = message.str ();
         return false;
      }

      return true;
   };

   // Helper to validate that a pointer is non-null and that the block it points to starts with the expected eye-catcher bytes.
   auto validate_eyecatcher = [&message, &error_message, areTesting] (const void *ptr,
                                                                      const unsigned char *actual,
                                                                      const unsigned char *expected,
                                                                      std::size_t length,
                                                                      const char *block_name,
                                                                      const char *pointer_name) -> bool
   {
      if (ptr == nullptr)
      {
         message.str ("");
         message.clear ();

         message << pointer_name << " is zero - cannot locate " << block_name << ".";

         error_message = message.str ();
         return false;
      }

      if (std::memcmp (actual, expected, length) != 0)
      {
         message.str ("");
         message.clear ();

         message << block_name << " acronym mismatch at " << ptr << " - got ";

         for (std::size_t i = 0; i < length; ++i)
         {
            if (i != 0)
            {
               message << ' ';
            }

            message << std::hex << static_cast<int> (actual[i]);
         }

         error_message = message.str ();

         if (areTesting)
         {
            std::cout << error_message << std::endl;
         }

         return false;
      }

      return true;
   };

   /////////////////////////////////////////////////////////////////


   /*
    * Step 2: sanity check the CVT acronym. The first 4 bytes of the
    * input_field cvtcvt should be the EBCDIC characters ' ','C','V','T'
    *
    */
   if (!validate_eyecatcher (cvt_ptr, cvt_ptr->cvtcvt, CVT_ACRONYM, 4, "CVT", "FLCCVT"))
   {
      return -1;
   }

   /*
    * Step 3: sanity check the ECVT acronym. The first 4 bytes of the dsect
    */
   if (!validate_eyecatcher (ascb_ptr, ascb_ptr->ascbascb, ASCB_ACRONYM, 4, "ASCB", "psaaold"))
   {
      return -1;
   }

   if (ascb.ascbjbni != 0)
   {
      ebcdic_field_to_ascii (ascb.ascbjbni, 8, zos_time_used.job_name);
   }
   else if (ascb.ascbjbns != 0)
   {
      ebcdic_field_to_ascii (ascb.ascbjbns, 8, zos_time_used.job_name);
   }
   else
   {
      zos_time_used.job_name = "UNKNOWN";
   }
   zos_time_used.asid = ascb.ascbasid;
   zos_time_used.execp_count = ascb.ascbxcnt;
   /*
    * • Bit 51 represents 1 microsecond.
    * • Bit 31 represents 1.048576 seconds.
    * • Bit 0 increments every 0.000000000232 seconds (approx. 256 picoseconds).
    */
   double elapsed_time = static_cast<double> (((ascb.ascbejst) / 4096) / 1000000.0);       // Convert from microseconds to seconds
   double srb_time = static_cast<double> (((ascb.ascbsrbt) / 4096) / 1000000.0);           // Convert from microseconds to seconds
   return 0;
}
