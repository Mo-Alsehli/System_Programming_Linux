#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
	
	for(int i = 1; i < argc; i++){
		int argLen = strlen(argv[i]);
		// Print Arguemnts
		if(write(1, argv[i], argLen) < 0){
			printf("ERROR: writing faild!!\n");
			exit(-1);
		}
		// print space to separate between arguments.
		write(1, " ", 1);
	}
	printf("\n");

	return 0;
}
