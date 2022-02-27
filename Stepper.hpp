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

#ifndef STEPPER_H
#define STEPPER_H

#include "hardware/pwm.h"
#include "pico/stdlib.h"
#include <math.h>
#include <iostream>

//GPIO pins data
#define PUL_GPIO 0
#define ENA_GPIO 25
#define DIR_GPIO 13

//raspberry pi pico PWM data
#define MAXWRAP 65534
#define DIVIDER 255
#define CLOCK 125000000

//motor data
#define STEPS_PER_REV 200
#define MAX_MOTOR_RPM 10000
#define DEFAULT_ACCELL_S 500

class Stepper
{
	public:
	Stepper(void);
	~Stepper(void);
	void set_speed(int speed_rmp);
	void enable(void);
	void disable(void);
	void set_accell(int accell_rpm_s);
	void print_status(void);

	private:
	uint _channel;
	uint _slice_num;
	uint _pul_gpio;
	uint _ena_gpio;
	uint _dir_gpio;
	uint _accell_rpm_s;
	int _speed_rpm;
	void _speed_ramp(int speed_rmp);
	void _set_wrap(int wrap, int freq, int sleep_per_step_us);
	void _set_direction(int dir);
};
#endif