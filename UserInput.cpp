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

#include "UserInput.hpp"

float UserInput::get_float(float init_value, float step, std::string prt, std::string unit, PicoExplorer pico_explorer)
{
	float res;
	res = init_value;
	bool pressed = 0;
	bool waspressdebefore = 0;
	int i = 0;
	sleep_ms(300);
	while (1)
	{
		//width = height = 240
		std::stringstream strvalstream;
		strvalstream << std::fixed << std::setprecision(2) << res << unit;
		std::string str = strvalstream.str();

		//std::cout<<PicoExplorer::WIDTH<<"  "<<PicoExplorer::HEIGHT;
		pico_explorer.set_pen(i * 2 % 160, i * 4 % 160, i * 8 % 160);
		pico_explorer.clear();
		pico_explorer.set_pen(255, 255, 255);
		pico_explorer.text(prt , Point(000,  10), 220, 4);
		pico_explorer.text(str , Point(000,  90), 220, 9);
		pico_explorer.text("+" , Point(200,  30), 220, 10);
		pico_explorer.text("-" , Point(200, 140), 220, 10);
		pico_explorer.text("ok", Point(000, 170), 220, 4);
		pico_explorer.update();

		if (pressed == 1 && waspressdebefore == 0)
		{
			sleep_ms(300);
			waspressdebefore = 1;
		}
		pressed = 1;
		i++;
		if(pico_explorer.is_pressed(pico_explorer.X))
			res += step;
		else if(pico_explorer.is_pressed(pico_explorer.Y))
			res -= step;
		else if(pico_explorer.is_pressed(pico_explorer.B))
			break ;
		else
		{
			i--;
			pressed = 0;
			waspressdebefore = 0;
		}
	}
	return (res);
}
