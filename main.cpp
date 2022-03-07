/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:24:51 by sameye            #+#    #+#             */
/*   Updated: 2022/03/06 23:12:02 by sameye           ###   ########.fr       */
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


	
	//SET SPEED ACCORDING TO MASS
	stepper.set_accell(500);
	while (1)
	{
		stepper.set_speed(balance.get_mass() * 20);
		balance.print_balance_data();
		if (interface.button_clicked())
			break;
	}
	

	//grinder.print_averaged_mass(1);

/*
	stepper.set_accell(500);
	stepper.set_speed(4000); // debourage
	stepper.set_speed(0);
*/
/*
	stepper.set_accell(500);
	stepper.set_speed(9999);
	sleep_ms(2000);
	stepper.set_accell(6000);
	stepper.set_speed(-2000);
	stepper.set_speed(-0);
	stepper.set_speed(2000);
	stepper.set_speed(-0);
	stepper.set_speed(-2000);
	stepper.set_speed(-0);
	stepper.set_speed(2000);
	sleep_ms(2000);
	stepper.set_accell(70);
	stepper.set_speed(2500);
	stepper.set_accell(20000);
	stepper.set_speed(-2500);
	sleep_ms(2000);
	stepper.set_speed(-0);
*/

/*
	stepper.set_accell(3000);
	stepper.set_speed(-1000); // debourage
	stepper.set_speed(0);
	stepper.set_speed(-1000); // debourage
	stepper.set_speed(0);
	stepper.set_speed(-1000); // debourage
	stepper.set_speed(0);
	stepper.set_speed(-1000); // debourage
	stepper.set_speed(0);
*/



/*
	//loop
	//MAIN
	std::stringstream mass_str_stream;
	std::string mass_str;
	while (1)
	{
		switch (interface.show_menu("Grind", "Set mass", "Calibrate", "Show data", grinder.get_coffee_mass_g()))
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
				grinder.show_data();
				break;
		}
	}
	
	sleep_ms(2000);
	std::cout << "****************************" << std::endl;
	std::cout << "*       Pico returned      *" << std::endl;
	std::cout << "****************************" << std::endl;
*/
}
