#include <libft.h>

int	print_var(char *args, char **env)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (args[i] && args[i] != ' ' && args[i] != '$' && args[i] != '\t')
		i++;
	while (env[j])
	{
		if (ft_strnequ(&(args[1]), env[j], i - 1))
		{
			ft_putstr(&(env[j][i]));
			break ;
		}
		j++;
	}
	return (i);
}

int	ft_echo(char *args, char **env)
{
	int	new_line;
	int	i;
	
	i = 0;
	new_line = 1;
	if (ft_strnequ(args, "-n", 2) && (args[2] == '\0' || args[2] == ' '
		|| args[2] == '\t'))
	{
		new_line = 0;
		args += 2;
		args += (args[2] != '\0');
	}
	while (args[i])
	{
		if(args[i] == '$' && args[i + 1] != '\0' && args[i + 1] != ' ')
			i += print_var(&(args[i]), env);
		else
			ft_putchar(args[i++]);
	}
	if (new_line)
		ft_putchar('\n');
	return (0);
}

int	call_function(char *cmd, char *args, char **env)
{
	char	*trim_args;

	trim_args = ft_strtrim(args);
	if (ft_strequ(cmd, "echo"))
		ft_echo(args, env);
	//else if(ft_strcmp(cmd, "cd"))
	//	ft_cd(args);
	//else if(ft_strcmp(cmd, "setenv"))
	//	ft_setenv(args);
	//else if(ft_strcmp(cmd, "unsetenv"))
	//	ft_unsetenv(args);
	//else if(ft_strcmp(cmd, "env"))
	//	ft_env(args);
	//else if(ft_strcmp(cmd, "exit"))
	//	ft_exit(args);
	else
	{
		free (trim_args);
		return (1);
	}
	free(trim_args);
	return (0);
}

int	read_line(char *line, char **env)
{
	char	*cmd;
	int		i;

	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\t')
		i++;
	cmd = ft_strndup(line, i);
	call_function(cmd, &(line[i + ((line[i]) ? 1 : 0)]), env);
	return (0);
}

int main(int argc, char **argv, char **env)
{
	char	*line;
	int		i;

	i = 0;
	write(1, "$> ", 3);
	while (get_next_line(0, &line) > 0)
	{
		read_line(line, env);
		write(1, "$> ", 3);
	}
	exit (0);
} 