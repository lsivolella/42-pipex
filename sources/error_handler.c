/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgoncalv <lgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 10:28:43 by lgoncalv          #+#    #+#             */
/*   Updated: 2022/07/09 10:35:35 by lgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static void	print_error(t_error e_code)
{
	ft_printf("Error\n");
	if (e_code == e_no_arg)
		ft_printf("No arguments detected.\n");
	else if (e_code == e_invalid_arg)
		ft_printf("Invalid argument detected.\n");
	else if (e_code == e_mlx_init)
		ft_printf("Could not initialize MinilibX.\n");
	else if (e_code == e_window_init)
		ft_printf("Could not instantiate a MinilibX window.\n");
	else if (e_code == e_image_init)
		ft_printf("Could not render a MinilibX image.\n");
	else if (e_code == e_mlx_null)
		ft_printf("Could not proceed. Connection has been lost.\n");
	else if (e_code == e_obj_null)
		ft_printf("Attempting to modify a null object.\n");
	else if (e_code == e_unreadable_map)
		ft_printf("Could not read map file.\n");
	else if (e_code == e_invalid_map)
		ft_printf("Map is invalid.\n");
}

void	get_error(t_error e_code)
{
	if (e_code == e_none)
		ft_printf("\nExited with no errors.\n");
	else
		print_error(e_code);
}
