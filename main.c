#include "libftprintf.h"
#include <stdio.h>

int	main(void)
{
	char *test = "Hello";
	ft_printf("Hello, %d\n", 77);
	ft_printf("ft_printf :%p:\n", test);
	printf("printf :%p:\n", test);
	return 0;
}
