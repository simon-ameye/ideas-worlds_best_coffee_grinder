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

static void print_debug(std::string str)
{
	#ifdef PRINT_DEBUG
		std::cout<< "Grinder : " << str <<std::endl;
	#endif
}

Grinder::Grinder(Stepper *stepper, UserInterface *interface, Balance *balance)
{
	print_debug("consrtuctor call");
	this->_stepper = stepper;
	this->_interface = interface;
	this->_balance = balance;
	this->_coffee_mass_g = DEFAULT_COFFEE_MASS_G;
	print_debug("consrtuctor return");
}

void Grinder::set_coffee_mass_g(void)
{
	print_debug("set coffee mass call");
	float mass_g;
	mass_g = this->_interface->get_float(9.0, 0.01, "Coffee mass", "g");
	if (mass_g <= 0 || mass_g >= 100)
		mass_g = 7.00;
	this->_coffee_mass_g = mass_g;
	print_debug("set coffee mass return");
}

float Grinder::get_coffee_mass_g(void)
{
	print_debug("get coffee mass call");
	print_debug("get coffee mass return");
	return (this->_coffee_mass_g);
}

void Grinder::grind(void)
{
	print_debug("grind call");
	Stepper *stepper = this->_stepper;
	UserInterface *interface = this->_interface;
	Balance *balance = this->_balance;
	float coffee_mass_g = this->_coffee_mass_g;
	float initial_mass_g;

	this->_interface->show_message_validate("Please place container on balance");

	interface->print_coffee_mass(0, "Grinded mass :");
	stepper->set_accell(5000);
	stepper->set_speed(-50);
	sleep_ms(1000);
	stepper->set_speed(0);
	sleep_ms(1000);

	print_debug("grind : init mass");
	initial_mass_g = balance->get_mass();
	initial_mass_g = 0; //to remove

	print_debug("grind : debourage");
	stepper->set_accell(5000);
	stepper->set_speed(-500); // debourage
	stepper->set_speed(0);
	stepper->set_speed(-500); // debourage
	stepper->set_speed(0);
	stepper->set_speed(-500); // debourage
	stepper->set_speed(0);

	print_debug("grind : first grind");
	stepper->set_accell(300);
	Grinder::grind_until(4, initial_mass_g + this->_coffee_mass_g - 1, 500, initial_mass_g); //brew coarsly and leave 1g

	print_debug("grind : second grind");
	stepper->set_accell(500);
	Grinder::grind_until(1, initial_mass_g + this->_coffee_mass_g, 100, initial_mass_g); //brew coarsly and leave 1g

	print_debug("grind : second grind");
	stepper->set_accell(500);
	Grinder::grind_until(1, initial_mass_g + this->_coffee_mass_g, 100, initial_mass_g); //brew coarsly and leave 1g

	print_debug("grind : show result");
	float final_mass;
	while (!interface->button_clicked())
	{
		final_mass = balance->get_averaged_mass(100) - initial_mass_g;
		interface->print_coffee_mass(final_mass, "Grinded mass :");
	}
	print_debug("grind return");
}

void Grinder::print_averaged_mass(int nb_samples)
{
	UserInterface *interface = this->_interface;
	Balance *balance = this->_balance;
	float final_mass;
	while (!interface->button_clicked())
	{
		final_mass = balance->get_averaged_mass(nb_samples);
		interface->print_coffee_mass(final_mass, "Grinded mass :");
	}
	print_debug("grind return");
}

void Grinder::calibrate(void)
{
	print_debug("calibrate call");

	print_debug("calibrate : show message");
	this->_interface->show_message_validate("Place mass 1 and set mass value");

	print_debug("calibrate : get float");
	float ym1 = this->_interface->get_float(10.0, 0.1, "Mass 1", "g");

	print_debug("calibrate : get sig");
	float xm1 = this->_balance->get_sig();

	print_debug("calibrate : show message");
	this->_interface->show_message_validate("Place mass 2 and set mass value");

	print_debug("calibrate : get float");
	float ym2 = this->_interface->get_float(10.0, 0.1, "Mass 2", "g");

	print_debug("calibrate : get sig");
	float xm2 = this->_balance->get_sig();

	print_debug("calibrate : calculate calibration");
	float sensitivity = (ym2 - ym1) / (xm2 - xm1);
	float offcet = ym1 - sensitivity * xm1; //offSet

	print_debug("calibrate : set calibration");
	this->_balance->set_calibration(offcet, sensitivity);

	print_debug("calibrate return");
}

//Set max_time = 0 or max_mass = 0 to ignore
void	Grinder::grind_until(float duration_s, float mass_target_g, int speed_rpm, float initial_mass_g)
{
	print_debug("grind until call");
	absolute_time_t begin, end;
	int64_t elapsed = 0;
	begin = get_absolute_time();
	//clock_t time = 0.0;
	//clock_t time_ref = clock();
	float mass = 0.0;
	float i = initial_mass_g; // to remove

	print_debug("grind until : set speed");
	this->_stepper->set_speed(speed_rpm);

	print_debug("grind until : loop");
	while (1)
	{
		if (duration_s && elapsed >= duration_s)
			break;
		if (mass_target_g && mass >= mass_target_g)
			break;
		this->_interface->print_coffee_mass(mass - initial_mass_g, "Grinding...");
		end = get_absolute_time();
		elapsed = absolute_time_diff_us (begin, end) / 1000000;
		
		//time = (float)(clock() - time_ref) / CLOCKS_PER_SEC;



		mass = this->_balance->get_mass() - initial_mass_g;
		//mass = i; // to remove
		//i += 0.1; // to remove
	}
	this->_stepper->set_speed(0);

	print_debug("grind until return");
}

void	Grinder::show_data(void)
{
	Balance *balance = this->_balance;
	while (1)
	{
		balance->print_balance_data();
	}
}
