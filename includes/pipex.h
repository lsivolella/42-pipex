/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgoncalv <lgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:03:35 by lgoncalv          #+#    #+#             */
/*   Updated: 2022/07/24 11:58:17 by lgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>			// for file opening flags
# include <sys/wait.h>		// for waitpid
//# include <sys/types.h>		// for pid_t
# include "libft.h"
# include "error_handler.h"

# define FILE_PERM 0664

typedef struct s_args
{
	char	**argv;
	char	**envp;
	char	**cmd1;
	char	**cmd2;
}	t_args;

typedef struct s_pipex
{
	int		fd[2];
	int		infile_access;
	int		infile_fd;
	int		outfile_fd;
	char	**paths;
	int		exit_code;
	t_args	input;
}	t_pipex;

// commands.c
void	get_cmd_path(char **paths, char **cmd, char **envp);
void	get_paths(t_pipex *data, char **envp);
void	get_cmd(t_pipex *data, char *argv);

// utils.c
char	*substitute_char(char *str, char search, char replace);
char	*restore_space(char *str);
void	free_matrix(char **matrix);

#endif