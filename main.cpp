/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:24:51 by sameye            #+#    #+#             */
/*   Updated: 2022/02/27 21:13:47 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//libs
//#include <string.h>
//#include <math.h>
//#include <vector>
//#include <cstdlib>
//#include "pico/stdlib.h"

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
	sleep_ms(2000);
	std::cout << "****************************" << std::endl;
	std::cout << "*       Pico startup       *" << std::endl;
	std::cout << "****************************" << std::endl;

	//init instances
	std::cout << "main : initializing instances" << std::endl;
	UserInterface	interface;
	Balance			balance;
	Stepper			stepper;
	Grinder			grinder(&stepper, &interface, &balance);

	//loop
	std::stringstream mass_str_stream;
	std::string mass_str;
	while (1)
	{
		switch (interface.show_menu("Grind", "Set mass", "Calibrate", "Bonus", grinder.get_coffee_mass_g()))
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
	sleep_ms(2000);
	std::cout << "****************************" << std::endl;
	std::cout << "*       Pico returned      *" << std::endl;
	std::cout << "****************************" << std::endl;
}
