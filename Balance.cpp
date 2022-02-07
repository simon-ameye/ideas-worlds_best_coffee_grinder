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
	std::cout << "balance : constructor call" << std::endl;
	Balance::_recover_calibraton();
	this->_sig_0_simulator_of_load = clock();
}

void Balance::_save_calibration(void)
{
	std::cout << "balance : save calibration call" << std::endl;
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
	std::cout << "balance : save calibration return" << std::endl;
}

void Balance::_recover_calibraton(void)
{
	std::cout << "balance : recover calibration call" << std::endl;
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
	std::cout << "balance : recover calibration return" << std::endl;
}

float Balance::get_sig(void)
{
	std::cout << "balance : get sig call" << std::endl;
	//get the raw sig
	float res = this->_sig_0_simulator_of_load;
	std::cout << "balance : get sig return" << std::endl;
	return (res);
}

float Balance::get_mass(void)
{
	std::cout << "balance : get mass call" << std::endl;
	std::cout << "balance : get mass return" << std::endl;
	return (this->_offset + this->_sensivity * Balance::get_sig());
}

void Balance::set_calibration(float offcet, float sensitivity)
{
	std::cout << "balance : set calibration call" << std::endl;
	this->_offset = offcet;
	this->_sensivity = sensitivity;
	Balance::_save_calibration();
	std::cout << "balance : set calibration return" << std::endl;
}
