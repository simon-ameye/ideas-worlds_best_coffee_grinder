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

#include <time.h>

#include "Stepper.hpp"
#include "UserInterface.hpp"
#include "Balance.hpp"

#include "UserConfig.hpp"

class Grinder
{
	public:
			Grinder(Stepper *stepper, UserInterface *interface, Balance *balance);
	void	set_coffee_mass_g(void);
	float	get_coffee_mass_g(void);
	void	grind(void);
	void	calibrate(void);
	void	tare(void);
	void	print_averaged_mass(int nb_samples);
	void	show_data(void);

	int		note(int n, int i);
	void	song(void);

	private:
	float	_coffee_mass_g;
	Stepper	*_stepper;
	UserInterface *_interface;
	Balance	*_balance;
	void	grind_until(float duration_s, float mass_target_g, int speed_rpm);
};
#endif