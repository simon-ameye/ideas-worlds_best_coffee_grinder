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

#ifndef USERINTERFACE_HPP
#define USERINTERFACE_HPP

#include "pico_explorer.hpp"
#include "font8_data.hpp"
#include <iomanip>
#include <sstream>
#include <iostream>

using namespace pimoroni;

class UserInterface// : pimoroni::PicoExplorer// PUTAIN IMPOSSIBLE DE DECLARER CETTE CLASSE COMME CA
{
	public:
	UserInterface(void);
	~UserInterface(void);
	float get_float(float init_value, float step, std::string prompt, std::string unit);
	char show_menu(std::string str_A, std::string str_B, std::string str_X, std::string str_Y);
	void show_message_validate(std::string str);
	void show_message_pass(std::string str);


	private:
	//PicoExplorer pimoroni::_pico_explorer(uint16_t buffer);
	PicoExplorer *_pico_explorer;
};

#endif