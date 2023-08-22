#include "main.h"

/**
 * handle_unknown_format - Handles printing for unknown format specifier
 * @fmt: Formatted string in which to print the arguments.
 * @ind: Pointer to the current index in the format string.
 * @unknow_len: Length of unknown characters printed.
 *
 * Return: Total number of characters printed.
 */
int handle_unknown_format(const char *fmt, int *ind, int unknow_len)
{
	unknow_len += write(1, "%%", 1);
	if (fmt[*ind - 1] == ' ')
		unknow_len += write(1, " ", 1);
	else
	{
		--(*ind);
		while (fmt[*ind] != ' ' && fmt[*ind] != '%')
			--(*ind);
		if (fmt[*ind] == ' ')
			--(*ind);
		return (1);
	}
	unknow_len += write(1, &fmt[*ind], 1);
	return (unknow_len);
}

/**
 * handle_known_format - Handles printing for known format specifier
 * @fmt: Formatted string in which to print the arguments.
 * @ind: Pointer to the current index in the format string.
 * @list: List of arguments to be printed.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags.
 * @width: Width of the field.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: Number of characters printed by the corresponding function.
 */
int handle_known_format(const char *fmt, int *ind, va_list list,
	char buffer[], int flags, int width, int precision, int size)
{
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	int i;

	for (i = 0; fmt_types[i].fmt != '\0'; i++)
	{
		if (fmt[*ind] == fmt_types[i].fmt)
		{
			return fmt_types[i].fn(list, buffer, flags, width, precision, size);
		}
	}

	return handle_unknown_format(fmt, ind, 0);
}

/**
 * handle_print - Prints an argument based on its type
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: Pointer to the current index in the format string.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags.
 * @width: Width of the field.
 * @precision: Precision specification.
 * @size: Size specifier.
 *
 * Return: Total number of characters printed.
 */
int handle_print(const char *fmt, int *ind, va_list list,
	char buffer[], int flags, int width, int precision, int size)
{
	return handle_known_format(fmt, ind, list, buffer, flags, width, precision, size);
}
