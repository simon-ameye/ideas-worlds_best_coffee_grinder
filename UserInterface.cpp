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

UserInterface::UserInterface(void)
{
	std::cout << "userinterface : constructor call" << std::endl;
	uint16_t buffer[PicoExplorer::WIDTH * PicoExplorer::HEIGHT];
	this->_pico_explorer = new PicoExplorer(buffer);
	PicoExplorer *px = this->_pico_explorer;
	px->init();
	px->set_font(&font8);
	px->set_pen(0, 0, 0);
	px->clear();
	px->update();
	std::cout << "userinterface : constructor return" << std::endl;
}

UserInterface::~UserInterface(void)
{
	std::cout << "userinterface : destructor call" << std::endl;
	delete this->_pico_explorer;
	std::cout << "userinterface : destructor return" << std::endl;
}

char UserInterface::show_menu(std::string str_A, std::string str_B, std::string str_X, std::string str_Y)
{
	std::cout << "userinterface : show menu call" << std::endl;
	PicoExplorer *px = this->_pico_explorer;

	std::cout << "userinterface : show menu : set rectangles" << std::endl;
	Rect rectA(  0,   0, 120, 120);
	Rect rectB(  0, 120, 120, 120);
	Rect rectX(120,   0, 120, 120);
	Rect rectY(120, 120, 120, 120);

	std::cout << "userinterface : show menu : draw rectangles" << std::endl;
	px->set_pen(100, 100, 0);
	px->rectangle(rectA);
	px->set_pen(  0, 100, 100);
	px->rectangle(rectB);
	px->set_pen(100,   0, 100);
	px->rectangle(rectX);
	px->set_pen(100, 100, 100);
	px->rectangle(rectY);
	px->set_pen(255, 255, 255);

	std::cout << "userinterface : show menu : draw text" << std::endl;
	px->text(str_A,			Point(0  ,   0), 220, 4);
	px->text(str_B,	Point(0  , 120), 220, 4);
	px->text(str_X,		Point(120,   0), 220, 4);
	px->text(str_Y,			Point(120, 120), 220, 4);

	std::cout << "userinterface : show menu : loop" << std::endl;
	char button;
	while (1)
	{
		if (button = this->button_clicked())
			return (button);
	}
	std::cout << "userinterface : show menu return" << std::endl;
	return (0);
}

float UserInterface::get_float(float init_value, float step, std::string prt, std::string unit)
{
	std::cout << "userinterface : get float call" << std::endl;

	//std::cout << "width : " << PicoExplorer::WIDTH << "height : " << PicoExplorer::HEIGHT << std::endl;
	float res;
	res = init_value;
	bool pressed = 0;
	bool waspressdebefore = 0;
	int i = 0;
	PicoExplorer *px = this->_pico_explorer;
	sleep_ms(300);
	Rect rectangle(0, 0, 239, 239);
	std::stringstream strvalstream;
	std::string str;

	std::cout << "userinterface : get float : loop" << std::endl;
	while (1)
	{
		strvalstream << std::fixed << std::setprecision(2) << res << unit;
		str = strvalstream.str();
		px->set_pen(i * 2 % 160, i * 4 % 160, i * 8 % 160);
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
		if(this->_button_click() == 'X')
			res += step;
		if(this->_button_click() == 'Y')
			res -= step;
		if(this->_button_click() == 'B')
			break ;
		else
		{
			i--;
			pressed = 0;
			waspressdebefore = 0;
		}
	}
	std::cout << "userinterface : get float return" << std::endl;
	return (res);
}

void UserInterface::show_message_validate(std::string str)
{
	std::cout << "userinterface : show message validate call" << std::endl;
	PicoExplorer *px = this->_pico_explorer;
	Rect rectangle(0, 0, 239, 239);
	px->set_pen(0, 0, 0);
	px->rectangle(rectangle);
	px->set_pen(255, 255, 255);
	px->text(str , Point(000,  90), 220, 4);

	std::cout << "userinterface : show message validate : loop" << std::endl;
	while (1)
	{
		px->text("ok", Point(000, 170), 220, 4);
		if(this->button_clicked() == 'B')
			break ;
	}
	std::cout << "userinterface : show message validate return" << std::endl;
}
void UserInterface::show_message_pass(std::string str)
{
	std::cout << "userinterface : show message pass call" << std::endl;
	PicoExplorer *px = this->_pico_explorer;
	Rect rectangle(0, 0, 239, 239);
	px->set_pen(0, 0, 0);
	px->rectangle(rectangle);
	px->set_pen(255, 255, 255);
	px->text(str , Point(000,  90), 220, 4);
	std::cout << "userinterface : show message pass return" << std::endl;
}

void UserInterface::print_coffee_mass(float mass, std::string str)
{
	std::cout << "userinterface : print coffee mass call" << std::endl;
	std::stringstream mass_strvalstream;
	std::string mass_str;
	mass_strvalstream << std::fixed << std::setprecision(2) << mass << "g";
	mass_str = mass_strvalstream.str();

	PicoExplorer *px = this->_pico_explorer;
	Rect rectangle(0, 0, 239, 239);
	px->set_pen(0, 0, 0);
	px->rectangle(rectangle);
	px->set_pen(255, 255, 255);
	px->text(str , Point(0,  0), 220, 4);
	px->text(mass_str , Point(0,  90), 220, 9);
	std::cout << "userinterface : print coffee mass return" << std::endl;
}

char UserInterface::_button_click(void)
{
	std::cout << "userinterface : button click call" << std::endl;
	PicoExplorer *px = this->_pico_explorer;
	if(px->is_pressed(px->X))
		return('X');
	else if(px->is_pressed(px->Y))
		return('Y');
	else if(px->is_pressed(px->A))
		return('A');
	else if(px->is_pressed(px->A))
		return('B');
	std::cout << "userinterface : button click return" << std::endl;
	return (0);
}

char UserInterface::button_clicked(void)
{
	std::cout << "userinterface : button clicked call" << std::endl;
	char button = this->_button_click();
	while (this->_button_click());
	std::cout << "userinterface : button clicked return" << std::endl;
	return (button);
}
