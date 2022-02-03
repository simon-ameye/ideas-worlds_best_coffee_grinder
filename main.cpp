/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:24:51 by sameye            #+#    #+#             */
/*   Updated: 2022/02/03 23:35:47 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <math.h>
#include <vector>
#include <cstdlib>
//#include <unistd.h>

//#include "pico_explorer.hpp"
//#include "font8_data.hpp"
#include "serial_print.hpp"
//#include "hardware/gpio.h"
//#include "hardware/pwm.h"


#include "pico/stdlib.h"
//#include "hardware/pio.h"
//#include "hardware/clocks.h"
//#include "blink.pio.h"
#include "Stepper.hpp"

//using namespace pimoroni;

int main()
{

// init serial
	serial_print_init();
	sleep_ms(1000);
	for (int k = 0; k < 100; k++)
		printf("$$$$$$$$$$$$$$$$$First print$$$$$$$$$$$$$$$$\n");

// test audio

	Stepper motor(0, 25, 13);
	printf("$$$$$$$$$$$$$$Sepper created\n");
	motor.print_status();
	sleep_ms(1000);

	motor.set_speed(500);
	printf("$$$$$$$$$$$$$$Speed set\n");
	motor.print_status();
	sleep_ms(1000);

	motor.set_accell(200);
	printf("$$$$$$$$$$$$$$Accell set\n");
	motor.print_status();
	sleep_ms(1000);

	motor.set_speed(-200);
	printf("$$$$$$$$$$$$$$Speed set\n");
	motor.print_status();
	sleep_ms(1000);

	printf("$$$$$$$$$$$$$$Speed set\n");
	motor.set_speed(0);
	motor.print_status();
	sleep_ms(1000);

	printf("$$$$$$$$$$$$$$Speed set\n");
	motor.set_speed(20);
	motor.print_status();
	sleep_ms(1000);

	printf("$$$$$$$$$$$$$$Speed set\n");
	motor.set_speed(-20);
	motor.print_status();

	printf("$$$$$$$$$$$$$$Speed set\n");
	motor.set_accell(800);
	motor.print_status();
	printf("$$$$$$$$$$$$$$Speed set111111111111111\n");
	motor.set_speed(-5000);
	printf("$$$$$$$$$$$$$$Speed set222222222222\n");
	motor.set_accell(8000);
	printf("$$$$$$$$$$$$$$Speed set33333333333333\n");
	motor.set_speed(50000);
	printf("$$$$$$$$$$$$$$Speed set44444444444\n");
	motor.set_speed(-50000);
/*



	uint16_t buffer[PicoExplorer::WIDTH * PicoExplorer::HEIGHT];
	PicoExplorer pico_explorer(buffer);
	pico_explorer.init();
	//pico_explorer.set_font(&font8);
	uint32_t i = 0;
	while(true)
	{
		pico_explorer.set_pen(120, 40, 60);
		pico_explorer.clear();	
		pico_explorer.set_pen(255, 255, 255);
		pico_explorer.text("HHHHHHHEEEEEYYYYYY", Point(10, 10), 220);
		pico_explorer.update();
		printf("frame %d\n", i);
		i++;
	}
	return 0;
*/
}
