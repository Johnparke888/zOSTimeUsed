/*

 */
#ifndef __MVS__
#define __ptr32
#endif

#include <cstdio>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include "zosTimeUsed.h"

#if defined(__MVS__)
#include <unistd.h> /* __e2a_l() */
#endif

int main ()
{
   zOS_TimeUsed zos_time_used;
   std::string error_message;
   bool areTesting = true;
   int result = get_zos_time_used (zos_time_used, error_message, areTesting);
   if (result != 0)
   {
      std::cerr << "Error retrieving z/OS information: " << error_message << std::endl;
      return 1;
   }
   std::cout << zos_time_used.toString() << std::endl;

   return 0;
}
