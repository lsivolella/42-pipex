/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgoncalv <lgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:03:35 by lgoncalv          #+#    #+#             */
/*   Updated: 2022/07/09 21:47:24 by lgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
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
	char	**path;
	char	*shell;
	char	*temp_string;
	char	*temp_cmd;
}	t_args;

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	t_args	input;
}	t_pipex;

#endif