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
	PicoExplorer &px = pico_explorer;
	sleep_ms(300);
	while (1)
	{
		//width = height = 240
		std::stringstream strvalstream;
		strvalstream << std::fixed << std::setprecision(2) << res << unit;
		std::string str = strvalstream.str();

		//std::cout<<PicoExplorer::WIDTH<<"  "<<PicoExplorer::HEIGHT;
		px.set_pen(i * 2 % 160, i * 4 % 160, i * 8 % 160);
		px.clear();
		px.set_pen(255, 255, 255);
		px.text(prt , Point(000,  10), 220, 4);
		px.text(str , Point(000,  90), 220, 9);
		px.text("+" , Point(200,  30), 220, 10);
		px.text("-" , Point(200, 140), 220, 10);
		px.text("ok", Point(000, 170), 220, 4);
		px.update();

		if (pressed == 1 && waspressdebefore == 0)
		{
			sleep_ms(300);
			waspressdebefore = 1;
		}
		pressed = 1;
		i++;
		if(px.is_pressed(px.X))
			res += step;
		else if(px.is_pressed(px.Y))
			res -= step;
		else if(px.is_pressed(px.B))
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
