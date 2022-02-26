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

//Simon Ameye adapted driver for PICO from reference driver available at https://cdn.sparkfun.com/datasheets/Sensors/ForceFlex/hx711_english.pdf

//25 clock pulses - select A channel with gain = 128 // default
//26 clock pulses - select B channel with gain = 32 //Do not use
//27 clock pulses - select A channel with gain = 64 //Maybe

//T1 DOUT falling edge to PD_SCK rising edge min 0.1 µs
//T2 PD_SCK rising edge to DOUT data ready max 0.1 µs
//T3 PD_SCK high time min 0.2, typ 1, max 50 µs
//T4 PD_SCK low time min 0.2 typ 1 µs

//T1 = 0.1us
//T2 = 0.1us
//T3 = 1us
//T4 = 1us

//sbit ADDO = P1^5;
//sbit ADSK = P0^0;
static unsigned long ReadCound(void)
{
	unsigned long Count;
	unsigned char i;
	//ADD0 = 1;
	//ADSK = 0;
	Count = 0;
	//while (ADD0); //DOUT stays high while data is not ready for retrieval
	//Here, sleep T1
	for (i = 0; i < 24; i++) //data is encoded on 24 bits
	{
		//ADSK = 1;
		//Here, sleep T3
		Count = Count << 1;
		//if (ADD0)
		//	Count++;
		//ADSK = 0;
		//Here, sleep T4
	} //25th PD_SDK pulse will pull DOUT back to high
	//ADSK = 1;
	Count = Count ^ 0x800000;
	//ADSK = 0;
	//maybe send 0-1-2 more blinks ?
	return (Count);
}

float Balance::get_sig(void)
{
	std::cout << "balance : get sig call" << std::endl;


	std::cout << "balance : get sig return" << std::endl;
	return (42);
}

float Balance::get_mass(void)
{
	std::cout << "balance : get mass call" << std::endl;
	float res = this->_offset + this->_sensivity * Balance::get_sig();
	std::cout << "balance : get mass return" << std::endl;
	return (2);
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
