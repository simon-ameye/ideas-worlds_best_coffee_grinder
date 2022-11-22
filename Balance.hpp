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

#ifndef BALANCE_HPP
#define BALANCE_HPP

#include "Hx711.hpp"
#include <iostream>
#include <fstream>
#include <time.h>
#include <cerrno>
#include <cstring>
#include "hardware/timer.h"

					#include "hardware/flash.h"
					#include "pico/stdlib.h"
					#include "hardware/irq.h"
					#include "hardware/sync.h"

#include "UserConfig.hpp"

class Balance
{
	public:
					Balance(void);
	unsigned long	get_sig(void);
	float			get_mass(void);
	void			set_calibration(float offcet, float sensitivity);
	float			get_averaged_mass(int samples);
	void			print_balance_data();
	float			get_sensivity();
	float			get_offset();

	private:
	void	_save_calibration(void);
	void	_recover_calibraton(void);
	float	_offset;
	float	_sensivity;
	Hx711	_Hx711;
};
#endif