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

#ifndef GRINDER_HPP
#define GRINDER_HPP

#include "Stepper.hpp"
#include "UserInterface.hpp"
#include "Balance.hpp"

#define DEFAULT_COFFEE_MASS_G 9.00;

class Grinder
{
	public:
			Grinder(Stepper *stepper, UserInterface *interface, Balance *balance);
	void	set_coffee_mass_g(void);
	float	get_coffee_mass_g(void);
	void	grind(void);
	void	calibrate(void);

	private:
	float	_coffee_mass_g;
	Stepper	*_stepper;
	UserInterface *_interface;
	Balance	*_balance;
};
#endif