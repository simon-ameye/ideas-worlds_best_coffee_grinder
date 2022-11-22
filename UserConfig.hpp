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

#ifndef USERCONFIG_HPP
#define USERCONFIG_HPP

//Show debug messages
#define PRINT_DEBUG

//Balance.hpp
	#define DEFAULT_OFFSET 479.076
	#define DEFAULT_SENSITIVITY -0.0000586143
	#define CALIBRARION_FILE_NAME "load_cell_calibration.txt"

	#define FLASH_TARGET_OFFSET (256 * 1024)

//Hx711.hpp
	#define PD_SCK_GPIO 1 //GPIO pin for clock
	#define DOUT_GPIO 2 //GPIO pin for data reading
	#define GAIN 128
	#define T1 1
	#define T2 0.1 // not used
	#define T3 1
	#define T4 1

//Stepper.hpp
	//GPIO pins data
	#define PUL_GPIO 4
	#define ENA_GPIO 5
	#define DIR_GPIO 3

	//raspberry pi pico PWM data
	#define MAXWRAP 65534
	#define DIVIDER 255
	//#define DIVIDER 100

	#define CLOCK 125000000

	//motor data
	#define STEPS_PER_REV 200
	#define MAX_MOTOR_RPM 10000
	#define DEFAULT_ACCELL_S 500

//Grinder.hpp
	#define DEFAULT_COFFEE_MASS_G 9.00;

#endif