/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:24:51 by sameye            #+#    #+#             */
/*   Updated: 2022/02/05 23:15:12 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//libs
#include <string.h>
#include <math.h>
#include <vector>
#include <cstdlib>
#include "pico/stdlib.h"

//custom classes
#include "serial_print.hpp"
#include "Stepper.hpp"
#include "UserInterface.hpp"
#include "Grinder.hpp"
#include "Balance.hpp"

int main()
{
	// init serial
	serial_print_init();
	sleep_ms(1000);
	for (int k = 0; k < 100; k++)
		printf("$$$$$$$$$$$$$$$$$First print$$$$$$$$$$$$$$$$\n");

	//init instances
	UserInterface	interface;
	Balance			balance;
	Stepper			stepper(0, 25, 13);
	Grinder			grinder(&stepper, &interface, &balance);

	//loop
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
				grinder.calibrate();
				break;
			case 'Y':
				break;
		}
	}
}
