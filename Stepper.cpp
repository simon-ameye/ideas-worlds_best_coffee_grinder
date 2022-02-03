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

Stepper::Stepper(uint pul_gpio, uint ena_gpio, uint dir_gpio)
{
	std::cout << "Stepper constructor called\n";
	this->_accell_rpm_s = 500;
	this->_speed_rpm = 0;

	this->_pul_gpio = pul_gpio;
	this->_ena_gpio = ena_gpio;
	this->_dir_gpio = dir_gpio;

	gpio_set_function(pul_gpio, GPIO_FUNC_PWM);
	this->_channel = pwm_gpio_to_channel(pul_gpio);
	this->_slice_num = pwm_gpio_to_slice_num(pul_gpio);
	pwm_set_clkdiv_int_frac(this->_slice_num, DIVIDER, 0);
	std::cout << "Stepper constructor done\n";
}

Stepper::~Stepper(void)
{
	std::cout << "Stepper destructor called\n";
	Stepper::set_speed(0);
	Stepper::disable();
	std::cout << "Stepper destructor done\n";
}

void Stepper::set_speed(int speed_rpm)
{
	std::cout << "set_speed called\n";
	if (this->_speed_rpm == speed_rpm || speed_rpm > MAX_MOTOR_RPM)
	{
		std::cout << "same speed, skip\n";
		return ;
	}
	if (this->_speed_rpm == 0)
	{
		std::cout << "previous speed was 0, enabling\n";
		Stepper::enable();
		Stepper::_set_direction(speed_rpm);
	}
	else if ((speed_rpm <= 0) != (this->_speed_rpm <= 0))
	{
		std::cout << "oposed speeds, first ramp to 0\n";
		Stepper::_speed_ramp(0);
		Stepper::_set_direction(speed_rpm);
	}
	Stepper::_speed_ramp(speed_rpm);
	if (speed_rpm == 0)
		Stepper::disable();
	std::cout << "speed set\n";
}

void Stepper::_speed_ramp(int speed_rpm)
{
	std::cout << "stepper :: speed_ramp\n";
	int start_freq_s;
	int end_freq_s;
	int sleep_per_step_us;
	int nb_of_steps;
	float total_time;
	int wrap;

	start_freq_s = abs(this->_speed_rpm) * STEPS_PER_REV / 60;
	end_freq_s = abs(speed_rpm) * STEPS_PER_REV / 60;
	nb_of_steps = abs(end_freq_s - start_freq_s);
	total_time = (float)abs(speed_rpm - this->_speed_rpm) / (float)this->_accell_rpm_s;
	sleep_per_step_us = total_time * 1000000 / nb_of_steps;

	std::cout << "lets speed ramp with data : \n";
	std::cout << "speed_rpm : " << speed_rpm << std::endl;
	std::cout << "start_freq_s : " << start_freq_s << std::endl;
	std::cout << "end_freq_s : " << end_freq_s << std::endl;
	std::cout << "sleep_per_step_us : " << sleep_per_step_us << std::endl;
	std::cout << "nb_of_steps : " << nb_of_steps << std::endl;
	std::cout << "total_time : " << total_time << std::endl;
	std::cout << "_speed_rpm : " << this->_speed_rpm << std::endl;
	std::cout << std::endl;

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
}

void Stepper::_set_wrap(int wrap, int freq, int sleep_per_step_us)
{
	wrap = CLOCK / DIVIDER / freq;
	if (wrap > MAXWRAP)
		wrap = MAXWRAP;
	if (wrap < 1)
		wrap = 1;
	//std::cout << "wrap : " << wrap << std::endl;
	pwm_set_wrap(this->_slice_num, wrap);
	pwm_set_chan_level(this->_slice_num, this->_channel, wrap / 2);
	sleep_us(sleep_per_step_us);
}

void Stepper::enable(void)
{
	std::cout << "stepper :: enable\n";
	pwm_set_enabled(this->_slice_num, 1);
	gpio_init(this->_dir_gpio);
	gpio_init(this->_ena_gpio);
	gpio_set_dir(this->_ena_gpio, GPIO_OUT);
	gpio_put(this->_ena_gpio, 1);
}

void Stepper::disable(void)
{
	std::cout << "stepper :: disable\n";
	pwm_set_enabled(this->_slice_num, 0);
	gpio_put(this->_ena_gpio, 0);
}

void Stepper::_set_direction(int speed_rpm)
{
	std::cout << "_set_direction\n";
	if (speed_rpm > 0)
		gpio_put(this->_dir_gpio, 1);
	else
		gpio_put(this->_dir_gpio, 0);
}

void Stepper::set_accell(int accell_rpm_s)
{
	std::cout << "_set_accell\n";
	this->_accell_rpm_s = accell_rpm_s;
}

void Stepper::print_status(void)
{
	std::cout << "Stepper configuration :" << std::endl;
	std::cout << "_channel : "		<< this->_channel		<< std::endl;
	std::cout << "_slice_num : "	<< this->_slice_num		<< std::endl;
	std::cout << "_pul_gpio : "		<< this->_pul_gpio		<< std::endl;
	std::cout << "_ena_gpio : "		<< this->_ena_gpio		<< std::endl;
	std::cout << "_dir_gpio : "		<< this->_dir_gpio		<< std::endl;
	std::cout << "_accell_rpm_s : "	<< this->_accell_rpm_s	<< std::endl;
	std::cout << "_speed_rpm : "	<< this->_speed_rpm		<< std::endl;
	std::cout << std::endl;
}
