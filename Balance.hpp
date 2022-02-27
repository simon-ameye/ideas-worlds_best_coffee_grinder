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

#define DEFAULT_OFFSET 42.42
#define DEFAULT_SENSITIVITY -100.7333
#define CALIBRARION_FILE_NAME "load_cell_calibration.txt"

class Balance
{
	public:
			Balance(void);
	float	get_sig(void);
	float	get_mass(void);
	void	set_calibration(float offcet, float sensitivity);
	float	get_averaged_mass(int samples);

	private:
	void	_save_calibration(void);
	void	_recover_calibraton(void);
	float	_offset;
	float	_sensivity;
	Hx711	_Hx711;
};
#endif