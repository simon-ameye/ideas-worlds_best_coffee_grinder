/* **************************************************************** */
/*                                           ____    ______         */
/*   Stepper                                /\###\  /#:+_+:\        */
/*                                          \ \##+\/:+:/_\ :\       */
/*                                           \ \#:+:+:+: : . \      */
/*   By: Simon Ameye                          \ \:+:___: .    \     */
/*                                             \ \ :\_/.  /\   \    */
/*                                              \ \______/\ \___\   */
/*   Please star my Github !                     \/_____/  \/___/   */
/*   https://github.com/simon-ameye/                                */
/* **************************************************************** */

#include "Grinder.hpp"

Grinder::Grinder(Stepper *stepper, UserInterface *interface, Balance *balance)
{
	this->_stepper = stepper;
	this->_interface = interface;
	this->_balance = balance;
	this->_coffee_mass_g = DEFAULT_COFFEE_MASS_G;
}

void Grinder::set_coffee_mass_g(void)
{
	float mass_g;
	mass_g = this->_interface->get_float(9.0, 0.01, "Coffee mass", "g");
	if (mass_g <= 0 || mass_g >= 100)
		mass_g = 7.00;
	this->_coffee_mass_g = mass_g;
}

float Grinder::get_coffee_mass_g(void)
{
	return (this->_coffee_mass_g);
}

void Grinder::grind(void)
{
	Stepper *stepper = this->_stepper;
	//reset balance
	stepper->set_speed(-500); // debourage
	stepper->set_accell(100);
	stepper->set_speed(200);
	sleep_ms(2000);
	stepper->set_accell(500);
	//wait first mass reach point
	stepper->set_speed(-500); // debourage
	stepper->set_speed(0);
	//precise measurement
	stepper->set_speed(70);
	sleep_ms(1000);
	stepper->set_speed(0);
	sleep_ms(1000);
	stepper->set_speed(70);
	sleep_ms(1000);
	stepper->set_speed(0);
	//play finish music
}

void Grinder::calibrate(void)
{
	this->_interface->show_message_validate("Please place mass 1 on the balance and set mass 1 value");
	float xm1 = this->_interface->get_float(10.0, 0.01, "Mass 1", "g");
	float ym1 = this->_balance->get_sig();
	this->_interface->show_message_validate("Please place mass 2 on the balance and set mass 2 value");
	float xm2 = this->_interface->get_float(10.0, 0.01, "Mass 2", "g");
	float ym2 = this->_balance->get_sig();
	float sensitivity = (ym2 - ym1) / (xm2 - xm1);
	float offcet = ym1 - sensitivity * xm1;
	this->_balance->set_calibration(offcet, sensitivity);
}