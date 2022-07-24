/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgoncalv <lgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 21:54:40 by lgoncalv          #+#    #+#             */
/*   Updated: 2022/07/24 11:58:17 by lgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_cmd_path(char **paths, char **cmd, char **envp)
{
	char	*path;
	char	*temp;
	int		i;

	if (ft_strchr(cmd[0], '/'))
		execve(*cmd, cmd, envp);
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, cmd[0]);
		if (access(path, F_OK) == 0)
		{
			execve(path, cmd, envp);
		}
		free(temp);
		free(path);
	}
	get_error_msg(P_INVALID_COMMNAND, cmd[0]);
	free_matrix(cmd);
	free_matrix(paths);
	exit(127);
}

void	get_paths(t_pipex *data, char **envp)
{
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4))
		i++;
	data->paths = ft_split(envp[i] + 5, ':');
}

void	get_cmd(t_pipex *data, char *argv)
{
	char	**cmd;
	char	*temp;
	int		i;

	if (!*argv)
		get_error(e_no_arg);
	temp = substitute_char(argv, ' ', 1);
	cmd = ft_split(temp, ' ');
	free(temp);
	i = -1;
	while (cmd[++i])
		cmd[i] = restore_space(cmd[i]);
	get_paths(data, data->input.envp);
	get_cmd_path(data->paths, cmd, data->input.envp);
}
