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

#include "Arduino.h"
#include "wiring_private.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <zephyr.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/drivers/pwm.h>

#ifdef CONFIG_ADC

void analogReference( eAnalogReference ulMode )
{
	struct adc_channel_cfg cfg;
	cfg.gain = ADC_GAIN_1; 
	cfg.reference = EXTERNAL ? ADC_REF_EXTERNAL0 : ADC_REF_INTERNAL;
	cfg.channel_id = 0;
	cfg.differential = 0;

	adc_channel_setup(NULL, &cfg);
}

uint32_t analogRead( uint32_t ulPin )
{
	struct adc_sequence seq;
	adc_read(NULL, &seq);
	return 0;
}

void _analogReadResolution(int res)
{
	struct adc_channel_cfg cfg;
	cfg.gain = ADC_GAIN_1; 
	cfg.reference = EXTERNAL ? ADC_REF_EXTERNAL0 : ADC_REF_INTERNAL;
	cfg.channel_id = 0;
	cfg.differential = 0;

	adc_channel_setup(NULL, &cfg);
}

#endif

#ifdef CONFIG_PWM

struct pwm_dev_pin {
	struct device* dev;
	uint32_t ch;
};
static struct pwm_dev_pin pwm_table[] = { LISTIFY(NUM_UART, GEN_PWM_CFG_N, (,)) };

static struct device* pwm_device(int pin)
{
	if(pin<ARRAY_SIZE(pwm_table)) {
		return pwm_table[pin].dev;
	}
	return NULL;
}

static int pwm_resolution = 255;

void analogWrite( uint32_t ulPin, uint32_t ulValue )
{
	if(!pwm_device(ulPin)) return;

	pwm_set_cycles(pwm_device(ulPin), pwm_table[ulPin].ch, pwm_resolution, ulValue);
}

void analogWriteResolution(int res)
{
	pwm_resolution = res;
}


#endif


#ifdef __cplusplus
}
#endif


