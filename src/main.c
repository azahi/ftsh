#include <errno.h>
#include <ft_stdio.h>
#include <ft_stdlib.h>
#include <ft_string.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "builtin/builtin.h"

#define FTSH_NAME "ftsh"
#define FTSH_VERSION "0.1"
#define FTSH_TOK_BUFSIZE 8
#define FTSH_TOK_DELIM "\t\n\v\f\r "

/**
 * Executes from PATH.
 */
int
sh_execvp(char **argv)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(argv[0], argv) == -1) // TODO Switch to execve
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
 * Executes a builtin if argv[0] corresponds to an element in builtin array.
 */
int
sh_exec(char **argv)
{
	if (!argv[0])
		return (1);

	for (int i = 0; i < BUILTIN_COUNT; i++)
	{
		if (strcmp(argv[0], builtin_names[i]) == 0)
			return ((*builtin_func[i])(argv));
	}

	return (sh_execvp(argv));
}

/**
 * Splits input into arguments.
 */
char
**sh_split(char *line)
{
	int bufsize = FTSH_TOK_BUFSIZE, i = 0;
	char **tokens, *token;

	// FIXME Numerical operations are kinda useless on "constant" malloc().
	if (!(tokens = malloc(sizeof (**tokens) * bufsize)))
	{
		perror(NULL);
		exit(errno);
	}

	token = strtok(line, FTSH_TOK_DELIM);
	while (token)
	{
		tokens[i] = token;
		i++;

		if (i >= bufsize)
		{
			bufsize += FTSH_TOK_BUFSIZE;
			if (!(tokens = realloc(tokens, sizeof (**tokens) * bufsize)))
			{
				// FIXME Iteratively clean tokens on failure.
				perror(NULL);
				exit(errno);
			}
		}
		token = strtok(NULL, FTSH_TOK_DELIM);
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
 * Reads a line from input.
 */
char
*sh_getline(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	getline(&line, &bufsize, stdin);
	return (line);
}

/**
 * The main shell loop.
 */
void
sh_loop(char **envp)
{
	int status;

	do
	{
		char *line, **argv;

		printf("> ");
		line = sh_getline();
		argv = sh_split(line);
		status = sh_exec(argv);

		free(line);
		free(argv);
	} while (status);
}

int
main(int argc, char **argv, char **envp)
{
	char **envp_c;
	int opt;

	while ((opt = getopt(argc, argv, "v")) != -1)
	{
		switch (opt) {
			case 'v':
				fprintf(stdout, "%s v%s\n", FTSH_NAME, FTSH_VERSION);
				exit(EXIT_SUCCESS);
			default:
				fprintf(stderr, "Usage: %s [-v]\n", argv[0]);
				exit(EXIT_FAILURE);
		}
	}

	/* Copying the array of environment variables. */
	if (!(envp_c = malloc(sizeof (*envp_c) * argc)))
	{
		perror(NULL);
		exit(errno);
	}
	for (int i = 0; i < argc; i++)
	{
		if (!(envp_c[i] = malloc(sizeof (**envp_c) * strlen(envp[i]))))
		{
			perror(NULL);
			exit(errno);
		}
		strcpy(envp_c[i], envp[i]);
	}

	sh_loop(envp_c);

	exit(EXIT_SUCCESS);
}
