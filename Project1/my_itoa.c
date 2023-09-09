#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int my_itoa(char* buf, int bufSize, int value, int sysnum)
{
	int tmp = value, numOfSymbols = 0, i, length, nullflag = 0, errbufSizeflag = 0;
	unsigned v = (unsigned)value; // Use an unsigned version of the value for positive representation

	if (buf == NULL)
		nullflag = 1; // Check if the buffer pointer is NULL

	char str1[32] = { '\0' } ; // Initialize a character array to store the converted string
	char* str2 = str1;  // Pointer to the current position in str1

	if (sysnum == 10 && value < 0)
		v = -value; // For base 10 and negative value, use the absolute value

	// Convert the value to the specified base (sysnum)
	while (v)
	{
		if (str2 - str1 > bufSize) // Check if the buffer size is insufficient
			errbufSizeflag = 1;
		i = v % sysnum;
		v /= sysnum;
		if (i < 10)
			*str2++ = i + '0'; // Convert to a character and store in str1
		else if (i < 36)
			*str2++ = i + 'a' - 10;
		else
			*str2++ = i + 'A' - 36;
	}

	length = str2 - str1; // Calculate the length of the converted string

	if (sysnum == 10 && value < 0)
	{
		*buf++ = '-'; // Add a minus sign for negative values in base 10
		length++;
	}

	// Copy the converted string to the output buffer in reverse order
	while ((str2 > str1) && !nullflag && !errbufSizeflag)
		*buf++ = *--str2;

	if (errbufSizeflag)
		printf_s("\nIncorrect bufferSize!\n"); // Handle buffer size error
	if (nullflag) 
	{
		printf_s("\nBuf = NULL\n"); // Handle NULL buffer pointer
		return length;
	}
	return 1;
}