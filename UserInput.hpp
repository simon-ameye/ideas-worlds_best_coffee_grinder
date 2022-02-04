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

#ifndef USERINPUT_HPP
#define USERINPUT_HPP

#include "pico_explorer.hpp"
#include "serial_print.hpp"
#include <iomanip>
#include <sstream>
#include <iostream>

using namespace pimoroni;

class UserInput
{
	public:
	float get_float(float init_value, float step, std::string prompt, std::string unit, PicoExplorer pico_explorer);
	private:
};

#endif