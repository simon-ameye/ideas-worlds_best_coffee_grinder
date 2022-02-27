/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hx711.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sameye <sameye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:08:27 by sameye            #+#    #+#             */
/*   Updated: 2022/02/27 19:24:04 by sameye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Hx711.hpp"

Hx711::Hx711(void)
{
	gpio_init(PD_SCK_GPIO);
	gpio_set_dir(PD_SCK_GPIO, GPIO_OUT);
	gpio_put(PD_SCK_GPIO, 0);

	gpio_init(DOUT_GPIO);
	gpio_set_dir(DOUT_GPIO, GPIO_IN);
}

unsigned long Hx711::ReadCound(void)
{
	unsigned long Count;
	unsigned char i;
	//ADD0 = 1;
	//ADSK = 0;
	Count = 0;
	while (gpio_get(DOUT_GPIO)); //DOUT stays high while data is not ready for retrieval
	usleep(T1); //Here, sleep T1
	for (i = 0; i < 24; i++) //data is encoded on 24 bits
	{
		gpio_put(PD_SCK_GPIO, 1); //ADSK = 1;
		usleep(T3); //Here, sleep T3
		Count = Count << 1;
		if (gpio_get(DOUT_GPIO)) //if (ADD0)
			Count++;
		gpio_put(PD_SCK_GPIO, 0); //ADSK = 0;
		usleep(T4); //Here, sleep T4
	} //25th PD_SDK pulse will pull DOUT back to high
	gpio_put(PD_SCK_GPIO, 1); //ADSK = 1;
	usleep(T3); //Here, sleep T4
	Count = Count ^ 0x800000;
	gpio_put(PD_SCK_GPIO, 0); //ADSK = 0;
	usleep(T4); //Here, sleep T4
	if (GAIN == 64) //maybe send 0-1-2 more blinks ?
	{
		gpio_put(PD_SCK_GPIO, 1); //ADSK = 1;
		usleep(T3);
		gpio_put(PD_SCK_GPIO, 0); //ADSK = 1;
		usleep(T4);
		gpio_put(PD_SCK_GPIO, 1); //ADSK = 1;
		usleep(T3);
		gpio_put(PD_SCK_GPIO, 0); //ADSK = 1;
		usleep(T4);
	}
	return (Count);
}
