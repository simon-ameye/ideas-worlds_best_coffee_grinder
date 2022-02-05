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

#include <iostream>
#include <fstream>

#define DEFAULT_OFFSET 42.42
#define DEFAULT_SENSITIVITY -100.7333
#define CALIBRARION_FILE_NAME "load_cell_calibration.txt"

class Balance
{
	public:
			Balance(void);
	float	get_sig(void);
	float	get_load(void);
	void	set_calibration(float offcet, float sensitivity);

	private:
	void	_save_calibration(void);
	void	_recover_calibraton(void);
	float	_offset;
	float	_sensivity;
};
#endif