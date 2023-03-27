#include "main.h"

/**
 * print_unsigned - prints unsigned nos.
 * @buffer: buffer array to handle print
 * @flags: calculates flags that are active
 * @types: arguments list
 * @width: gets width
 * @size: specify size
 * @precision: specifies precision
 * Return: no. of chars printed
 */

int print_unsigned(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '\0';
	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num = num / 10;
	}
	i++;
	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**
 * print_octal - prints an unsigned no. in Octal
 * @buffer: buffer array handles print
 * @types: arg. list
 * @width: get width
 * @flags: active flag calculator
 * @precision: specify precision
 * @size: specify size
 * Return: No. of printed chars
 */

int print_octal(va_list types, char buffer[], int flags, int width, int precision, int size)

{
	int i = BUFF_SIZE - 2;
        unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

        num = convert_size_unsgnd(num, size);

        if (num == 0)
                buffer[i--] = '0';
        buffer[BUFF_SIZE - 1] = '\0';
        
        while (num > 0)
        {       
                buffer[i--] = (num % 8) + '0';
                num = num / 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[i--] = '0';
	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**
 * print_hexadecimal - prints an unsigned no. in hexadecimal notation
 * @buffer: buffer array handles print
 * @types: arg. list
 * @width: get width
 * @flags: active flag calculator
 * @precision: specify precision
 * @size: specify size
 * Return: No. of printed chars
 */

int print_hexadecimal(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer, flags, 'x', width, precision, size));
}

/**
 * print_hexa_upper - prints an unsigned number in upper hexadecimal
 * @buffer: buffer array handles print
 * @types: arg. list
 * @width: get width
 * @flags: active flag calculator
 * @precision: specify precision
 * @size: specify size
 * Return: No. of printed chars
 */

int print_hexa_upper(va_list types, char buffer[], int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer, flags, 'X', width, precision, size));
}

/**
 * print_hexa - prints hexadecimal no. in lower/upper
 * @types: arg. list
 * @map_to: array of values to map no. to
 * @buffer: buffer array that handles print
 * @flags: active flag calculator
 * @flag_ch: calculate active flags
 * @width: get width
 * @precision: specify precision
 * @size: specify size
 * @size: 
 * Return: No. of printed char
 */

int print_hexa(va_list types, char map_to[], char buffer[], int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
        unsigned long int num = va_arg(types, unsigned long int);
        unsigned long int init_num = num;

        UNUSED(width);

        num = convert_size_unsgnd(num, size);

        if (num == 0)
                buffer[i--] = '0';
        buffer[BUFF_SIZE - 1] = '\0';

        while (num > 0)
        {
                buffer[i--] = map_to(num % 16);
                num = num / 16;
        }

        if (flags & F_HASH && init_num != 0)
	{
                buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

        i++;

        return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
