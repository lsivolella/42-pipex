/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgoncalv <lgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 10:28:43 by lgoncalv          #+#    #+#             */
/*   Updated: 2022/07/10 17:47:43 by lgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	print_error(t_error e_code)
{
	if (e_code == e_no_arg)
		ft_putstr_fd(P_NO_ARG, 1);
	else if (e_code == e_invalid_arg)
		ft_putstr_fd(P_INVALID_ARG, 1);
	else if (e_code == e_pipe)
		perror(P_PIPE);
	else if (e_code == e_fork)
		perror(P_FORK);
	else if (e_code == e_write)
		perror(P_WRITE);
	else if (e_code == e_read)
		perror(P_READ);
	else if (e_code == e_create_infile)
	{
		printf("Errror creating infile\n");
		//strerror(errno);
		perror(P_CREATE_INFILE);
	}
	else if (e_code == e_open_infile)
	{
		printf("Errror opening infile\n");
		perror(P_OPEN_INFILE);
	}
	else if (e_code == e_open_outfile)
		perror(P_OPEN_OUTFILE);
	else if (e_code == e_invalid_command)
	{
		//ft_putstr_fd("Invalid command error printing here\n", 2);
		perror(P_INVALID_COMMNAND);
	}
	if (e_code == e_no_arg || e_code == e_invalid_arg)
		ft_putstr_fd(P_HOW_TO_USE, 1);
}

void	get_error(t_error e_code)
{
	if (e_code == e_none)
		ft_putstr_fd(P_NONE, 1);
	else
		print_error(e_code);
}

void	exit_with_error(t_error e_code)
{
	get_error(e_code);
	printf("Exit with code 1\n");
	exit(1);
}
