/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:24:51 by sameye            #+#    #+#             */
/*   Updated: 2022/02/04 15:13:08 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <math.h>
#include <vector>
#include <cstdlib>
//#include <unistd.h>

#include "pico_explorer.hpp"
#include "font8_data.hpp"
//#include "hardware/gpio.h"
//#include "hardware/pwm.h"


#include "pico/stdlib.h"
//#include "hardware/pio.h"
//#include "hardware/clocks.h"
//#include "blink.pio.h"
#include "serial_print.hpp"
#include "Stepper.hpp"
#include "UserInput.hpp"

using namespace pimoroni;

int main()
{

// init pico explorer
	uint16_t buffer[PicoExplorer::WIDTH * PicoExplorer::HEIGHT];
	PicoExplorer pico_explorer(buffer);
	pico_explorer.init();
	pico_explorer.set_font(&font8);
	pico_explorer.set_pen(0, 0, 0);
	pico_explorer.clear();
	pico_explorer.update();

// init serial
	serial_print_init();
	sleep_ms(1000);
	for (int k = 0; k < 100; k++)
		printf("$$$$$$$$$$$$$$$$$First print$$$$$$$$$$$$$$$$\n");

// test motor
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

// test user input
	UserInput userinput;
	float f;
	f = userinput.get_float(9.00, 0.01, "Coffee mass", "g", pico_explorer);
	std::cout << "entered mass : " << f << std::endl;

	f = userinput.get_float(10.00, 0.01, "Calib mass", "g", pico_explorer);
	std::cout << "entered mass : " << f << std::endl;;
}
