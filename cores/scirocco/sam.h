#pragma once

typedef int EPioType;

#if !defined(CONFIG_NEWLIB_LIBC)
    extern int isnan(double x);
    extern int isinf(double x);
#endif
