#include <errno.h>
#include <ft_stdio.h>
#include <ft_stdlib.h>
#include <ft_string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define FTSH_TOK_BUFSIZE 64
#define FTSH_TOK_DELIM "\t\n\v\f\r "

/**
 * Executes given binary/builtin
 */
int
sh_exec(char **argv)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(argv[0], argv) == -1)
			perror(NULL);
		exit(errno);
	}
	else if (pid < 0)
	{
		perror(NULL);
	}
	else
	{
		do
			wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}

/**
 * Splits input into arguments
 */
char
**sh_split(char *line)
{
	int bufsize = FTSH_TOK_BUFSIZE, i = 0;
	char **tokens = malloc(sizeof (**tokens) * bufsize);
	char *token;

	token = strtok(line, FTSH_TOK_DELIM);
	while (!token)
	{
		tokens[i] = token;
		i++;

		if (i >= bufsize)
		{
			bufsize += FTSH_TOK_BUFSIZE;
			tokens = realloc(tokens, sizeof (*tokens) * bufsize);
		}
		token = strtok(NULL, FTSH_TOK_DELIM);
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
 * Reading line from input
 */
char
*sh_getline(void)
{
	char *line = NULL;
	ssize_t bufsize = 0;

	getline(&line, &bufsize, stdin);
	return (line);
}

/**
 * The main shell loop
 */
void
sh_loop(char **envp)
{
	char *line, **argv;
	int status;

	do
	{
		printf("> ");
		line = sh_getline();
		argv = sh_split(line);
		free(line);
		status = sh_exec(argv);
		free(argv);
	} while (status);
}

int
main(int argc, char **argv, char **envp)
{
	char **env;
	if (!(env = malloc(sizeof (*env) * argc)))
	{
		perror(NULL);
		exit(errno);
	}
	for (int i = 0; i < argc; i++)
	{
		if (!(env[i] = malloc(sizeof (**env) * strlen(envp[i]))))
		{
			perror(NULL);
			exit(errno);
		}
		strcpy(env[i], envp[i]);
	}

	sh_loop(env);

	exit(0);
}
