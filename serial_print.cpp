#include "serial_print.hpp"

void serial_print_init(void)
{
	stdio_init_all();
	printf("serial print initialized\n");
}