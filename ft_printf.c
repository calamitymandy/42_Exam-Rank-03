#include <unistd.h>
#include <stdarg.h>
#include <limits.h>
#include <stdio.h>

void	put_str(char *str, int *len)
{
	int i = 0;

	if (!str)
		str = "(null)";
	while (str[i])
	{
		*len += write(1, &str[i], 1);
		i++;
	}
}

void	put_number(long long int number, int base, int *len)
{
	char *hexa = "0123456789abcdef";

	if (number < 0)
	{
		number *= -1;
		*len += write(1, "-", 1);
	}
	if (number >= base)
		put_number((number / base), base, len);
	*len += write(1, &hexa[number % base], 1);
}

int	ft_printf(char *format, ...)
{
	int i = 0;
	int len = 0;
	va_list args;
	va_start(args, format);
	
	while (format[i])
	{
		if ((format[i] == '%') && (format[i + 1] == 'd' || format[i + 1] == 's' || format[i + 1] == 'x'))
		{
			i++;
			if (format[i] == 's')
				put_str(va_arg(args, char *), &len);
			else if (format[i] == 'd')
				put_number(va_arg(args, int), 10, &len);
			else if (format[i] == 'x')
				put_number(va_arg(args, unsigned int), 16, &len);
		}
		else 
			len += write(1, &format[i], 1);
		i++;
	}
	return (va_end(args), len);
}

/*QUIT MAIN
int	main(void)
{
	ft_printf("lets see, it prints: %x ?", UINT_MAX);
	printf("lets see, it prints: %x ?", UINT_MAX);
}
*/

