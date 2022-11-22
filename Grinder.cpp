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
	tare();
	tare();
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
	//float initial_mass_g;

	this->_interface->show_message_validate("Please place container on balance");

	/*
	print_debug("grind : feedback");
	stepper->set_hard_frequency(500);
	sleep_ms(500);
	stepper->set_hard_frequency(0);
	return ;
	*/


	interface->print_coffee_mass(0, "Grinding init :");
	tare();

	int j = 10;
	while (j-- > 0)
	{
		_stepper->set_hard_frequency(-1000);
		sleep_ms(100);
		_stepper->set_hard_frequency(0);
		sleep_ms(100);
	}

/*
	print_debug("grind : debourage");
	stepper->set_accell(500);
	stepper->set_speed(-100); // debourage
	stepper->set_speed(0);
	stepper->set_speed(-100); // debourage
	stepper->set_speed(0);
	stepper->set_speed(-100); // debourage
	stepper->set_speed(0);
*/


	print_debug("grind : first grind");
	stepper->set_accell(500);
	grind_until(100, this->_coffee_mass_g - 1, 500); //brew coarsly and leave n g

	print_debug("grind : secondary grinds");
	stepper->set_accell(1000);

	float flow_rate = 0.5f; // init value g/s
	float grind_time; // s
	float new_mass;

	sleep_ms(100);
	float mass = balance->get_mass();

	int i = 6; // nb of fine grinds
	while (i-- > 0) // n .. 3 2 1
	{
		grind_time = (this->_coffee_mass_g - mass) / i / flow_rate;
		grind_until(grind_time, this->_coffee_mass_g, 60);
		sleep_ms(100);
		new_mass = balance->get_mass();
		flow_rate = (new_mass - mass) / grind_time;
		mass = new_mass;
	}

	show_data();
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
	float offset = ym1 - sensitivity * xm1;

	print_debug("calibrate : set calibration");
	this->_balance->set_calibration(offset, sensitivity);

	print_debug("calibrate return");
}

void Grinder::tare(void)
{
	print_debug("tare call");
	sleep_ms(100);
	float offset = - (this->_balance->get_sig() * this->_balance->get_sensivity());
	this->_balance->set_calibration(offset, this->_balance->get_sensivity());
	print_debug("tare return");
}

//Set max_time = 0 or max_mass = 0 to ignore
void	Grinder::grind_until(float duration_s, float mass_target_g, int speed_rpm)
{
	print_debug("grind until call");
	absolute_time_t begin, end;
	int64_t elapsed = 0;
	float mass = 0;
	//clock_t time = 0.0;
	//clock_t time_ref = clock();
	//float mass = -100.0;
	//float i = initial_mass_g; // to remove
	begin = get_absolute_time();

	print_debug("grind until : set speed");
	this->_stepper->set_speed(speed_rpm);

	print_debug("grind until : loop");
	while (1)
	{
		mass = this->_balance->get_mass();
		this->_interface->print_coffee_mass(mass, "Grinding...");
		end = get_absolute_time();
		elapsed = absolute_time_diff_us (begin, end) / 1000000;
		if (duration_s > 0.0f && elapsed >= duration_s)
			break;
		if (mass_target_g > 0.0f && mass >= mass_target_g)
			break;
		
		//time = (float)(clock() - time_ref) / CLOCKS_PER_SEC;



		//mass = i; // to remove
		//i += 0.1; // to remove
	}
	this->_stepper->set_speed(0);

	print_debug("grind until return");
}











int Grinder::note(int n, int i)
{
	switch (n)
	{
		case 1:
			return (-523 * i);
		case 2:
			return (-587 * i);
		case 3:
			return (-659 * i);
		case 4:
			return (-698 * i);
		case 5:
			return (-784 * i);
		case 6:
			return (-880 * i);
		case 7:
			return (-988 * i);
		default:
			return (0);
	}
}

void Grinder::song()
{
	{
		int song[] = {1, 2, 3, 4, 5, 6, 7, 0};
		int i = 0;
		while (song[i])
		{
			this->_interface->play_note(abs(note(song[i], 2)), 1);
			sleep_ms(200);
			i++;
		}
		this->_interface->play_note(0, 0);
	}
	/*
	{
		int song[] = {7, 6, 5, 4, 3, 2, 1, 3, 5 , 3, 1, 5, 3, 5, 1, 0};
		int i = 0;
		while (song[i])
		{
			_stepper->set_hard_frequency(note(song[i], 8));
			sleep_ms(200);
			i++;
		}
		_stepper->set_hard_frequency(0);
	}
	*/
}

void	Grinder::show_data(void)
{
	print_debug("show data");
	//this->_interface->play_note(1000);
	float mass;
	while (!this->_interface->button_clicked())
	{
		mass = this->_balance->get_mass();
		this->_interface->print_coffee_mass(mass, "Mass :");
		//this->_balance->print_balance_data();
	}
}
