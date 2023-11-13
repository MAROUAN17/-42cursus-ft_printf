#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

void    ft_putnbr(long d, int *ptr_c)
{
    if (d < 0)
    {
        ft_putchar('-');
        d = -d;
    }
    if (d >= 10)
    {
        (*ptr_c)++;
        ft_putnbr(d / 10, ptr_c);
        ft_putnbr(d % 10, ptr_c);
    }
    if (d < 10)
    {
        d = d + 48;
        ft_putchar(d);
    }
}

int ft_printf(const char *format, ...)
{
    int             i;
    int             counter;
    unsigned int    ui;
    int             index;
    unsigned long   ul;
    char            c;
    char            *s;
    char            *base;
    unsigned long   *ptr_ul;
    int             z;
    char            hex[50];
    va_list         args;

    index = 0;
    counter = 0;
    z = 0;
    base = "0123456789abcdef";
    va_start(args, format);
    while (*format == '%')
    {
        format++;
        while (*format == 'c')
        {
            c = va_arg(args, int);
            ft_putchar(c);
            counter++;
            format++;
            return (counter);
        }
        while (*format == 'd' || *format == 'i')
        {
            i = va_arg(args, int);
            ft_putnbr(i, &counter);
            format++;
            return (counter + 1);
        }
        while (*format == 's')
        {
            s = va_arg(args, char *);
            while(*s)
            {
                ft_putchar(*s);
                counter++;
                s++;
            }
            format++;
            return (counter);
        }
        while (*format == 'p' || *format == 'x' || *format == 'X')
        { 
            ul = (unsigned long)va_arg(args, void *);
            if (*format == 'p')
            {
                ft_putchar('0');
                ft_putchar('x');
            }
            while(ul != 0)
            {
                index = ul % 16;
                if (*format == 'X' && index >= 10)
                    hex[z] = *(base + index) - 32;
                else
                    hex[z] = *(base + index);
                ul /= 16;
                z++;
                counter++;
            }
            while (z > 0)
            {
                ft_putchar(hex[z - 1]);
                z--;
            }
            format++;
            return (counter);
        }
        while (*format == 'u')
        {
            ui = va_arg(args, unsigned int);
            ft_putnbr(ui, &counter);
            format++;
            return (counter + 1);
        }
        if (*format == '%')
        {
            ft_putchar('%');
            return (1);
        }
    }
    va_end(args);
    return (c);
}

int main()
{
    int str = 9;
    printf("\n%d\n", ft_printf("%X", str));
    // printf("\n%u\n", str);
}