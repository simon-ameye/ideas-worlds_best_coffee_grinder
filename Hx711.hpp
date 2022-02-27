/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hx711.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:08:29 by sameye            #+#    #+#             */
/*   Updated: 2022/02/27 20:54:39 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HX711_HPP
#define HX711_HPP

#include <hardware/gpio.h>
#include <hardware/adc.h>
#include "pico/stdlib.h"

#define PD_SCK_GPIO 1 //GPIO pin for clock
#define DOUT_GPIO 2 //GPIO pin for data reading
#define GAIN 128
#define T1 1
#define T2 0.1 // not used
#define T3 1
#define T4 1

//Simon Ameye adapted driver for PICO from reference driver available at https://cdn.sparkfun.com/datasheets/Sensors/ForceFlex/hx711_english.pdf

//T1 DOUT falling edge to PD_SCK rising edge min 0.1 µs
//T2 PD_SCK rising edge to DOUT data ready max 0.1 µs
//T3 PD_SCK high time min 0.2, typ 1, max 50 µs
//T4 PD_SCK low time min 0.2 typ 1 µs

//25 clock pulses - select A channel with GAIN = 128 // default
//26 clock pulses - select B channel with GAIN = 32 //Do not use
//27 clock pulses - select A channel with GAIN = 64 //Maybe

class Hx711
{
	public:
	Hx711(void);
	unsigned long ReadCound(void);
};

#endif