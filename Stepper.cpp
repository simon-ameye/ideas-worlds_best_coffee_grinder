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

Stepper::Stepper(void)
{
	std::cout << "stepper : constructor call" << std::endl;
	this->_accell_rpm_s = DEFAULT_ACCELL_S;
	this->_speed_rpm = 0;

	gpio_set_function(PUL_GPIO, GPIO_FUNC_PWM);
	this->_channel = pwm_gpio_to_channel(PUL_GPIO);
	this->_slice_num = pwm_gpio_to_slice_num(PUL_GPIO);
	pwm_set_clkdiv_int_frac(this->_slice_num, DIVIDER, 0);
	std::cout << "stepper : constructor return" << std::endl;
}

Stepper::~Stepper(void)
{
	std::cout << "stepper : destructor call" << std::endl;
	Stepper::set_speed(0);
	Stepper::disable();
	std::cout << "stepper : destructor return" << std::endl;
}

void Stepper::set_speed(int speed_rpm)
{
	multicore_launch_core1(set_speed_thread(speed_rpm));
	multicore_fifo_pop_blocking();
}

void Stepper::set_speed_thread(int speed_rpm)
{
	std::cout << "stepper : set speed call" << std::endl;
	if (this->_speed_rpm == speed_rpm || speed_rpm > MAX_MOTOR_RPM)
	{
		std::cout << "stepper : set speed :  same speed, skip" << std::endl;
		return ;
	}
	if (this->_speed_rpm == 0)
	{
		std::cout << "stepper : set speed : previous speed was 0, enabling\n";
		Stepper::enable();
		Stepper::_set_direction(speed_rpm);
	}
	else if (speed_rpm != 0 && this->_speed_rpm != 0 && (speed_rpm < 0) != (this->_speed_rpm < 0))
	{
		std::cout << "stepper : set speed : oposed speeds, first ramp to 0" << std::endl;
		Stepper::_speed_ramp(0);
		Stepper::_set_direction(speed_rpm);
	}
	Stepper::_speed_ramp(speed_rpm);
	if (speed_rpm == 0)
		Stepper::disable();
	std::cout << "stepper : set speed return" << std::endl;

	exit(0);
}

void Stepper::_speed_ramp(int speed_rpm)
{
	std::cout << "stepper : speed ramp call" << std::endl;
	int start_freq_s;
	int end_freq_s;
	int sleep_per_step_us;
	int nb_of_steps;
	float total_time;
	int wrap;

	std::cout << "stepper : speed ramp : calculation" << std::endl;
	start_freq_s = abs(this->_speed_rpm) * STEPS_PER_REV / 60;
	end_freq_s = abs(speed_rpm) * STEPS_PER_REV / 60;
	nb_of_steps = abs(end_freq_s - start_freq_s);
	total_time = (float)abs(speed_rpm - this->_speed_rpm) / (float)this->_accell_rpm_s;
	sleep_per_step_us = total_time * 1000000 / nb_of_steps;

/*
	std::cout << "    lets speed ramp with data : \n";
	std::cout << "    speed_rpm : " << speed_rpm << std::endl;
	std::cout << "    start_freq_s : " << start_freq_s << std::endl;
	std::cout << "    end_freq_s : " << end_freq_s << std::endl;
	std::cout << "    sleep_per_step_us : " << sleep_per_step_us << std::endl;
	std::cout << "    nb_of_steps : " << nb_of_steps << std::endl;
	std::cout << "    total_time : " << total_time << std::endl;
	std::cout << "    _speed_rpm : " << this->_speed_rpm << std::endl;
	std::cout << std::endl;
*/

	std::cout << "stepper : speed ramp : loop" << std::endl;
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
	std::cout << "stepper : speed ramp return" << std::endl;
}

void Stepper::_set_wrap(int wrap, int freq, int sleep_per_step_us)
{
	//std::cout << "stepper : set wrap call" << std::endl;
	wrap = CLOCK / DIVIDER / freq;
	if (wrap > MAXWRAP)
		wrap = MAXWRAP;
	if (wrap < 1)
		wrap = 1;
	pwm_set_wrap(this->_slice_num, wrap);
	pwm_set_chan_level(this->_slice_num, this->_channel, wrap / 2);
	sleep_us(sleep_per_step_us);
	//std::cout << "stepper : set wrap return" << std::endl;
}

void Stepper::enable(void)
{
	std::cout << "stepper : enable call" << std::endl;
	pwm_set_enabled(this->_slice_num, 1);
	gpio_init(DIR_GPIO);
	gpio_init(ENA_GPIO);
	gpio_set_dir(ENA_GPIO, GPIO_OUT);
	gpio_put(ENA_GPIO, 1);
	std::cout << "stepper : enable return" << std::endl;
}

void Stepper::disable(void)
{
	std::cout << "stepper : disable call" << std::endl;
	pwm_set_enabled(this->_slice_num, 0);
	gpio_put(ENA_GPIO, 0);
	std::cout << "stepper : disable return" << std::endl;
}

void Stepper::_set_direction(int speed_rpm)
{
	std::cout << "stepper : set direction call" << std::endl;
	if (speed_rpm > 0)
		gpio_put(DIR_GPIO, 1);
	else
		gpio_put(DIR_GPIO, 0);
	std::cout << "stepper : set direction return" << std::endl;
}

void Stepper::set_accell(int accell_rpm_s)
{
	std::cout << "stepper : set accell call" << std::endl;
	this->_accell_rpm_s = accell_rpm_s;
	std::cout << "stepper : set accell return" << std::endl;
}

void Stepper::print_status(void)
{
	std::cout << "    Stepper configuration :" << std::endl;
	std::cout << "    _channel : "		<< this->_channel		<< std::endl;
	std::cout << "    _slice_num : "	<< this->_slice_num		<< std::endl;
	std::cout << "    _pul_gpio : "		<< PUL_GPIO		<< std::endl;
	std::cout << "    _ena_gpio : "		<< ENA_GPIO		<< std::endl;
	std::cout << "    _dir_gpio : "		<< DIR_GPIO		<< std::endl;
	std::cout << "    _accell_rpm_s : "	<< this->_accell_rpm_s	<< std::endl;
	std::cout << "    _speed_rpm : "	<< this->_speed_rpm		<< std::endl;
	std::cout << std::endl;
}
