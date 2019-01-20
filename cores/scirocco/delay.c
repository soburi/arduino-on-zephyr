/*
  Copyright (c) 2015-2017 Tokita, Hiroshi  All right reserved.

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

#include "delay.h"
#include "Arduino.h"

#include <sys_clock.h>

unsigned long millis( void )
{
	return k_uptime_get();
}

unsigned long micros( void )
{
	return k_uptime_get() * 1000; //TODO
}

void delay( unsigned long ms )
{
	k_sleep(ms);
}

void _delayMicroseconds( unsigned int usec )
{
	k_busy_wait(usec);
}

