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

#include "Stepper.hpp"
#include "UserInterface.hpp"

#define DEFAULT_COFFEE_MASS_G 9.00;

class Grinder
{
	public:
	Grinder(Stepper *stepper, UserInterface *interface);
	void set_coffee_mass_g(void);
	float get_coffee_mass_g(void);
	void grind(void);

	private:
	float _coffee_mass_g;
	Stepper *_stepper;
	UserInterface *_interface;
};