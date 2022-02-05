/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:24:51 by sameye            #+#    #+#             */
/*   Updated: 2022/02/05 10:23:46 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <math.h>
#include <vector>
#include <cstdlib>
//#include <unistd.h>

//#include "pico_explorer.hpp"
//#include "hardware/gpio.h"
//#include "hardware/pwm.h"


#include "pico/stdlib.h"
//#include "hardware/pio.h"
//#include "hardware/clocks.h"
//#include "blink.pio.h"
#include "serial_print.hpp"
#include "Stepper.hpp"
#include "UserInterface.hpp"
#include "Grinder.hpp"

using namespace pimoroni;

int main()
{

// init pico explorer
/*
	uint16_t buffer[PicoExplorer::WIDTH * PicoExplorer::HEIGHT];
	PicoExplorer pico_explorer(buffer);
	pico_explorer.init();
	pico_explorer.set_font(&font8);
	pico_explorer.set_pen(0, 0, 0);
	pico_explorer.clear();
	pico_explorer.update();
*/

// init serial

	serial_print_init();
	sleep_ms(1000);
	for (int k = 0; k < 100; k++)
		printf("$$$$$$$$$$$$$$$$$First print$$$$$$$$$$$$$$$$\n");


// test motor
/*
	Stepper motor(0, 25, 13);
	printf("$$$$$$$$$$$$$$Sepper created\n");
*/

/*
	motor.set_speed(500);
	printf("$$$$$$$$$$$$$$Speed set\n");
	//motor.print_status();
	sleep_ms(1000);

*/
/*
	motor.set_speed(-200);
	printf("$$$$$$$$$$$$$$Speed set\n");
	//motor.print_status();
	sleep_ms(1000);

	motor.set_accell(1000);
	printf("$$$$$$$$$$$$$$Speed set\n");
	//motor.print_status();
	sleep_ms(1000);

	motor.set_speed(2000);
	printf("$$$$$$$$$$$$$$Speed set\n");
	//motor.print_status();
	sleep_ms(1000);

	motor.set_speed(0);
	printf("$$$$$$$$$$$$$$Speed set\n");
	//motor.print_status();
	sleep_ms(1000);

	motor.set_speed(-200);
	printf("$$$$$$$$$$$$$$Speed set\n");
	//motor.print_status();
	sleep_ms(1000);

	motor.set_speed(-20);
	motor.set_accell(10);
	motor.set_speed(20);
	motor.set_speed(-20);
	motor.set_speed(20);
	motor.set_speed(0);
*/
/*
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
	*/

// test user input








/*
	UserInterface interface;
	//userinput.init_explorer(pico_explorer);
	float f;
	f = interface.get_float(9.00, 0.01, "Coffee mass", "g");
	std::cout << "entered mass : " << f << std::endl;

	f = interface.get_float(10.00, 0.01, "Calib mass", "g");
	std::cout << "entered mass : " << f << std::endl;;
*/


	//first try
	UserInterface	interface;
	Stepper			stepper(0, 25, 13);
	Grinder			grinder(&stepper, &interface);

	std::stringstream mass_str_stream;
	std::string mass_str;
	while (1)
	{
		mass_str_stream << std::fixed << std::setprecision(2) << grinder.get_coffee_mass_g() << "g";
		mass_str = mass_str_stream.str();
		switch (interface.show_menu("Grind " + mass_str, "Set mass", "Calibrate", "Bonus"))
		{
			case 'A':
				grinder.grind();
				break;
			case 'B':
				grinder.set_coffee_mass_g();
				break;
			case 'X':
				interface.get_float(10.0, 0.01, "Mass 1", "g");
				interface.get_float(10.0, 0.01, "Mass 2", "g");
				//balance.calibrate();
				break;
			case 'Y':
				break;

		}
	}
	
	

}
