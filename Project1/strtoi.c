#include <stdio.h>
#include <stdlib.h>

int mystrlen(char* substr)
{
	int i = 0;
	while (*(substr + i) != '\0')
		i++;
	return i;
}

int pow(int x, int n)
{
	if (n == 0)
		return 1;
	else if (n == 1)
		return x;
	else if (n % 2 == 0)
		return pow(x * x, n / 2);
	else
		return pow(x * x, n / 2) * x;
}

int strtoi(const char* str, char** p, int* ret)
{
	char max_str[34] = { '\0' };
	int k = mystrlen(str) - 1, i = 0, sign = 1, index = 0;
	int sos = 10; // Default base is 10
	// Check first symbols for different bases
	if (*str == 'b')
	{
		sos = 2; // binary
		i++;
		k--;
	}
	else if (*str == '0' && *(str + 1) == 'x')
	{
		sos = 16; // hex
		i += 2;
		k -= 2;
	}
	else if (*str == '0')
	{
		sos = 8; // octal
		i++;
		k--;
	}

	// Cycle through the string char by char
	for (i; *(str + i) != '\0'; i++)
	{
		// Handle binary base
		if (sos == 2 && i > 0)
		{
			if (*(str + i) == '-' && i == 1)
			{
				i++;
				k--;
				sign *= -1; // Handle negative numbers
			}
			if (*(str + i) == '0' || *(str + i) == '1')
			{
				*ret += (*(str + i) - '0') * pow(2, k); // Calculate the value
			}
			else
			{
				*p = *(str + i);  // Set p to the invalid char
				return 0;
			}
		}
		// Handle octal base
		else if (sos == 8 && i > 0)
		{
			if (*(str + i) == '-' && i == 1)
			{
				i++;
				k--;
				sign *= -1; // Handle negative numbers
			}
			if (*(str + i) >= '0' && *(str + i) <= '7')
			{
				*ret += (*(str + i) - '0') * pow(8, k); // Calculate the value
			}
			else
			{
				*p = *(str + i);  // Set p to the invalid char
				return 0;
			}
		}
		// Handle hex base
		else if (sos == 16 && i > 1)
		{
			if (*(str + i) == '-' && i == 2)
			{
				i++;
				k--;
				sign *= -1; // Handle negative numbers
			}
			if ((*(str + i) >= '0' && *(str + i) <= '9') || (*(str + i) >= 'A' && *(str + i) <= 'F'))
			{
				if (*(str + i) >= 'A' && *(str + i) <= 'F')
					*ret += (*(str + i) - 'A' + 10) * pow(16, k); // Calculate the value(A-F)
				else
					*ret += (*(str + i) - '0') * pow(16, k); // Calculate the value(0-9)
			}
			else
			{
				*p = *(str + i);  // Set p to the invalid char
				return 0;
			}
		}
		// Handle dec base
		else if ((*(str + i) >= '0' && *(str + i) <= '9') || (*(str + i) == '-' && i == 0))
		{
			if (*(str + i) == '-' && i == 0)
			{
				i++;
				k--;
				sign *= -1; // Handle negative numbers
			}
			*ret += (*(str + i) - '0') * pow(10, k); // Calculate value
		}
		else
		{
			*p = *(str + i);  // Set p to the invalid char
			return 0;
		}
		k--;
	}

	// Handle overflow for binary base
	if (sos == 2)
	{
		// Set the maximum allowed value for binary (all pos is 1)
		if (sign == 1)
		{
			for (int j = 0; j < 32; j++)
			{
				*(max_str + j) = '1';//[31]
			}
		}
		else
		// Set the minimum allowed value for binary 
		{
			index++;
			*max_str = '1';
			for (int j = 1; j < 33; j++)
			{
				*(max_str + j) = '0';//[31]
			}
		}
		// Loop through the input string starting from the third character (after '0b')
		for (int j = 2; *(str + j) != '\0'; j++)
		{
			if (*(str + j) == '0' && (j <= index + 1))
			{
				index++;
				continue; // Skip leading '0's
			}
			if (mystrlen(str) - index - 1 < 32)
				break; // Check for buffer overflow
			if (mystrlen(str) - index - 1 > 32) 
			{
                printf_s("\nBuffer overflow\n");
				return 0; // Check for excessive length
			}
				
			if (*(max_str + j - index ) == '\0')
			{
				printf_s("\nBuffer overflow\n");
				return 0; // Check for excessive length
			}
			if (*(str + j) > *(max_str + j - index - 1))
			{
				printf_s("\nBuffer overflow\n");
				return 0; // Check for exceeding maximum allowed value
			}
		}
	}

	// Handle overflow for octal base
	if (sos == 8)
	{
		// Set the maximum allowed value for positive octal (77777777777)
		if (sign == 1)
		{
			*max_str = '1';
			for (int j = 1; j < 11; j++)
			{
				*(max_str + j) = '7';
			}
		}
		// Set the maximum allowed value for negative octal (-20000000000)
		else 
		{
			*max_str = '2';
			for (int j = 1; j < 11; j++)
			{
				*(max_str + j) = '0';
			}
		}
		// Check for buffer overflow and maximum allowed values
		if (mystrlen(str) >= 12)
		{
			for (int j = 1; *(str + j) != '\0'; j++)
			{   
				if (*(str + j) == '0' && (j <= index+1) || (*(str + j) == '-'))
				{
					index++;
					continue;					
				}
				if (mystrlen(str) - index - 1 < 11)
					break; // Check for buffer overflow
				if (*(max_str + j - index - 1) == '\0')
				{
					printf_s("\nBuffer overflow\n");
					return 0; // Check for buffer overflow
				}
				if (*(str + j) < *(max_str + j - index - 1) && mystrlen(str) - index <= 12)
					break; // Break if the value is within bounds
				if (*(str + j) > *(max_str + j - index - 1))
				{
					printf_s("\nBuffer overflow\n");
					return 0; // Check for exceeding maximum allowed value
				}
			}
		}
	}

	// Handle overflow for hex base
	if (sos == 16)
	{
		// Set the maximum allowed value for positive hexadecimal (0x7FFFFFFFFF)
		if (sign == 1)
		{
			*max_str = '7';
			for (int j = 1; j < 8; j++)
			{
				*(max_str + j) = 'F';
			}
		}
		// Set the maximum allowed value for negative hexadecimal (-0x800000000)
		else
		{
			*max_str = '8';
			for (int j = 1; j < 8; j++)
			{
				*(max_str + j) = '0';
			}
		}
		// Check for buffer overflow and maximum allowed values
		if (mystrlen(str) >= 10)
		{
			for (int j = 2; *(str + j) != '\0'; j++)
			{
				if (*(str + j) == '0' && (j <= index + 2) || *(str + j) == '-')
				{
					index++;
					continue;
				}
				if (mystrlen(str) - index < 10)
					break; // Check for buffer overflow
				if ((*(str + j) < *(max_str + j - index - 2)) && (mystrlen(str) - index <= 10))
					break; // Stop if the value is within bounds
				if (*(max_str + j - 2 - index) == '\0')
				{
					printf_s("\nBuffer overflow\n");
					return 0;  // Check for buffer overflow
				}
				if (*(str + j) > *(max_str + j - 2 - index))
				{
					printf_s("\nBuffer overflow\n");
					return 0; // Check for exceeding maximum allowed value
				}
			}
		}
	}

	// Handle overflow for dec base
	if (sos == 10)
	{
		int flag = 0;
		char* max_int_str = "2147483647", * min_int_str = "2147483648"; // max min dec values
		if (sign == -1)
		{
			max_int_str = min_int_str;
			// Check for buffer overflow and maximum allowed values
			if (mystrlen(str) >= 11)
			{
				for (int j = 0; *(str + j) != '\0'; j++)
				{
					if (*(str + j) == '0' && (j <= index) || *(str + j) == '-')
					{
						if (*(str + j) == '-' && j > 0)
						{
							*p = *(str + i);
							return 0;
						}
						index++;
						continue;
					}
					if (mystrlen(str) - index < 10)
						break; // Check for buffer overflow
					if ((*(str + j) < *(max_int_str + j - index)) && (mystrlen(str) - index <= 10))
						break; // Stop if the value is within bounds
					if (*(max_int_str + j - index) == '\0')
					{
						printf_s("\nBuffer overflow\n");
						return 0; // Check for buffer overflow
					}
					if (*(str + j) > *(max_int_str + j - index))
					{
						printf_s("\nBuffer overflow\n");
						return 0; // Check for exceeding maximum allowed value
					}
				}
			}
		}
		else
		{
			// Check for buffer overflow and maximum allowed values
			if (mystrlen(str) >= 9)
			{
				for (int j = 0; *(str + j) != '\0'; j++)
				{
					if (*(str + j) == '0' && (j <= index) || *(str + j) == '-')
					{
						index++;
						continue;
					}
					if (mystrlen(str) - index < 10)
						break; // Check for buffer overflow
					if ((*(str + j) < *(max_int_str + j - index)) && (mystrlen(str) - index <= 10))
						break; // Stop if the value is within bounds
					if (*(max_int_str + j) == '\0')
					{
						printf_s("\nBuffer overflow\n");
						return 0; // Check for buffer overflow
					}
					if (*(str + j) > *(max_int_str + j))
					{
						printf_s("\nBuffer overflow\n");
						return 0; // Check for exceeding maximum allowed value
					}
				}
			}
		}
	}

	*ret = *ret * sign;
	return 1;
}