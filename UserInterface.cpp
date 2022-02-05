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

#include "UserInterface.hpp"

//uint16_t buffer[PicoExplorer::WIDTH * PicoExplorer::HEIGHT];
//UserInterface::UserInterface(void) : pico_explorer
UserInterface::UserInterface(void)
{
	std::cout << "interface constructor called" << std::endl;
	//PicoExplorer pico_explorer(buffer);
	//this->_pico_explorer = pico_explorer;
	uint16_t buffer[PicoExplorer::WIDTH * PicoExplorer::HEIGHT];
	this->_pico_explorer = new PicoExplorer(buffer);
	PicoExplorer *px = this->_pico_explorer;
	px->init();
	px->set_font(&font8);
	px->set_pen(0, 0, 0);
	px->clear();
	px->update();
}

UserInterface::~UserInterface(void)
{
	std::cout << "interface desstructor called" << std::endl;
	delete this->_pico_explorer;
}

char UserInterface::show_menu(std::string str_A, std::string str_B, std::string str_X, std::string str_Y)
{
	sleep_ms(300);
	PicoExplorer *px = this->_pico_explorer;
	Rect rectA(  0,   0, 120, 120);
	Rect rectB(  0, 120, 120, 120);
	Rect rectX(120,   0, 120, 120);
	Rect rectY(120, 120, 120, 120);

	px->set_pen(100, 100, 0);
	px->rectangle(rectA);
	px->set_pen(  0, 100, 100);
	px->rectangle(rectB);
	px->set_pen(100,   0, 100);
	px->rectangle(rectX);
	px->set_pen(100, 100, 100);
	px->rectangle(rectY);
	px->set_pen(255, 255, 255);

	px->text(str_A,			Point(0  ,   0), 220, 4);
	px->text(str_B,	Point(0  , 120), 220, 4);
	px->text(str_X,		Point(120,   0), 220, 4);
	px->text(str_Y,			Point(120, 120), 220, 4);

	while (1)
	{
		if(px->is_pressed(px->A))
			return ('A');
		if(px->is_pressed(px->B))
			return ('B');
		if(px->is_pressed(px->X))
			return ('X');
		if(px->is_pressed(px->Y))
			return ('Y');
	}
	return ('0');
}

float UserInterface::get_float(float init_value, float step, std::string prt, std::string unit)
{
	std::cout << "UserInterface::get_float" << std::endl;
	std::cout << "width : " << PicoExplorer::WIDTH << "height : " << PicoExplorer::HEIGHT << std::endl;
	//std::cout << "1" << std::endl;
	float res;
	res = init_value;
	bool pressed = 0;
	bool waspressdebefore = 0;
	int i = 0;
	PicoExplorer *px = this->_pico_explorer;
	sleep_ms(300);
	//std::cout << "2" << std::endl;
	Rect rectangle(0, 0, 239, 239);
	std::stringstream strvalstream;
	std::string str;
	while (1)
	{
		//width = height = 240
		strvalstream << std::fixed << std::setprecision(2) << res << unit;
		str = strvalstream.str();
		//std::cout << "3" << std::endl;
		//px->clear();

		//std::cout<<PicoExplorer::WIDTH<<"  "<<PicoExplorer::HEIGHT;
		px->set_pen(i * 2 % 160, i * 4 % 160, i * 8 % 160);
			//px->set_pen(0, 0, 0);
		//px->clear();
		px->rectangle(rectangle);

		px->set_pen(255, 255, 255);

		px->text(prt , Point(000,  10), 220, 4);
		px->text(str , Point(000,  90), 220, 9);
		px->text("+" , Point(200,  30), 220, 10);
		px->text("-" , Point(200, 140), 220, 10);
		px->text("ok", Point(000, 170), 220, 4);
		px->update();

		if (pressed == 1 && waspressdebefore == 0)
		{
			sleep_ms(300);
			waspressdebefore = 1;
		}
		pressed = 1;
		i++;
		if(px->is_pressed(px->X))
			res += step;
		else if(px->is_pressed(px->Y))
			res -= step;
		else if(px->is_pressed(px->B))
			break ;
		else
		{
			i--;
			pressed = 0;
			waspressdebefore = 0;
		}
	}
	std::cout << "UserInterface::get_float returned " << res << std::endl;
	return (res);
}

void UserInterface::show_message_validate(std::string str)
{
	PicoExplorer *px = this->_pico_explorer;
	Rect rectangle(0, 0, 239, 239);
	px->set_pen(0, 0, 0);
	px->rectangle(rectangle);
	px->set_pen(255, 255, 255);
	px->text(str , Point(000,  90), 220, 4);
	while (1)
	{
		px->text("ok", Point(000, 170), 220, 4);
		if(px->is_pressed(px->B))
			break ;
	}
	sleep_ms(300);
}
void UserInterface::show_message_pass(std::string str)
{
	PicoExplorer *px = this->_pico_explorer;
	Rect rectangle(0, 0, 239, 239);
	px->set_pen(0, 0, 0);
	px->rectangle(rectangle);
	px->set_pen(255, 255, 255);
	px->text(str , Point(000,  90), 220, 4);
}
