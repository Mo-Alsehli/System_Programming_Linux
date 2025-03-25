#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

// Buffer size macro.
#define SIZE	100

int main(int argc, char* argv[]){
	char buff[SIZE];

	if(argc != 3){
		printf("ERROR: wrong arguments\nusage: ./move source destination\n");
		exit(-1);
	}

	int inputFd = open(argv[1], O_RDONLY);

	if(inputFd < 0){
		printf("ERROR: can't open %s file!!\n", argv[1]);
		exit(-2);
	}

	int outputFlags = O_CREAT | O_WRONLY | O_TRUNC;
	mode_t filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |S_IROTH | S_IWOTH;

	int outputFd = open(argv[2], outputFlags, filePerms);
	if(outputFd < -1){
		printf("ERROR: can't open %s file!!\n", argv[2]);
		exit(-3);
	}

	int numRead;
	while((numRead = read(inputFd, buff, SIZE)) > 0){
		if(write(outputFd, buff, numRead) != numRead){
			printf("ERROR: writing on file %s !!\n", argv[2]);
			exit(-4);
		}
	}

	close(inputFd);
	close(outputFd);
	// Remove the file after coping its contents to the destination.
	remove(argv[1]);

	return 0;

}



