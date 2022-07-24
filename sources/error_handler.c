/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgoncalv <lgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 10:28:43 by lgoncalv          #+#    #+#             */
/*   Updated: 2022/07/23 17:14:41 by lgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_error_msg(char *error, char *var)
{
	ft_putstr_fd(error, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(var, STDERR_FILENO);
}

static void	print_error(t_error e_code)
{
	if (e_code == e_no_arg)
		ft_putstr_fd(P_NO_ARG, STDERR_FILENO);
	else if (e_code == e_invalid_arg)
		ft_putstr_fd(P_INVALID_ARG, STDERR_FILENO);
	else if (e_code == e_pipe)
		perror(P_PIPE);
	else if (e_code == e_fork)
		perror(P_FORK);
	else if (e_code == e_write)
		perror(P_WRITE);
	else if (e_code == e_read)
		perror(P_READ);
	else if (e_code == e_invalid_command)
		perror(P_INVALID_COMMNAND);
	else if (e_code == e_dup2)
		perror(P_DUP2);
	if (e_code == e_no_arg || e_code == e_invalid_arg)
		ft_putstr_fd(P_HOW_TO_USE, STDERR_FILENO);
}

void	get_error(t_error e_code)
{
	if (e_code == e_none)
		ft_putstr_fd(P_NONE, STDERR_FILENO);
	else
		print_error(e_code);
}

void	exit_with_error(t_error e_code)
{
	get_error(e_code);
	exit(1);
}
