#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define CONT 100 // count macro for read buffer.

int main(int argc, char *argv[])
{

	char buff[CONT];
	if (argc != 2)
	{
		printf("ERROR: too few arguments!!\nUsage: %s file-name\n", argv[0]);
		exit(-1);
	}

	int fd = open(argv[1], O_RDONLY);

	if (fd < 0)
	{
		printf("ERROR: couldn't open a file!!\n");
		exit(-2);
	}

	int numread;

	while ((numread = read(fd, buff, CONT)) > 0)
	{
		if (write(1, buff, numread) < 0)
		{
			printf("ERROR: write faild!!\n");
			exit(-3);
		}
	}

	close(fd);
	return 0;
}
