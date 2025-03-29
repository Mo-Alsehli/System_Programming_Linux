#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

// Function declarations.
void tokenize(char buff[], char *argArr[]);
void echo(char *args[]);
void pwd(char currentDir[]);

#define SIZE 256

// Main function.
int main(int argc, char **argv)
{

	char buff[SIZE];
	char currentDir[SIZE];
	int status;
	char *argArr[100];

	// Main loop.
	while (1)
	{
		pwd(currentDir);
		// print shell prompt with current working directory.
		// Note: \033[1;31m is for red color, \033[0m is for reset color.
		// Note: \033[36m is for cyan color.
		// Note: \033[0m is for reset color.
		printf("\033[1;31mMM@Pico_shell:\033[0m \033[36m%s\033[0m $ ", currentDir);
		fgets(buff, SIZE, stdin);
		//              buff[strlen(buff)-1] = 0; // replace the '\n' character with null terminator.

		tokenize(buff, argArr); // tokanize user input line.
		if (strlen(buff) == 0)
			continue;

		// Built-in commands and new process creation (linux native commands).
		if (strcmp(argArr[0], "echo") == 0)
		{
			echo(argArr);
		}
		else if (strcmp(argArr[0], "pwd") == 0)
		{
			printf("%s\n", currentDir);
		}
		else if (strcmp(argArr[0], "cd") == 0)
		{
			// Note: chdir() function only accepts path starting with '/'.
			if (chdir(argArr[1]) < 0)
			{
				exit(-1);
			}
		}
		else if (strcmp(argArr[0], "exit") == 0)
		{
			exit(0);
		}
		else
		{
			pid_t child_pid = fork();
			if (child_pid == 0)
			{
				// char *argv[] = { NULL };
				// char *envp[] = { NULL };
				execvp(argArr[0], argArr); // Supports program execution directly (check `man exec`).
				printf("ERROR: Process creation faild!!\n");
				exit(-1);
			}
			else if (child_pid > 0)
			{
				wait(&status);
				// printf
				("PARENT: I'm %d, and my child returned with a status: %d\n", getpid(), WEXITSTATUS(status));
			}
			else
			{
				printf("ERROR: can't create process\n");
				exit(-1);
			}
		}
	}

	// Memory de-allocation.
	int i = 0;
	while (argArr[i] != NULL)
	{
		free(argArr[i]);
		i++;
	}

	return 0;
}

// Command line parsing function definition.
void tokenize(char buff[], char *argArr[])
{
	int i = 0, j = 0, count = 0;

	// Remove trailing newline from fgets()
	size_t len = strlen(buff);
	if (len > 0 && buff[len - 1] == '\n')
	{
		buff[len - 1] = '\0';
	}

	while (buff[j] != '\0')
	{
		// Skip leading spaces
		while (buff[j] == ' ')
			j++;

		if (buff[j] == '\0')
			break; // If only spaces are left, stop

		i = j; // Start of word

		// Find the end of the word
		while (buff[j] != ' ' && buff[j] != '\0')
			j++;

		// Only allocate if we have a non-empty token
		if (j > i)
		{
			argArr[count] = (char *)malloc((j - i + 1) * sizeof(char));
			if (argArr[count] == NULL)
			{
				perror("Memory allocation failed");
				exit(EXIT_FAILURE);
			}
			// Copy the word
			strncpy(argArr[count], buff + i, j - i);
			argArr[count][j - i] = '\0'; // Null-terminate the copied string
			count++;
		}
		// Skip spaces between words
		while (buff[j] == ' ')
			j++;
	}

	argArr[count] = NULL; // Null-terminate the array
}

// built-in `echo` command function definition.
void echo(char *args[])
{
	int i = 1;
	while (args[i] != NULL)
	{
		int argLen = strlen(args[i]);
		// Print Arguemnts
		if (write(1, args[i], argLen) < 0)
		{
			printf("ERROR: writing faild!!\n");
			exit(-1);
		}
		// print space to separate between arguments.
		write(1, " ", 1);
		i++;
	}
	printf("\n");
}

// built-in `pwd` command function defintion.
void pwd(char currentDir[])
{
	char buff[SIZE];

	if (getcwd(buff, SIZE) == NULL)
	{ // Function returns NULL on Failure.
		printf("ERROR: can't print current working directory\n");
		exit(-1);
	}

	int buffLen = strlen(buff);

	strcpy(currentDir, buff);
}
