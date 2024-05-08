#include <unistd.h>
#include <stdarg.h>
#include <limits.h>

void    put_str(char *str, int *len)
{
    int i = 0;
    if (!str)
        str = "(null)";
    while (str[i])
        *len += write (1, &str[i++], 1);
}

void    put_number(long long int number, int base, int *len)
{
    char    *hexa = "0123456789abcdef";

    if (number < 0)
    {
        number *= -1;
        *len += write (1, "-", 1);
    }
    if (number >= base)
        put_number((number / base), base, len);
    *len += write (1, &hexa[number % base], 1);
}

int ft_printf(const char *format, ...)
{
    int i = 0;
    int len = 0;

    va_list args;
    va_start(args, format);
    while (format[i])
    {
        if(format[i] == '%' && (format[i + 1] == 's' || format[i + 1] == 'd' || format[i + 1] == 'x'))
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
            len += write (1, &format[i], 1);
        i++;
    }
    return (va_end(args), len);
}


int main(void)
{
    ft_printf("simple petit test\n");
    ft_printf("%s\n", "test string normal");
    ft_printf("%s\n", NULL);
    ft_printf("%d\n", 10);
    ft_printf("%d\n", INT_MIN);
    ft_printf("%x\n", UINT_MAX);
    ft_printf("%x\n", 15);
    ft_printf("Magic %s is %d\n", "number", 42);
    ft_printf("Hexadecimal for %d is %x\n", 42, 42);
}
