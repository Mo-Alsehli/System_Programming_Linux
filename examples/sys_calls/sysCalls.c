#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	// Replacing the printf with the System Call Function from linux.
	//printf("Hello Linux");
	// For more information check the manual for the write function "man write".
	if(write(1, "hello linux\n", strlen("hello linux\n")) < 0)
		exit(-1);
	return 0;

}
