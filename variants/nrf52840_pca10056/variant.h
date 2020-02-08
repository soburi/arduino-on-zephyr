/*
  Copyright (c) 2020 Tokita, Hiroshi  All right reserved.

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

#ifndef _VARIANT_NRF52840_PCA10056_
#define _VARIANT_NRF52840_PCA10056_

#include "wiring_private.h"

#ifdef CONFIG_ADC_NRFX_SAADC
#include <nrfx_saadc.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

/*
 * Analog pins
 */
#if   defined(CONFIG_ADC_NRFX_SAADC)
#define PIN_A0 (NRF_SAADC_INPUT_AIN0)
#define PIN_A1 (NRF_SAADC_INPUT_AIN1)
#define PIN_A2 (NRF_SAADC_INPUT_AIN2)
#define PIN_A3 (NRF_SAADC_INPUT_AIN3)
#define PIN_A4 (NRF_SAADC_INPUT_AIN4)
#define PIN_A5 (NRF_SAADC_INPUT_AIN5)
#define PIN_A6 (NRF_SAADC_INPUT_AIN6)
#define PIN_A7 (NRF_SAADC_INPUT_AIN7)
#define PIN_V8 (NRF_SAADC_INPUT_VDD)
#elif defined(CONFIG_ADC_NRFX_ADC_CHANNEL_COUNT)
//TODO
#endif

#ifdef __cplusplus
}
#endif

#endif /* _VARIANT_NRF52840_PCA10056_ */

