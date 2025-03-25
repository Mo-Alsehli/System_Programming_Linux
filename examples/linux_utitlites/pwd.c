#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// Buffer Size Macro
#define SIZE 1024

int main(int argc, char *argv[])
{
	char buff[SIZE];

	if (getcwd(buff, SIZE) == NULL)
	{ // Function returns NULL on Failure.
		printf("ERROR: can't print current working directory\n");
		exit(-1);
	}

	int buffLen = strlen(buff);

	if (write(1, buff, buffLen) < 0)
	{
		printf("ERROR: writing pwd\n");
		exit(-2);
	}
	printf("\n");

	return 0;
}
