#include "shell.h"

/**
 * eputin - Display the input string to the standard error.
 * @input: The string to be displayed.
 *
 * Return: None.
 */
void eputin(char *input)
{
	int i = 0;

	if (!input)
		return;

	while (input[i] != '\0')
	{
		eputword(input[i]);
		i++;
	}
}

/**
 * eputword - Output the character 'c' to the standard error.
 * @c: The character to be outputted.
 *
 * Return: On success 1.
 *         On error, returns -1 and sets errno accordingly.
 */
int eputword(char c)
{
	static int index;
	static char buffer[WRITE_BUFFER];

	if (c == BUFFER_FLUSHER || index >= WRITE_BUFFER)
	{
		write(2, buffer, index);
		index = 0;
	}

	if (c != BUFFER_FLUSHER)
		buffer[index++] = c;

	return (1);
}

/**
 * putFd - Write the character 'c' to the specified file descriptor 'fd'.
 * @c: The character to be written.
 * @fd: The file descriptor to write to.
 *
 * Return: On success 1.
 *         On error, returns -1 and sets errno accordingly.
 */
int putFd(char c, int fd)
{
	static int index;
	static char buffer[WRITE_BUFFER];

	if (c == BUFFER_FLUSHER || index >= WRITE_BUFFER)
	{
		write(fd, buffer, index);
		index = 0;
	}

	if (c != BUFFER_FLUSHER)
		buffer[index++] = c;

	return (1);
}

/**
 * putsFdk - Write the input string 'str' to the specified file descriptor 'fd'.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 *         On error, returns -1 and sets errno accordingly.
 */
int putsFdk(char *str, int fd)
{
	int count = 0;

	if (!str)
		return (0);

	while (*str)
	{
		count += putFd(*str++, fd);
	}

	return (count);
}

