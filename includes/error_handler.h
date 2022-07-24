/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgoncalv <lgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 16:09:45 by lgoncalv          #+#    #+#             */
/*   Updated: 2022/07/23 17:14:48 by lgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLER_H
# define ERROR_HANDLER_H

# include <errno.h>
# include <string.h>

# define P_NONE				"Exited with no errors.\n"
# define P_NO_ARG			"No arguments detected."
# define P_INVALID_ARG		"Invalid number of arguments detected."
# define P_HOW_TO_USE		" Usage: ./pipex \"file1\" \"cmd1\" \"cmd2\" \"file2\"\n"
# define P_PIPE				"Failed to create a pipe"
# define P_FORK				"Failed to fork process"
# define P_WRITE			"Failed to write to pipe"
# define P_READ				"Failed to read from pipe"
# define P_INVALID_COMMNAND	"command not found"
# define P_DUP2				"Failed to duplicate file descriptor"

typedef enum e_error
{
	e_none				= 0,
	e_no_arg			= 10,
	e_invalid_arg		= 20,
	e_pipe				= 30,
	e_fork				= 40,
	e_write				= 50,
	e_read				= 60,
	e_dup2				= 70,
	e_invalid_command	= 100
}	t_error;

void	get_error_msg(char *error, char *var);
void	get_error(t_error e_arg);
void	exit_with_error(t_error e_code);

#endif