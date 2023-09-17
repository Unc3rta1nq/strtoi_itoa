#include <stdio.h>
#include <stdlib.h>
#include "my_itoa.h"
#include "strtoi.h"

int main(void)	
{
	int ret = 0, bufSize = 9, value = 1, opnum = 0, sysnum = 10, result = 1;
	char* string = "b10000000000000000ddd00000000000000"; // String for strtoi
	char* buf = (char*)calloc(bufSize, sizeof(char));
	char* p = NULL;

	printf_s("Enter number of operation:\n1)str to int\n2)int to str\n");
	scanf_s("%d", &opnum);
	switch (opnum)
	{
	case 1:
		if (strtoi(string, &p, &ret) == 1)
			printf_s("str to int: \'%s\' -> \'%d\'\n", string, ret);

		else if (p != NULL)
			printf_s("String: '%s'\nUnknown symbol: '%c'\n", string, p);

		break;
	case 2:
		printf_s("Enter value: ");
		scanf_s("%d", &value);
		printf_s("\nEnter the number system [2,62]: ");
		scanf_s("%d", &sysnum);

		if (!(sysnum >= 2 && sysnum <= 62))
		{
			printf_s("Incorrect number of system!\n");
			return -1;
		}

		result = my_itoa(buf, bufSize, value, sysnum);

		if (result == 1)
		    printf_s("\nint to str: \'%d\' -> \'%s\'\n", value, buf);

		else 
			printf_s("\nRequired bufSIze - %d symbols\n", result);

		break;

	default:

		printf_s("Incorrect number of operation!\n");
		return -1;
	}

	return 0;
}