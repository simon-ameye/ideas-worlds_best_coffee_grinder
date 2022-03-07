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

static void print_debug(std::string str)
{
	#ifdef PRINT_DEBUG
	std::cout << str << std::endl;
	#endif
}

static std::string float_mass_to_str(float a_value)
{
	std::ostringstream out;
	out.precision(2);
	out << std::fixed << a_value << "g";
	return out.str();
}

UserInterface::UserInterface(void)
{
	print_debug("userinterface : constructor call");
	uint16_t buffer[PicoExplorer::WIDTH * PicoExplorer::HEIGHT];
	this->_pico_explorer = new PicoExplorer(buffer);
	PicoExplorer *px = this->_pico_explorer;
	px->init();
	px->set_font(&font8);
	px->set_pen(0, 0, 0);
	px->clear();
	px->set_pen(255, 255, 255);
	px->text("initializing..." , Point(000,  10), 220, 3);
	px->update();
	print_debug("userinterface : constructor return");
}

UserInterface::~UserInterface(void)
{
	print_debug("userinterface : destructor call");
	delete this->_pico_explorer;
	print_debug("userinterface : destructor return");
}

char UserInterface::show_menu(std::string str_A, std::string str_B, std::string str_X, std::string str_Y, float coffee_mass_g)
{
	print_debug("userinterface : show menu call");
	PicoExplorer *px = this->_pico_explorer;

	print_debug("userinterface : show menu : set rectangles");
	Rect rectA(  0,   0, 120, 120);
	Rect rectB(  0, 119, 120, 120);
	Rect rectX(119,   0, 120, 120);
	Rect rectY(119, 119, 120, 120);

	print_debug("userinterface : show menu : draw rectangles");
	px->set_pen(100, 100, 0);
	px->rectangle(rectA);
	px->set_pen(  0, 100, 100);
	px->rectangle(rectB);
	px->set_pen(100,   0, 100);
	px->rectangle(rectX);
	px->set_pen(100, 100, 100);
	px->rectangle(rectY);
	px->set_pen(255, 255, 255);

	print_debug("userinterface : show menu : draw text");
	std::string strAA = str_A + " " + float_mass_to_str(coffee_mass_g);
	px->text(strAA,			Point(0 ,   50), 220, 2);
	px->text(str_B,			Point(0 ,  170), 220, 2);
	px->text(str_X,			Point(120,  50), 220, 2);
	px->text(str_Y,			Point(120, 170), 220, 2);

	px->update();

	print_debug("userinterface : show menu : loop");
	char button;
	while (1)
	{
		if (button = this->button_clicked())
			return (button);
	}
	print_debug("userinterface : show menu return");
	return (0);
}

float UserInterface::get_float(float init_value, float step, std::string prt, std::string unit)
{
	print_debug("userinterface : get float call");

	//std::cout << "width : " << PicoExplorer::WIDTH << "height : " << PicoExplorer::HEIGHT << std::endl;
	float res;
	res = init_value;
	bool pressed = 0;
	bool waspressdebefore = 0;
	int i = 0;
	PicoExplorer *px = this->_pico_explorer;
	sleep_ms(300);
	Rect rectangle(0, 0, 239, 239);

	std::string str;
	print_debug("userinterface : get float : loop");
	while (1)
	{
		px->set_pen(i * 2 % 160, i * 4 % 160, i * 8 % 160);
		px->rectangle(rectangle);
		px->set_pen(255, 255, 255);

		str = float_mass_to_str(res);
		px->text(prt , Point(  0,  10), 220, 4);
		px->text(str , Point(  0,  90), 220, 9);
		px->text("+" , Point(200,  30), 220, 10);
		px->text("-" , Point(200, 140), 220, 10);
		px->text("ok", Point(  0, 170), 220, 4);
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
		else if(this->_button_click() == 'Y')
			res -= step;
		else if(this->_button_click() == 'B')
		{
			this->button_clicked();
			break ;
		}
		else
		{
			i--;
			pressed = 0;
			waspressdebefore = 0;
		}
	}
	print_debug("userinterface : get float return");
	return (res);
}

void UserInterface::show_message_validate(std::string str)
{
	print_debug("userinterface : show message validate call");
	//std::cout << "userinterface : string : " << str << std::endl;
	PicoExplorer *px = this->_pico_explorer;
	Rect rectangle(0, 0, 239, 239);
	px->set_pen(0, 0, 0);
	px->rectangle(rectangle);
	px->set_pen(255, 255, 255);
	px->text(str , Point(  0,   0), 220, 4);
	px->text("ok", Point(  0, 170), 220, 4);
	px->update();

	print_debug("userinterface : show message validate : loop");
	while (1)
	{
		if(this->button_clicked() == 'B')
			break ;
	}
	print_debug("userinterface : show message validate return");
}
void UserInterface::show_message_pass(std::string str)
{
	print_debug("userinterface : show message pass call");
	PicoExplorer *px = this->_pico_explorer;
	Rect rectangle(0, 0, 239, 239);
	px->set_pen(0, 0, 0);
	px->rectangle(rectangle);
	px->set_pen(255, 255, 255);
	px->text(str , Point(000,  90), 220, 4);
	px->update();
	print_debug("userinterface : show message pass return");
}

void UserInterface::print_coffee_mass(float mass, std::string str)
{
	print_debug("userinterface : print coffee mass call");
	//std::stringstream mass_strvalstream;
	//std::string mass_str;
	//mass_strvalstream << std::fixed << std::setprecision(2) << mass << "g";
	//mass_str = mass_strvalstream.str();

	PicoExplorer *px = this->_pico_explorer;
	Rect rectangle(0, 0, 239, 239);
	px->set_pen(0, 0, 0);
	px->rectangle(rectangle);
	px->set_pen(255, 255, 255);
	px->text(str , Point(0,  0), 220, 4);
	px->text(float_mass_to_str(mass) , Point(0,  90), 220, 5);
	px->update();
	print_debug("userinterface : print coffee mass return");
}

char UserInterface::_button_click(void)
{
	//print_debug("userinterface : button click call");
	PicoExplorer *px = this->_pico_explorer;
	if	   (px->is_pressed(px->X))
		return('X');
	else if(px->is_pressed(px->Y))
		return('Y');
	else if(px->is_pressed(px->A))
		return('A');
	else if(px->is_pressed(px->B))
		return('B');
	//print_debug("userinterface : button click return");
	return (0);
}

char UserInterface::button_clicked(void)
{
	//print_debug("userinterface : button clicked call");
	char button = this->_button_click();
	while (this->_button_click());
	//print_debug("userinterface : button clicked return");
	return (button);
}
