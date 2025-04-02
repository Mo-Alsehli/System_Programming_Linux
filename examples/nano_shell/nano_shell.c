#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

// New type for shell local variables represented as a key and value.
typedef struct
{
  char *key;
  char *value;
} shellLocalVar;

extern char **environ;		// Global environment variables

// Function declarations.
void tokenize (shellLocalVar * localVars[], char buff[], char *argArr[]);
void echo (char *args[]);
void pwd (char currentDir[]);
int addLocalVar (shellLocalVar * localVars[], shellLocalVar * newVar);
int searchLocalVar (shellLocalVar * arr[], char *key);
char *getEnvVarValue (const char *key);


#define SIZE	256


// Main function.
int
main (int argc, char **argv)
{

  char buff[SIZE];
  char currentDir[SIZE];
  int status;
  char *argArr[100];
  shellLocalVar *localVars[100] = { NULL };
  shellLocalVar currVar;


  // Main loop.
  while (1)
    {
      pwd (currentDir);
      printf ("\033[1;31m%s@Nano_shell:\033[0m \033[36m%s\033[0m $ ",
	      getEnvVarValue ("USER"), currentDir);
      fgets (buff, SIZE, stdin);
//              buff[strlen(buff)-1] = 0; // replace the '\n' character with null terminator.

      tokenize (localVars, buff, argArr);	// tokanize user input line.
      if (strlen (buff) == 0)
	continue;


      char *equalSign = strchr (argArr[0], '=');

      // Built-in commands and new process creation (linux native commands).
      if (strcmp (argArr[0], "echo") == 0)
	{
	  echo (argArr);
	}
      else if (strcmp (argArr[0], "pwd") == 0)
	{
	  printf ("%s\n", currentDir);
	}
      else if (strcmp (argArr[0], "cd") == 0)
	{
	  // Note: chdir() function only accepts path starting with '/'.
	  if (chdir (argArr[1]) < 0)
	    {
	      exit (-1);
	    }
	}
      else if (strcmp (argArr[0], "exit") == 0)
	{
	  exit (0);
	}
      else if ((argArr[1] == NULL) && (equalSign != NULL))
	{
	  // Local Variables
	  int i = 0;
	  int keyLen = equalSign - argArr[0];
	  currVar.key = (char *) malloc (sizeof (char) * (keyLen + 1));
	  strncpy (currVar.key, argArr[0], keyLen);
	  currVar.key[keyLen] = '\0';

	  int valueLen = strlen (equalSign + 1);
	  currVar.value = (char *) malloc (sizeof (char) * (valueLen + 1));
	  strcpy (currVar.value, equalSign + 1);


	  if (addLocalVar (localVars, &currVar) != 0)
	    {
	      printf ("Local Var Not Added!!\n");
	    }

	}
      else if (strcmp (argArr[0], "export") == 0)
	{
	  char *equalSign = strchr (argArr[1], '=');
	  if (equalSign == NULL)
	    {
	      printf ("ERROR: can't create empty variable\n");
	      printf ("usage: export varName=\"value\"\n");
	    }
	  else
	    {
	      const char *value = equalSign + 1;
	      int keyLen = equalSign - argArr[1];
	      char *name = (char *) malloc (sizeof (char) * (keyLen) + 1);
	      name = strncpy (name, argArr[1], keyLen);
	      name[keyLen] = '\0';
	      setenv (name, value, 1);
	    }
	}
      else if (strcmp (argArr[0], "unset") == 0)
	{
	  unsetenv (argArr[1]);
	}
      else
	{
	  pid_t child_pid = fork ();
	  if (child_pid == 0)
	    {
	      //char *argv[] = { NULL };
	      //char *envp[] = { NULL };
	      execvp (argArr[0], argArr);	// Supports program execution directly (check `man exec`).
	      printf ("ERROR: Process creation faild!!\n");
	      exit (-1);
	    }
	  else if (child_pid > 0)
	    {
	      wait (&status);
	      //printf
	      ("PARENT: I'm %d, and my child returned with a status: %d\n",
	       getpid (), WEXITSTATUS (status));
	    }
	  else
	    {
	      printf ("ERROR: can't create process\n");
	      exit (-1);
	    }
	}

    }

  // Memory de-allocation.
  int i = 0;
  free (currVar.key);
  free (currVar.value);
  while (argArr[i] != NULL)
    {
      free (argArr[i]);
      i++;
    }

  return 0;
}

// Helper Functions for local Varibles manipulation
// Add new local Variable Function Definition.

int
addLocalVar (shellLocalVar *localVars[], shellLocalVar *newVar)
{
  int i = 0;
  int index = searchLocalVar (localVars, newVar->key);
  if (index == -1)
    {
      while (localVars[i] != NULL && i < 100)
	{
	  i++;
	}
      if (i >= 100)
	{
	  return -1;
	}

      if ((localVars[i] =
	   (shellLocalVar *) malloc (sizeof (shellLocalVar))) == NULL)
	{
	  return -1;
	}


      localVars[i]->key = strdup (newVar->key);
      localVars[i]->value = strdup (newVar->value);

      if (localVars[i]->key == NULL || localVars[i]->value == NULL)
	{
	  free (localVars[i]->key);
	  free (localVars[i]->value);
	  free (localVars[i]);
	  return -1;
	}

      if (i + 1 < 100)
	{
	  localVars[i + 1] = NULL;
	}

      return 0;
    }
  else
    {
      free (localVars[index]->value);
      localVars[index]->value = strdup (newVar->value);
      if (localVars[index]->value == NULL)
	{
	  return -1;
	}
      return 0;
    }

  return -1;			// shouldn't reach here.
}

int
searchLocalVar (shellLocalVar *arr[], char *key)
{
  int i = 0;
  while (arr[i] != NULL && i < 100)
    {
      if (strcmp (arr[i]->key, key) == 0)
	{
	  return i;
	}
      i++;
    }

  return -1;
}

// Function to search for a variable in environment variables
char *
getEnvVarValue (const char *key)
{
  if (key == NULL)
    return NULL;

  for (char **env = environ; *env != NULL; env++)
    {
      char *equal_sign = strchr (*env, '=');
      if (equal_sign != NULL)
	{
	  size_t key_len = equal_sign - *env;
	  if (strncmp (*env, key, key_len) == 0 && key[key_len] == '\0')
	    {
	      return equal_sign + 1;
	    }
	}
    }
  return NULL;
}


// Command line parsing function definition.
void
tokenize (shellLocalVar *localVars[], char buff[], char *argArr[])
{
  int i = 0, j = 0, count = 0;

  // Remove trailing newline from fgets()
  size_t len = strlen (buff);
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
	break;			// If only spaces are left, stop

      i = j;			// Start of word

      // Find the end of the word
      while (buff[j] != ' ' && buff[j] != '\0')
	j++;


      // Only allocate if we have a non-empty token
      if (j > i)
	{

	  int tokenLen = j - i;
	  char *token = malloc (tokenLen + 1);
	  if (token == NULL)
	    {
	      perror ("Memory allocation faild");
	      exit (EXIT_FAILURE);
	    }
	  // Copy the word
	  strncpy (token, buff + i, tokenLen);
	  token[tokenLen] = '\0';

	  if (token[0] == '$')
	    {
	      char *key = token + 1;
	      char *value = NULL;
	      int index;

	      if ((index = searchLocalVar (localVars, key)) != -1)
		{
		  value =
		    (char *) malloc (sizeof (char) *
				     strlen (localVars[index]->value));
		  strcpy (value, localVars[index]->value);
		}

	      if (value == NULL)
		{
		  value = getEnvVarValue (key);
		}

	      if (value != NULL)
		{
		  free (token);
		  token = strdup (value);
		  if (token == NULL)
		    {
		      perror ("Memory allocation faild");
		      exit (EXIT_FAILURE);
		    }
		}
	      else
		{
		  token = " ";
		}
	    }
	  argArr[count++] = token;

	}
      // Skip spaces between words
      while (buff[j] == ' ')
	j++;
    }

  argArr[count] = NULL;		// Null-terminate the array
}

// built-in `echo` command function definition.
void
echo (char *args[])
{
  int i = 1;
  while (args[i] != NULL)
    {
      int argLen = strlen (args[i]);
      // Print Arguemnts
      if (write (1, args[i], argLen) < 0)
	{
	  printf ("ERROR: writing faild!!\n");
	  exit (-1);
	}
      // print space to separate between arguments.
      write (1, " ", 1);
      i++;
    }
  printf ("\n");

}


// built-in `pwd` command function defintion.
void
pwd (char currentDir[])
{
  char buff[SIZE];

  if (getcwd (buff, SIZE) == NULL)
    {				// Function returns NULL on Failure.
      printf ("ERROR: can't print current working directory\n");
      exit (-1);
    }

  int buffLen = strlen (buff);

  strcpy (currentDir, buff);
}
