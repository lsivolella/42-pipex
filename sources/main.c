/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgoncalv <lgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:03:21 by lgoncalv          #+#    #+#             */
/*   Updated: 2022/07/09 23:51:31 by lgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>

void	get_cmd_path(char **cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*temp;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, cmd[0]);
		free(temp);
		if (access(path, F_OK) == 0)
		{
			//printf("Execute command\n");
			execve(path, cmd, envp);
		}
		free(path);
	}
	while (paths)
	{
		free(*paths);
		paths++;
	}
	free(paths);
}

void	get_cmd(char *argv, char **envp)
{
	char	**cmd;
	//printf("Get command: %s\n", argv);
	if (!*argv)
		get_error(e_no_arg);
	cmd = ft_split(argv, ' ');
	get_cmd_path(cmd, envp);
}

void	pipex(t_pipex *data)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (pipe(fd) == -1)
		get_error(e_pipe);
	pid1 = fork();
	if (pid1 < 0)
		get_error(e_fork);
	if (pid1 == 0)
	{
		//printf("Child process one\n");
		dup2(data->infile, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		get_cmd(data->input.argv[2], data->input.envp);
	}
	pid2 = fork();
	if (pid2 < 0)
		get_error(e_fork);
	if (pid2 == 0)
	{
		//printf("Child process two\n");
		dup2(data->outfile, STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		get_cmd(data->input.argv[3], data->input.envp);
	}
	wait(NULL);
}

void	init_data(t_pipex *data, char **argv, char **envp)
{
	ft_memset(data, '\0', sizeof(t_pipex));
	printf("Access: %d\n", access(argv[1], F_OK));
	if (access(argv[1], F_OK) < 0)
		get_error(e_create_infile);
	data->infile = open(argv[1], O_RDONLY);
	printf("Open Infile %d", data->infile);
	if (data->infile < 0)
		get_error(e_open_infile);
	data->outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, FILE_PERM);
	if (data->outfile < 0)
	{
		//printf("\n\nCould not open outfile baby\n\n");
		get_error(e_open_outfile);
		exit (1);
	}
	data->input.argv = argv;
	data->input.envp = envp;
}

void	error_msg(char *name, char *err)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err, 2);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	if (argc == 1)
		get_error(e_no_arg);
	else if (argc < 5 || argc > 5)
		get_error(e_invalid_arg);
	else if (argc == 5)
	{
		init_data(&data, argv, envp);
		pipex(&data);
	}
	//printf("End Program -> Process: %d\n", getpid());
	get_error(e_none);
	return (0);
}
