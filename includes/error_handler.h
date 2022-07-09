/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgoncalv <lgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 16:09:45 by lgoncalv          #+#    #+#             */
/*   Updated: 2022/07/09 10:34:05 by lgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLER_H
# define ERROR_HANDLER_H

typedef enum e_error
{
	e_none				= 0,
	e_no_arg			= 10,
	e_invalid_arg		= 20,
	e_pipe				= 30,
	e_mlx_init			= 40,
	e_window_init		= 50,
	e_image_init		= 60,
	e_mlx_null			= 70,
	e_window_null		= 80,
	e_image_null		= 90,
	e_obj_null			= 100,
	e_unreadable_map	= 110,
	e_invalid_map		= 120
}	t_error;

void	get_error(t_error e_arg);

#endif