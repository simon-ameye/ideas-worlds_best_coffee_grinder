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
}

void Balance::_save_calibration(void)
{
	std::cout << "balance : save calibration call" << std::endl;
	std::ofstream dst_stream (CALIBRARION_FILE_NAME);
	if (dst_stream.fail())
	{
		std::cout << "open failure : " << strerror(errno) << '\n';
		std::cout << "File creating fail" << std::endl;
	}
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

unsigned long Balance::get_sig(void)
{
	//std::cout << "balance : get sig call" << std::endl;
	unsigned long sig = _Hx711.ReadCound();
	//std::cout << "balance : get sig returned sig = " << sig << std::endl;
	return (sig);
}

float Balance::get_mass(void)
{
	//std::cout << "balance : get mass call" << std::endl;
	float res = this->_offset + this->_sensivity * Balance::get_sig();
	//res = Balance::get_sig(); //to remove
	//std::cout << "balance : get mass returned mass = " << res << std::endl;
	return (res);
}

float Balance::get_averaged_mass(int samples)
{
	std::cout << "balance : get averaged mass call for " << samples << " samples" << std::endl;
	absolute_time_t begin, end;
	//begin = get_absolute_time();

	float res = 0.0f;
	for (int i = 0; i < samples; i++)
		res = res + (Balance::get_mass() / samples);

	//end = get_absolute_time();
	//int64_t elapsed = absolute_time_diff_us (begin, end);
	std::cout << "balance : get averaged mass returned in " << std::endl;
	//std::cout << "Elapsed time: " << elapsed << " us\n";
	return (res);
}

void Balance::set_calibration(float offcet, float sensitivity)
{
	std::cout << "balance : set calibration call" << std::endl;
	this->_offset = offcet;
	this->_sensivity = sensitivity;
	Balance::_save_calibration();
	std::cout << "balance : set calibration return" << std::endl;
}

void	Balance::print_balance_data()
{
	/*
	std::cout << "signal : " << get_sig() <<std::endl;
	std::cout << "mass : " << get_mass() << "g" <<std::endl;
	std::cout << "offcet : " << _offset <<std::endl;
	std::cout << "sensitivuty : " << _sensivity <<std::endl;
	*/

	std::cout	<< "signal : " << get_sig() << " / "
				<< "mass : " << get_mass() << "g" << " / "
				<< "offcet : " << _offset << " / "
				<< "sensitivity : " << _sensivity << std::endl;
}