/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgoncalv <lgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 08:41:48 by lgoncalv          #+#    #+#             */
/*   Updated: 2022/07/23 23:00:56 by lgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipe_read(t_pipex *data)
{
	close(data->fd[1]);
	if (dup2(data->outfile_fd, STDOUT_FILENO) == -1)
		exit_with_error(e_dup2);
	if (dup2(data->fd[0], STDIN_FILENO) == -1)
		exit_with_error(e_dup2);
	close(data->outfile_fd);
	get_cmd(data, data->input.argv[3]);
}

void	pipe_write(t_pipex *data)
{
	close(data->fd[0]);
	if (data->infile_fd == -1)
		exit (0);
	if (dup2(data->infile_fd, STDIN_FILENO) == -1)
		exit_with_error(e_dup2);
	if (dup2(data->fd[1], STDOUT_FILENO) == -1)
		exit_with_error(e_dup2);
	close(data->infile_fd);
	get_cmd(data, data->input.argv[2]);
}

void	pipex(t_pipex *data)
{
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(data->fd) == -1)
		exit_with_error(e_pipe);
	pid1 = fork();
	if (pid1 < 0)
		exit_with_error(e_fork);
	if (pid1 == 0)
		pipe_write(data);
	pid2 = fork();
	if (pid2 < 0)
		exit_with_error(e_fork);
	if (pid2 == 0)
		pipe_read(data);
	close(data->fd[0]);
	close(data->fd[1]);
	waitpid(pid1, &data->exit_code, 0);
	waitpid(pid2, &data->exit_code, 0);
}

void	init_data(t_pipex *data, char **argv, char **envp)
{
	ft_memset(data, '\0', sizeof(t_pipex));
	data->infile_access = access(argv[1], F_OK);
	if (data->infile_access == -1)
		get_error_msg(strerror(errno), argv[1]);
	data->infile_fd = open(argv[1], O_RDONLY);
	if (data->infile_access == 0 && data->infile_fd == -1)
		get_error_msg(strerror(errno), argv[1]);
	data->outfile_fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, FILE_PERM);
	if (data->outfile_fd == -1)
	{
		get_error_msg(strerror(errno), argv[4]);
		exit (1);
	}
	data->input.argv = argv;
	data->input.envp = envp;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	if (argc == 1)
		exit_with_error(e_no_arg);
	else if (argc < 5 || argc > 5)
		exit_with_error(e_invalid_arg);
	else if (argc == 5)
	{
		init_data(&data, argv, envp);
		pipex(&data);
		exit(WEXITSTATUS(data.exit_code));
	}
	return (0);
}
