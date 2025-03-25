#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

// Buffer Size.
#define SIZE	100

int main(int argc, char* argv[]){
	char buff[SIZE];

	if(argc != 3){
		printf("ERROR: arguements \nusage: ./copy path_to_source path_to_distination\n");
		exit(-1);
	}
	
	// Input file descriptor (file to copy dat from).
	int inputFd = open(argv[1], O_RDONLY);
	if(inputFd < 0){
		printf("ERROR: can't open %s file\n", argv[1]);
	      ;exit(-2);
	 }

	// output file descriptor flags (create, write only and truncate).
	int outputFlags = O_CREAT | O_WRONLY | O_TRUNC;
	mode_t filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |S_IROTH | S_IWOTH;
	
	// Output file descriptor.
	int outputFd = open(argv[2], outputFlags, filePerms);

	if(outputFd < 0){
		printf("ERROR: can't open %s file\n", argv[2]);
		exit(-3);
	}

	int numRead;
	while((numRead = read(inputFd, buff, SIZE)) > 0){
		if(write(outputFd, buff, numRead) != numRead){
			printf("ERROR: couldn't write whole buffer\n");
			exit(-4);
		}
	}

	// close input and output files.
	close(inputFd);
	close(outputFd);

	return 0;

}


