/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgoncalv <lgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 21:56:19 by lgoncalv          #+#    #+#             */
/*   Updated: 2022/07/24 11:58:17 by lgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*substitute_char(char *str, char search, char replace)
{
	char	*string;
	int		i;

	string = ft_strdup(str);
	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '\'')
		{
			i++;
			while (string[i] != '\'')
			{
				if (string[i] == search)
					string[i] = replace;
				i++;
			}
		}
		i++;
	}
	return (string);
}

char	*restore_space(char *str)
{
	char	*string;
	char	*temp;

	temp = substitute_char(str, 1, ' ');
	string = ft_strtrim(temp, "'");
	free(str);
	free(temp);
	return (string);
}

void	free_matrix(char **matrix)
{
	int	i;

	if (matrix == NULL)
		return ;
	i = -1;
	while (matrix[++i] != NULL)
		free(matrix[i]);
	free(matrix);
}
