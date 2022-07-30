/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.
  Copyright (c) 2015-2019 Tokita, Hiroshi

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _DELAY_
#define _DELAY_

#include <stdint.h>
#include "variant.h"
#include <sys_clock.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Returns the number of milliseconds since the Arduino board began running the current program.
 *
 * This number will overflow (go back to zero), after approximately 50 days.
 *
 * \return Number of milliseconds since the program started (uint32_t)
 */
static inline unsigned long millis( void )
{
	return k_uptime_get();
}


/**
 * \brief Returns the number of microseconds since the Arduino board began running the current program.
 *
 * This number will overflow (go back to zero), after approximately 70 minutes. On 16 MHz Arduino boards
 * (e.g. Duemilanove and Nano), this function has a resolution of four microseconds (i.e. the value returned is
 * always a multiple of four). On 8 MHz Arduino boards (e.g. the LilyPad), this function has a resolution
 * of eight microseconds.
 *
 * \note There are 1,000 microseconds in a millisecond and 1,000,000 microseconds in a second.
 */
static inline unsigned long micros( void )
{
#if defined(CONFIG_TIMER_READS_ITS_FREQUENCY_AT_RUNTIME)
extern int z_clock_hw_cycles_per_sec;
#define HW_CYCLES_PER_SEC z_clock_hw_cycles_per_sec;
#else
#define HW_CYCLES_PER_SEC CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC
#endif
	return ( (uint32_t)( (uint64_t)k_cycle_get_32() * USEC_PER_SEC / HW_CYCLES_PER_SEC) );
}

/**
 * \brief Pauses the program for the amount of time (in miliseconds) specified as parameter.
 * (There are 1000 milliseconds in a second.)
 *
 * \param dwMs the number of milliseconds to pause (uint32_t)
 */
static inline void delay( unsigned long dwMs )
{
	k_msleep(dwMs);
}

/**
 * \brief Pauses the program for the amount of time (in microseconds) specified as parameter.
 *
 * \param dwUs the number of microseconds to pause (uint32_t)
 */
static inline void delayMicroseconds( unsigned int usec )
{
	k_busy_wait(usec);
}

#ifdef __cplusplus
}
#endif

#endif /* _DELAY_ */
