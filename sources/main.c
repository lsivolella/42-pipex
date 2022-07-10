/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgoncalv <lgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:03:21 by lgoncalv          #+#    #+#             */
/*   Updated: 2022/07/10 17:55:56 by lgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		//ft_putstr_fd("Cleaning Paths Array\n", 2);
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

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
		// ft_putstr_fd("Next Path: ", 2);
		// ft_putstr_fd(paths[i + 1], 2);
		// ft_putstr_fd("\n", 2);
		free(temp);
		if (access(path, F_OK) == 0)
		{
			//ft_putstr_fd("Execute command: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd("\n", 2);
			execve(path, cmd, envp);
		}
		free(path);
	}
	//ft_putstr_fd("Could not find valid command\n", 2);
	get_error(e_invalid_command);
	free_matrix(cmd);
	free_matrix(paths);
	exit(0);
}

void	get_cmd(char *argv, char **envp)
{
	char	**cmd;
	//ft_putstr_fd("Get command\n", 2);
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
		if (dup2(data->infile_fd, STDIN_FILENO) < 0)
		{
			//printf("No infile detected!\n");
			close(STDIN_FILENO);
			exit(1);
		}
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(data->outfile_fd);
		//printf("Test here!\n");
		get_cmd(data->input.argv[2], data->input.envp);
	}
	//wait(NULL);
	pid2 = fork();
	if (pid2 < 0)
		get_error(e_fork);
	if (pid2 == 0)
	{
		//printf("Child process two\n");
		dup2(data->outfile_fd, STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		get_cmd(data->input.argv[3], data->input.envp);
	}
	wait(NULL);
}

void	init_data(t_pipex *data, char **argv, char **envp)
{
	ft_memset(data, '\0', sizeof(t_pipex));
	//printf("Access: %d\n", access(argv[1], F_OK));
	data->infile_access = access(argv[1], F_OK);
	if (data->infile_access < 0)
	{
		printf("Access issues with infile\n");
		get_error(e_create_infile);
		// Set data->infile to -1 and skip reading (so I don't have double error calls?)
	}
	data->infile_fd = open(argv[1], O_RDONLY);
	//printf("Open Infile Return: %d\n", data->infile_fd);
	if (data->infile_fd < 0)
	{
		//printf("\n\nCould not open infile baby\n\n");
		get_error(e_open_infile);
	}
	data->outfile_fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, FILE_PERM);
	if (data->outfile_fd < 0)
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
		//printf("Begin Pipex execution\n");
		pipex(&data);
		if (data.infile_access < 0)
		{
			//printf("Error: infile does not exist.\n");
			exit(1);
		}
		if (data.infile_fd < 0)
		{
			//printf("Error: infile exists, but we do not have access permission.\n");
			exit(0);
		}
	}
	//printf("End Program -> Process: %d\n", getpid());
	get_error(e_none);
	return (0);
}
