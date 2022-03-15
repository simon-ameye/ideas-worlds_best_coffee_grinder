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

#include "Stepper.hpp"

static void print_debug(std::string str)
{
	#ifdef PRINT_DEBUG
	std::cout << "Steper : " << str << std::endl;
	#endif
}

Stepper::Stepper(void)
{
	print_debug("constructor call");
	this->_accell_rpm_s = DEFAULT_ACCELL_S;
	this->_speed_rpm = 0;

	gpio_set_function(PUL_GPIO, GPIO_FUNC_PWM);
	this->_channel = pwm_gpio_to_channel(PUL_GPIO);
	this->_slice_num = pwm_gpio_to_slice_num(PUL_GPIO);
	pwm_set_clkdiv_int_frac(this->_slice_num, DIVIDER, 0);
	print_debug("constructor return");
	Stepper::enable();
	Stepper::disable();
}

Stepper::~Stepper(void)
{
	print_debug("destructor call");
	Stepper::set_speed(0);
	Stepper::disable();
	print_debug("destructor return");
}

void Stepper::set_speed(int speed_rpm)
{
	print_debug("set speed call");
	if (this->_speed_rpm == speed_rpm || speed_rpm > MAX_MOTOR_RPM)
	{
		print_debug("set speed :  same speed, skip");
		return ;
	}
	if (this->_speed_rpm == 0)
	{
		print_debug("set speed : previous speed was 0, enabling");
		Stepper::enable();
		Stepper::_set_direction(speed_rpm);
	}
	else if (speed_rpm != 0 && this->_speed_rpm != 0 && (speed_rpm < 0) != (this->_speed_rpm < 0))
	{
		print_debug("set speed : oposed speeds, first ramp to 0");
		Stepper::_speed_ramp(0);
		Stepper::_set_direction(speed_rpm);
	}
	Stepper::_speed_ramp(speed_rpm);
	if (speed_rpm == 0)
		Stepper::disable();
	print_debug("set speed return");
}

void Stepper::_speed_ramp(int speed_rpm)
{
	print_debug("speed ramp call");
	int start_freq_s;
	int end_freq_s;
	int sleep_per_step_us;
	int nb_of_steps;
	float total_time;
	int wrap;

	print_debug("speed ramp : calculation");
	start_freq_s = abs(this->_speed_rpm) * STEPS_PER_REV / 60;
	end_freq_s = abs(speed_rpm) * STEPS_PER_REV / 60;
	nb_of_steps = abs(end_freq_s - start_freq_s);
	total_time = (float)abs(speed_rpm - this->_speed_rpm) / (float)this->_accell_rpm_s;
	sleep_per_step_us = total_time * 1000000 / nb_of_steps;

/*
	std::cout<< "    lets speed ramp with data : \n";
	std::cout<< "    speed_rpm : " << speed_rpm <<std::endl;
	std::cout<< "    start_freq_s : " << start_freq_s <<std::endl;
	std::cout<< "    end_freq_s : " << end_freq_s <<std::endl;
	std::cout<< "    sleep_per_step_us : " << sleep_per_step_us <<std::endl;
	std::cout<< "    nb_of_steps : " << nb_of_steps <<std::endl;
	std::cout<< "    total_time : " << total_time <<std::endl;
	std::cout<< "    _speed_rpm : " << this->_speed_rpm <<std::endl;
	std::cout<< std::endl;
*/

	print_debug("speed ramp : loop");
	if (start_freq_s < end_freq_s)
	{
		for(int freq = start_freq_s; freq <= end_freq_s; freq++)
			Stepper::_set_wrap(wrap, freq, sleep_per_step_us);
	}
	else
	{
		for(int freq = start_freq_s; freq >= end_freq_s; freq--)
			Stepper::_set_wrap(wrap, freq, sleep_per_step_us);
	}
	this->_speed_rpm = speed_rpm;
	print_debug("speed ramp return");
}

void Stepper::_set_wrap(int wrap, int freq, int sleep_per_step_us)
{
	//print_debug("set wrap call");
	wrap = CLOCK / DIVIDER / freq;
	if (wrap > MAXWRAP)
		wrap = MAXWRAP;
	if (wrap < 1)
		wrap = 1;
	pwm_set_wrap(this->_slice_num, wrap);
	pwm_set_chan_level(this->_slice_num, this->_channel, wrap / 2);
	sleep_us(sleep_per_step_us);
	//print_debug("set wrap return");
}

void Stepper::enable(void)
{
	print_debug("enable call");
	pwm_set_enabled(this->_slice_num, 1);
	gpio_init(DIR_GPIO);
	gpio_set_dir(DIR_GPIO, GPIO_OUT);
	gpio_init(ENA_GPIO);
	gpio_set_dir(ENA_GPIO, GPIO_OUT);
	gpio_put(ENA_GPIO, 0);
	print_debug("enable return");
}

void Stepper::disable(void)
{
	print_debug("disable call");
	pwm_set_enabled(this->_slice_num, 0);
	gpio_put(ENA_GPIO, 1);
	print_debug("disable return");
}

void Stepper::_set_direction(int speed_rpm)
{
	print_debug("set direction call");
	if (speed_rpm > 0)
		gpio_put(DIR_GPIO, 1);
	else
		gpio_put(DIR_GPIO, 0);
	print_debug("set direction return");
}

void Stepper::set_accell(int accell_rpm_s)
{
	print_debug("set accell call");
	this->_accell_rpm_s = accell_rpm_s;
	print_debug("set accell return");
}

void Stepper::print_status(void)
{
	std::cout<< "    Stepper configuration :" <<std::endl;
	std::cout<< "    _channel : "		<< this->_channel		<< std::endl;
	std::cout<< "    _slice_num : "	<< this->_slice_num		<< std::endl;
	std::cout<< "    _pul_gpio : "		<< PUL_GPIO		<< std::endl;
	std::cout<< "    _ena_gpio : "		<< ENA_GPIO		<< std::endl;
	std::cout<< "    _dir_gpio : "		<< DIR_GPIO		<< std::endl;
	std::cout<< "    _accell_rpm_s : "	<< this->_accell_rpm_s	<< std::endl;
	std::cout<< "    _speed_rpm : "	<< this->_speed_rpm		<< std::endl;
	std::cout<< std::endl;
}
