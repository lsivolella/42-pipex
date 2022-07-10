/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgoncalv <lgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 16:09:45 by lgoncalv          #+#    #+#             */
/*   Updated: 2022/07/09 23:47:30 by lgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLER_H
# define ERROR_HANDLER_H

# include <errno.h>
# include <string.h>

# define P_NONE			"Exited with no errors.\n"
# define P_NO_ARG		"No arguments detected."
# define P_INVALID_ARG	"Invalid number of arguments detected."
# define P_HOW_TO_USE	" Usage: ./pipex \"file1\" \"cmd1\" \"cmd2\" \"file2\"\n"
# define P_PIPE			"Failed to create a pipe: "
# define P_FORK			"Failed to fork process: "
# define P_WRITE		"Failed to write to pipe: "
# define P_READ			"Failed to read from pipe: "
# define P_CREATE_INFILE	"Failed to cleate infile: "
# define P_OPEN_INFILE	"Failed to open infile: "
# define P_OPEN_OUTFILE	"Failed to open outfile: "

typedef enum e_error
{
	e_none				= 0,
	e_no_arg			= 10,
	e_invalid_arg		= 20,
	e_pipe				= 30,
	e_fork				= 40,
	e_write				= 50,
	e_read				= 60,
	e_create_infile		= 70,
	e_open_infile		= 80,
	e_open_outfile		= 90
}	t_error;

void	get_error(t_error e_arg);

#endif