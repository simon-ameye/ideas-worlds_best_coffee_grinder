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

#include "Balance.hpp"

static void print_debug(std::string str)
{
	#ifdef PRINT_DEBUG
	std::cout<< "Balance : " << str <<std::endl;
	#endif
}

Balance::Balance(void)
{
	print_debug("constructor call");
	_recover_calibraton();
}

void Balance::_save_calibration(void)
{
	print_debug("save calibration call");
	
	/*
					/ We're going to erase and reprogram a region 256k from the start of flash.
					// Once done, we can access this at XIP_BASE + 1500k.
					#define FLASH_TARGET_OFFSET (1500 * 1024)

					const uint8_t *flash_target_contents = (const uint8_t *) (XIP_BASE + FLASH_TARGET_OFFSET);

						uint16_t     temp;
						uint8_t  resetcount_EEPROM[FLASH_PAGE_SIZE];
						// Keep a reset count
						temp = flash_target_contents[0] + (flash_target_contents[1] * 256);
						temp++;	
						resetcount_EEPROM[0] = temp & 0xFF;
						resetcount_EEPROM[1] = ((temp & 0xFF00) >> 8);
						uint32_t ints = save_and_disable_interrupts();
						flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE);
						flash_range_program(FLASH_TARGET_OFFSET, resetcount_EEPROM, FLASH_PAGE_SIZE);
						restore_interrupts (ints);
	*/
	//_recover_calibraton();
	print_debug("save calibration return");
}

void Balance::_recover_calibraton(void)
{
	print_debug("recover calibration call");
	_sensivity = DEFAULT_SENSITIVITY;
	_offset = DEFAULT_OFFSET;

	print_debug("recover calibration return");
}

unsigned long Balance::get_sig(void)
{
	//print_debug("get sig call");
	unsigned long sig = _Hx711.ReadCound();
	//print_debug("get sig returned sig = " << sig);
	return (sig);
}

float Balance::get_mass(void)
{
	//print_debug("get mass call");
	float res = this->_offset + this->_sensivity * get_sig();
	//res = Balance::get_sig(); //to remove
	//print_debug("get mass returned mass = " << res);
	return (res);
}

float Balance::get_averaged_mass(int samples)
{
	print_debug("get averaged mass call");
	absolute_time_t begin, end;
	//begin = get_absolute_time();

	float res = 0.0f;
	for (int i = 0; i < samples; i++)
		res = res + (get_mass() / samples);

	//end = get_absolute_time();
	//int64_t elapsed = absolute_time_diff_us (begin, end);
	print_debug("get averaged mass returned");
	//print_debug("Elapsed time: " << elapsed << " us\n";
	return (res);
}

void Balance::set_calibration(float offcet, float sensitivity)
{
	print_debug("set calibration call");
	this->_offset = offcet;
	this->_sensivity = sensitivity;
	_save_calibration();
	print_debug("set calibration return");
}

void	Balance::print_balance_data()
{
	/*
	print_debug("signal : " << get_sig() <<std::endl;
	print_debug("mass : " << get_mass() << "g" <<std::endl;
	print_debug("offcet : " << _offset <<std::endl;
	print_debug("sensitivuty : " << _sensivity <<std::endl;
	*/

	std::cout	<< "signal : " << get_sig() << " / "
				<< "mass : " << get_mass() << "g" << " / "
				<< "offcet : " << _offset << " / "
				<< "sensitivity : " << _sensivity <<std::endl;
}

float Balance::get_sensivity(void)
{
	return (_sensivity);
}

float Balance::get_offset(void)
{
	return (_offset);
}