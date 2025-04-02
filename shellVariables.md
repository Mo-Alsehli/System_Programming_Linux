# Shell Variables in Linux

Shell variables are an essential part of working with the Linux shell. They are used to store data that can be referenced and manipulated during a shell session. Shell variables can be categorized into two main types: **local variables** and **environment variables**.

## Local Variables

Local variables are defined within the shell and are only accessible in the current shell session or script. They are not passed to child processes or subshells. Local variables are typically used for temporary data storage during a script's execution.

### Example:

```bash
# Define a local variable
my_var="Hello, World!"

# Access the variable
echo $my_var
```

In this example, `my_var` is a local variable that exists only in the current shell session.

## Environment Variables

Environment variables are a special type of shell variable that are inherited by child processes. They are used to configure the behavior of the shell and other programs. Common environment variables include `PATH`, `HOME`, and `USER`.

### Example:

```bash
# Display the value of an environment variable
echo $PATH

# Set a new environment variable
export MY_ENV_VAR="Linux Programming"

# Access the environment variable
echo $MY_ENV_VAR
```

Here, `MY_ENV_VAR` is an environment variable that can be accessed by the current shell and any child processes.

### Key Differences Between Local and Environment Variables

| Feature     | Local Variables                  | Environment Variables                  |
| ----------- | -------------------------------- | -------------------------------------- |
| Scope       | Current shell session or script  | Current shell and child processes      |
| Inheritance | Not inherited by child processes | Inherited by child processes           |
| Usage       | Temporary data storage           | Configuration and system-wide settings |

## Managing Variables

- **Declaring a variable**: Use the syntax `variable_name=value` (no spaces around `=`).
- **Exporting a variable**: Use the `export` command to make a local variable an environment variable.
- **Unsetting a variable**: Use the `unset` command to remove a variable.

### Example:

```bash
# Declare a local variable
local_var="Temporary Data"

# Export it as an environment variable
export local_var

# Unset the variable
unset local_var
```

Understanding and managing shell variables effectively can significantly enhance your productivity and control over the Linux environment.
