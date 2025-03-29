#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define  SIZE	512

int main(){
	char buff[SIZE];
	char* message = "Please Enter a Command $ ";
	if(write(1, message, strlen(message)) < 0){
		printf("ERROR: writing faild\n");
		exit(-1);
	}

	int numRead = read(0, buff, SIZE);
	if(numRead > 0){
		while(strncmp(buff, "exit\n", numRead) != 0){
			if(strncmp(buff, "echo\n", numRead) == 0){
				if((numRead = read(0, buff, SIZE)) < 0){
					printf("ERROR: reading faild\n");
					exit(-2);
				}
				if((write(1, buff, numRead)) < 0){
					printf("ERROR: writing faild\n");
					exit(-3);
				}				
			}else {
				printf("Invalid Command\n");
			}
			if((write(1, message, strlen(message))) < 0){
				printf("ERROR: writing faild\n");
				exit(-4);
			}
			if((numRead = read(0, buff, SIZE)) < 0){
				printf("ERROR: reading faild\n");
				exit(-5);
			}
		}
	}else {
		printf("ERROR: reading faild\n");
		exit(-6);
	}
	write(1, "Good Bye :)\n", 12);
	return 0;
}	
