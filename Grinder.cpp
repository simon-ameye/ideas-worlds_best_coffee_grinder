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
	UserInterface *interface = this->_interface;
	Balance *balance = this->_balance;
	float coffee_mass_g = this->_coffee_mass_g;
	float initial_mass_g;

	this->_interface->show_message_pass("Please place container on balance");
	stepper->set_accell(100);
	stepper->set_speed(-500); // debourage
	stepper->set_speed(0);
	initial_mass_g = balance->get_mass();
	Grinder::grind_until(10, initial_mass_g + this->_coffee_mass_g - 1, 200, initial_mass_g); //brew coarsly and leave 1g
	stepper->set_accell(500);
	Grinder::grind_until(10, initial_mass_g + this->_coffee_mass_g, 100, initial_mass_g); //brew coarsly and leave 1g
	stepper->set_accell(500);
	float final_mass;
	while (!interface->button_clicked())
	{
		final_mass = balance->get_mass() - initial_mass_g;
		interface->print_coffee_mass(final_mass, "Grinded mass :");
	}
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

//Set max_time = 0 or max_mass = 0 to ignore
void	Grinder::grind_until(float duration_s, float mass_target_g, int speed_rpm, float initial_mass_g)
{
	clock_t time = 0.0;
	clock_t time_ref = clock();
	float mass = 0.0;
	this->_stepper->set_speed(speed_rpm);
	while (1)
	{
		if (duration_s && time >= duration_s)
			break;
		if (mass_target_g && mass >= mass_target_g)
			break;
		this->_interface->print_coffee_mass(mass - initial_mass_g, "Grinding...");
		time = (float)(clock() - time_ref) / CLOCKS_PER_SEC;
		mass = this->_balance->get_mass() - initial_mass_g;
	}
	this->_stepper->set_speed(0);
}
