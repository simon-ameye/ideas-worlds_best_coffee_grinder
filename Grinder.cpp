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
	std::cout << "grinder : consrtuctor call" << std::endl;
	this->_stepper = stepper;
	this->_interface = interface;
	this->_balance = balance;
	this->_coffee_mass_g = DEFAULT_COFFEE_MASS_G;
	std::cout << "grinder : consrtuctor return" << std::endl;
}

void Grinder::set_coffee_mass_g(void)
{
	std::cout << "grinder : set coffee mass call" << std::endl;
	float mass_g;
	mass_g = this->_interface->get_float(9.0, 0.01, "Coffee mass", "g");
	if (mass_g <= 0 || mass_g >= 100)
		mass_g = 7.00;
	this->_coffee_mass_g = mass_g;
	std::cout << "grinder : set coffee mass return" << std::endl;
}

float Grinder::get_coffee_mass_g(void)
{
	std::cout << "grinder : get coffee mass call" << std::endl;
	std::cout << "grinder : get coffee mass return" << std::endl;
	return (this->_coffee_mass_g);
}

void Grinder::grind(void)
{
	std::cout << "grinder : grind call" << std::endl;
	Stepper *stepper = this->_stepper;
	UserInterface *interface = this->_interface;
	Balance *balance = this->_balance;
	float coffee_mass_g = this->_coffee_mass_g;
	float initial_mass_g;

	this->_interface->show_message_validate("Please place container on balance");

	std::cout << "grinder : grind : debourage" << std::endl;
	stepper->set_accell(5000);
	stepper->set_speed(-500); // debourage
	stepper->set_speed(0);
	stepper->set_speed(-500); // debourage
	stepper->set_speed(0);
	stepper->set_speed(-500); // debourage
	stepper->set_speed(0);

	std::cout << "grinder : grind : init mass" << std::endl;
	initial_mass_g = balance->get_mass();

	std::cout << "grinder : grind : first grind" << std::endl;
	stepper->set_accell(300);
	Grinder::grind_until(10, initial_mass_g + this->_coffee_mass_g - 1, 200, initial_mass_g); //brew coarsly and leave 1g

	std::cout << "grinder : grind : second grind" << std::endl;
	stepper->set_accell(500);
	Grinder::grind_until(10, initial_mass_g + this->_coffee_mass_g, 100, initial_mass_g); //brew coarsly and leave 1g

	std::cout << "grinder : grind : show result" << std::endl;
	float final_mass;
	while (!interface->button_clicked())
	{
		final_mass = balance->get_mass() - initial_mass_g;
		interface->print_coffee_mass(final_mass, "Grinded mass :");
	}
	std::cout << "grinder : grind return" << std::endl;
}

void Grinder::calibrate(void)
{
	std::cout << "grinder : calibrate call" << std::endl;

	std::cout << "grinder : calibrate : show message" << std::endl;
	this->_interface->show_message_validate("Place mass 1 and set mass value");

	std::cout << "grinder : calibrate : get float" << std::endl;
	float xm1 = this->_interface->get_float(10.0, 0.01, "Mass 1", "g");

	std::cout << "grinder : calibrate : get sig" << std::endl;
	float ym1 = this->_balance->get_sig();

	std::cout << "grinder : calibrate : show message" << std::endl;
	this->_interface->show_message_validate("Place mass 2 and set mass value");

	std::cout << "grinder : calibrate : get float" << std::endl;
	float xm2 = this->_interface->get_float(10.0, 0.01, "Mass 2", "g");

	std::cout << "grinder : calibrate : get sig" << std::endl;
	float ym2 = this->_balance->get_sig();

	std::cout << "grinder : calibrate : calculate calibration" << std::endl;
	float sensitivity = (ym2 - ym1) / (xm2 - xm1);
	float offcet = ym1 - sensitivity * xm1;

	std::cout << "grinder : calibrate : set calibration" << std::endl;
	this->_balance->set_calibration(offcet, sensitivity);

	std::cout << "grinder : calibrate return" << std::endl;
}

//Set max_time = 0 or max_mass = 0 to ignore
void	Grinder::grind_until(float duration_s, float mass_target_g, int speed_rpm, float initial_mass_g)
{
	std::cout << "grinder : grind until call" << std::endl;
	clock_t time = 0.0;
	clock_t time_ref = clock();
	float mass = 0.0;
	float i = initial_mass_g; // to remove

	std::cout << "grinder : grind until : set speed" << std::endl;
	this->_stepper->set_speed(speed_rpm);

	std::cout << "grinder : grind until : loop" << std::endl;
	while (1)
	{
		if (duration_s && time >= duration_s)
			break;
		if (mass_target_g && mass >= mass_target_g)
			break;
		this->_interface->print_coffee_mass(mass - initial_mass_g, "Grinding...");
		time = (float)(clock() - time_ref) / CLOCKS_PER_SEC;
		mass = this->_balance->get_mass() - initial_mass_g;
		mass = i; // to remove
		i += 0.1; // to remove
	}
	this->_stepper->set_speed(0);

	std::cout << "grinder : grind until return" << std::endl;
}
