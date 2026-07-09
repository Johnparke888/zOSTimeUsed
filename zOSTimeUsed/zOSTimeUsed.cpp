#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

constexpr double TOD_INCREMENT = 1.048576;
constexpr std::size_t ascb_length = 0x0180;
constexpr std::size_t cct_length = 0x0190;
constexpr std::size_t csd_length = 0x0200;
constexpr std::size_t cvt_length = 0x0500;
constexpr std::size_t ecvt_length = 0x0438;
constexpr std::size_t pcca_length = 0x0248;
constexpr std::size_t pccavt_length = 0x0200;
constexpr std::size_t psa_length = 0x1000;
constexpr std::size_t rce_length = 0x0580;
constexpr std::size_t rmct_length = 0x0400;
constexpr std::size_t tcb_length = 0x0158;
constexpr std::size_t tct_length = 0x02d0;
constexpr std::size_t tctomvs_length = 0x0068;

#ifndef __MVS__
#define __ptr32
#endif
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
#include "tcb.h"
#include "tct.h"
#include "zosTimeUsed.h"


#if defined(__MVS__)
#include <unistd.h> /* __e2a_l() */
#endif


// Control block eye-catchers (acronyms) in EBCDIC. These are not necessarily at the start of the
// block, so we will check them at their documented offsets.

constexpr unsigned char ASCB_ACRONYM[4] = {0xC1, 0xE2, 0xC3, 0xC2};
constexpr unsigned char CCT_ACRONYM[4] = {0xC3, 0xC3, 0xE3, 0x40};
constexpr unsigned char CSD_ACRONYM[4] = {0xC3, 0xE2, 0xC4, 0x40};
constexpr unsigned char CVT_ACRONYM[4] = {0x40, 0xC3, 0xE5, 0xE3};
constexpr unsigned char ECVT_ACRONYM[4] = {0xC5, 0xC3, 0xE5, 0xE3};
constexpr unsigned char PCCA_ACRONYM[4] = {0xD7, 0xC3, 0xC3, 0xC1};
constexpr unsigned char RCE_ACRONYM[4] = {0xD9, 0xC3, 0xC5, 0x40};
constexpr unsigned char RMCT_ACRONYM[4] = {0xD9, 0xD4, 0xC3, 0xE3};
constexpr unsigned char TCB_ACRONYM[4] = {0xE3, 0xC3, 0xC2, 0x40};
constexpr unsigned char TCT_ACRONYM[4] = {0xE3, 0xC3, 0xE3, 0x40};
constexpr unsigned char TCT_OMVS_ACRONYM[4] = {0xE3, 0xC3, 0xE3, 0xD6};

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

   psa *__ptr32 psa_ptr = 0;                                               /* PSA is always at virtual address 0. */
   ascb *__ptr32 ascb_ptr = static_cast<ascb *__ptr32> (psa_ptr->psaaold); /* - Pointer to the home (current) ASCB.  @LQC */
   cvt *__ptr32 cvt_ptr = static_cast<cvt *__ptr32> (psa_ptr->flccvt);
   tcb *__ptr32 tcb_ptr = static_cast<tcb *__ptr32> (psa_ptr->psatold);
   tct *__ptr32 tct_ptr = reinterpret_cast<tct *__ptr32> (static_cast<std::uintptr_t> (tcb_ptr->tcbtct.tcbtctb));
   tctomvs *__ptr32 tctomvs_ptr = static_cast<tctomvs *__ptr32> (tct_ptr->tctomvsp);
   // If we're in testing mode, display the pointers we just read and the sizes of the blocks they point to, so we can verify that our offsets and
   // lengths match reality.

   if (areTesting)
   {
      auto display_pointer = [] (const char *name, const void *ptr) { std::cout << name << "=" << ptr << '\n'; };

      auto display_size = [] (const char *name, std::size_t actual, std::size_t expected)
      {
         std::cout << std::hex << "size of " << name << "=0x" << actual << " " << name << "_length=0x" << expected << " match=" << (actual == expected ? "yes" : "no") << std::dec
                   << '\n';
      };

      auto display_offset = [] (const char *field_name, const char *struct_name, std::size_t actual, std::size_t expected)
      {
         std::cout << std::hex << "offset of " << field_name << " in " << struct_name << "=0x" << actual << " expected=0x" << expected
                   << " match=" << (actual == expected ? "yes" : "no") << std::dec << '\n';
      };

      display_pointer ("psa_ptr", static_cast<void *> (psa_ptr));
      display_pointer ("ascb_ptr", static_cast<void *> (ascb_ptr));
      display_pointer ("cvt_ptr", static_cast<void *> (cvt_ptr));
      display_pointer ("tcb_ptr", static_cast<void *> (tcb_ptr));
      display_pointer ("tct_ptr", static_cast<void *> (tct_ptr));
      display_pointer ("tctomvs_ptr", static_cast<void *> (tctomvs_ptr));

      std::cout << '\n';


      display_size ("cvt", sizeof (cvt), cvt_length);
      display_size ("psa", sizeof (psa), psa_length);
      display_size ("ascb", sizeof (ascb), ascb_length);
      display_size ("tcb", sizeof (tcb), tcb_length);
      display_size ("tct", sizeof (tct), tct_length);
      display_size ("tctomvs", sizeof (tctomvs), tctomvs_length);
      std::cout << '\n';
      /*
       * 42 (2a) signed 2 ascbdph(0) - halfword dispatching priority
       * 80 (50) signed 4 ascbjstl - cpu time limit for the job step unsigned 32 bit binary number
       * 352 (160) dbl word 8 ascbiosx - i/o service measure extended. this is like ascbiosc but it is extended
       * to 8 bytes, so its value continues to grow past the 4gb ascbiosc maximum capacity.
       */
      display_offset ("cvtecvt", "cvt", offsetof (cvt, cvtecvt), 0x8c);
      display_offset ("ascbejst", "ascb", offsetof (ascb, ascbejst), 0x40);        // Elapsed Job Step Timing Unsigned 64 Bit Binary Number
      display_offset ("ascbsrbt", "ascb", offsetof (ascb, ascbsrbt), 0xc8);        // Accumulated Srb Time
      display_offset ("ascbasid", "ascb", offsetof (ascb, ascbasid), 0x24);        // Address Space Identifier For The Ascb
      display_offset ("ascbxcnt", "ascb", offsetof (ascb, ascbxcnt), 0x146);       // Excp Count Field.
      display_offset ("ascbjbni", "ascb", offsetof (ascb, ascbjbni), 0xac);        // Pointer To Jobname Field For Initiated Programs Or Zero
      display_offset ("ascbjbns", "ascb", offsetof (ascb, ascbjbns), 0xb0);        // - Pointer To Jobname Field For Start/Mount/Logon Or Zero
      display_offset ("ascbdph", "ascb", offsetof (ascb, ascbdphi), 0x2a);         // - Halfword Dispatching Priority
      display_offset ("ascbjstl", "ascb", offsetof (ascb, ascbjstl), 0x50);        // - CPU Time Limit For The Job Step Unsigned 32 Bit Binary Number
      display_offset ("ascbiosx", "ascb", offsetof (ascb, ascbiosx), 0x160);       // - I/O Service Measure Extended

      display_offset ("tctiotbl", "tct", offsetof (tct, tctiotbl), 0x0c);        // - address of the tct i/o table.
      display_offset ("tctsze", "tct", offsetof (tct, tctsze), 0x12);            // - size in bytes of the tct and the tct storage table
      display_offset ("tctajs", "tct", offsetof (tct, tctajs), 0x40);            // - accumulated session service time
      display_offset ("tctsrbs", "tct", offsetof (tct, tctsrbs), 0x50);          // - accum session srb service (os/vs2)
      display_offset ("tctejst", "tct", offsetof (tct, tctejst), 0x6c);          // - last value of elapsed tcb time
      display_offset ("tctsname", "tct", offsetof (tct, tctsname), 0xc8);        // - step name of current step
      display_offset ("tcttct", "tct", offsetof (tct, tcttct), 0xd0);            // - tct identifier field
      display_offset ("tcttpexx", "tct", offsetof (tct, tcttpexx), 0x2a8);       // - Last Value of 64-bit EXCP Count for TP

      display_offset ("tctopi", "tctomvs", offsetof (tctomvs, tctopi), 0x08);       // - Process ID
      display_offset ("tctosc", "tctomvs", offsetof (tctomvs, tctosc), 0x1c);       // - Number of syscals requested
      display_offset ("tctofr", "tctomvs", offsetof (tctomvs, tctofr), 0x28);       // - Number of I/O blocks read for standard files
      display_offset ("tctofw", "tctomvs", offsetof (tctomvs, tctofw), 0x2c);       // - Number of I/O blocks written for standard files
      display_offset ("tctokr", "tctomvs", offsetof (tctomvs, tctokr), 0x54);       // - Number of I/O blocks read for Remote socket by the process
      display_offset ("tctosy", "tctomvs", offsetof (tctomvs, tctosy), 0x64);       // - Number of sync() function calls

      std::cout << std::endl;
   }

   // At this point we have pointers to all the main control blocks we want to read.
   // We will validate that they look plausible before we trust them.
   // Validate that the pointers we just read from the CVT look plausible (non-null and point to blocks with the
   // expected eye-catchers).

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

   // Helper to validate that a pointer is non-null and that the block it points to starts with the expected eye-catcher
   // bytes.
   auto validate_eyecatcher =
       [&message, &error_message, areTesting] (
           const void *ptr, const unsigned char *actual, const unsigned char *expected, std::size_t length, const char *block_name, const char *pointer_name) -> bool
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
    * sanity check the CVT acronym. The first 4 bytes of the
    * input_field cvtcvt should be the EBCDIC characters ' ','C','V','T'
    *
    */
   if (!validate_eyecatcher (cvt_ptr, cvt_ptr->cvtcvt, CVT_ACRONYM, 4, "CVT ", "FLCCVT"))
   {
      return -1;
   }

   /*
    * sanity check the ASCB acronym. The first 4 bytes of the DSECT
    */
   if (!validate_eyecatcher (ascb_ptr, ascb_ptr->ascbascb, ASCB_ACRONYM, 4, "ASCB", "psaaold"))
   {
      return -1;
   }
   /*
    * sanity check the TCB acronym. At offset 256 (dec.)
    */
   if (!validate_eyecatcher (tcb_ptr, tcb_ptr->tcbtcbid, TCB_ACRONYM, 4, "TCB ", "psatold"))
   {
      return -1;
   }
   /*
    * sanity check the TCT acronym. Offset: 208 ('D0' in hex)
    */
   if (!validate_eyecatcher (tct_ptr, tct_ptr->tcttct, TCT_ACRONYM, 4, "TCT ", "tcttct"))
   {
      return -1;
   }
   if (!validate_eyecatcher (tctomvs_ptr, tctomvs_ptr->tctoid, TCT_OMVS_ACRONYM, 4, "TCTO", "tctoid"))
   {
      return -1;
   }
   const unsigned char *__ptr32 job_name_ptr = nullptr;

   if (ascb_ptr->ascbjbni != nullptr)
   {
      job_name_ptr = static_cast<const unsigned char *__ptr32> (ascb_ptr->ascbjbni);
   }
   else if (ascb_ptr->ascbjbns != nullptr)
   {
      job_name_ptr = static_cast<const unsigned char *__ptr32> (ascb_ptr->ascbjbns);
   }

   if (job_name_ptr != nullptr)
   {
      ebcdic_field_to_ascii (static_cast<const unsigned char *> (job_name_ptr), 8, zos_time_used.job_name);
   }
   else
   {
      zos_time_used.job_name = "UNKNOWN";
   }
   zos_time_used.asid = ascb_ptr->ascbasid;
   zos_time_used.execp_count = ascb_ptr->ascbxcnt;
   /*
    * â¢ Bit 51 represents 1 microsecond.
    * â¢ Bit 31 represents 1.048576 seconds.
    * â¢ Bit 0 increments every 0.000000000232 seconds (approx. 256 picoseconds).
    */
   constexpr double ZOS_TIME_UNITS_PER_SECOND = 4096.0 * 1000000.0;

   zos_time_used.cpu_time_used = static_cast<double> (ascb_ptr->ascbejst) / ZOS_TIME_UNITS_PER_SECOND;
   zos_time_used.srb_time_used = static_cast<double> (ascb_ptr->ascbsrbt) / ZOS_TIME_UNITS_PER_SECOND;

   zos_time_used.cpu_time_limit = (double) ascb_ptr->ascbjstl * TOD_INCREMENT;
   zos_time_used.dispatching_priority = (int) ascb_ptr->ascbdp;
   zos_time_used.io_service_measure = ascb_ptr->ascbiosx;

   return 0;
}
