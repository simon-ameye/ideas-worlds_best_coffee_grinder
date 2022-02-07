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

Balance::Balance(void)
{
	Balance::_recover_calibraton();
}

void Balance::_save_calibration(void)
{
	std::string dst_file = CALIBRARION_FILE_NAME;
	std::ofstream	dst_stream(dst_file.c_str(), std::ios_base::binary);
	if (dst_stream.fail())
		std::cout << "File creating fail" << std::endl;
	else
	{
		std::cout << "Writing calibration file" << std::endl;
		dst_stream.write((char *)&(this->_offset), sizeof(float));
		dst_stream.write((char *)&(this->_sensivity), sizeof(float));
		dst_stream.close();
	}
}

void Balance::_recover_calibraton(void)
{
	std::string dst_file = CALIBRARION_FILE_NAME;
	std::ifstream	src_stream(dst_file.c_str(), std::ios_base::binary);
	if (src_stream.fail())
	{
		std::cout << "File reading fail. Saving default values" << std::endl;
		this->_offset = DEFAULT_OFFSET;
		this->_sensivity = DEFAULT_SENSITIVITY;
		Balance::_save_calibration();
	}
	else
	{
		std::cout << "Reading calibration file" << std::endl;
		src_stream.read((char *)&(this->_offset), sizeof(float));
		src_stream.read((char *)&(this->_sensivity), sizeof(float));
		src_stream.close();
	}
}

float Balance::get_sig(void)
{
	//get the raw sig
	return (2.0);
}

float Balance::get_mass(void)
{
	return (this->_offset + this->_sensivity * Balance::get_sig());
}

void Balance::set_calibration(float offcet, float sensitivity)
{
	this->_offset = offcet;
	this->_sensivity = sensitivity;
	Balance::_save_calibration();
}
