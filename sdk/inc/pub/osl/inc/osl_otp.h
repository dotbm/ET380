#pragma once
#include "pub/pub.h"

LIB_EXPORT int osl_otp_write(unsigned char *rbuf, unsigned int addr, int size);
LIB_EXPORT int osl_otp_read(unsigned char *rbuf, unsigned int addr, int size);
LIB_EXPORT int osl_otp_valid();
LIB_EXPORT void osl_otp_creat();
LIB_EXPORT void osl_otp_init(int addr);