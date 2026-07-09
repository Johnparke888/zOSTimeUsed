#pragma once
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip> // Required for std::setprecision

extern void ebcdic_field_to_ascii (const unsigned char *input_field, std::size_t field_length, std::string &output);
extern void ebcdic_field_to_ascii (const unsigned char *input_field, std::size_t field_length, char *output_buffer, std::size_t output_buffer_size);

struct zOS_TimeUsed
{
   zOS_TimeUsed ()
   {
   }

   public:
   int asid = 0;
   int execp_count = 0;
   int cpu_time_limit = 0;
   int dispatching_priority = 0;
   unsigned long long io_service_measure = 0;
   double cpu_time_used = 0.0;
   double srb_time_used = 0.0;
   std::string job_name;

   public:
   std::string toString () const
   {
      std::ostringstream oss;
      oss << "ASID: " << asid << " ";
      oss << "Execp Count: " << execp_count << " ";
      oss << "CPU Time Used (seconds): " << std::fixed << std::setprecision (2) << cpu_time_used << " ";
      oss << "SRB Time Used (seconds): " << std::fixed << std::setprecision (2) << srb_time_used << " ";
      oss << "Dispatching Priority: " << dispatching_priority << " ";
      oss << "I/O Service Measure: " << io_service_measure << " ";
      oss << "CPU Time Limit (seconds): " << cpu_time_limit << " ";
      oss << "Job Name: " << job_name;
      return oss.str ();
   }
};

int get_zos_time_used (zOS_TimeUsed &zos_time_used, std::string &error_message, bool testing = false);
