#pragma once
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

extern void ebcdic_field_to_ascii (const unsigned char *input_field, std::size_t field_length, std::string &output);
extern void ebcdic_field_to_ascii (const unsigned char *input_field, std::size_t field_length, char *output_buffer, std::size_t output_buffer_size);

struct zOS_TimeUsed
{
   zOS_TimeUsed ()
   {
   }

   public:
   int asid=0; 
   int execp_count=0;
   double cpu_time_used=0.0;
   double srb_time_used=0.0;
   std::string job_name;
 
   public:
   toString () const
   {
      std::ostringstream oss;
      oss << "ASID: " << asid << std::endl;
      oss << "Execp Count: " << execp_count << std::endl;
      oss << "CPU Time Used (seconds): " << cpu_time_used << std::endl;
      oss << "SRB Time Used (seconds): " << srb_time_used << std::endl;
      oss << "Job Name: " << job_name << std::endl;
      return oss.str ();
   }
};

int get_zos_time_used (zOS_TimeUsed &zos_time_used, std::string &error_message, bool testing = false);
