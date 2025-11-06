/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsse_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:38:13 by mohben-t          #+#    #+#             */
/*   Updated: 2025/11/06 11:39:01 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	parse_component(char **str, int *value)
{
	int	component;

	skip_space(str);
	if (**str < '0' || **str > '9')
		return (-1);
	component = 0;
	while (**str >= '0' && **str <= '9')
	{
		component = component * 10 + (**str - '0');
		if (component > 255)
			return (-1);
		(*str)++;
	}
	if (**str && **str != ' ' && **str != '\t' && **str != ',' && **str != '\n')
		return (-1);
	*value = component;
	return (0);
}

int	get_color(char **str, int color[3])
{
	int	index;

	index = 0;
	while (index < 3)
	{
		if (parse_component(str, &color[index]) == -1)
			return (-1);
		skip_space(str);
		if (index < 2)
		{
			if (**str != ',')
				return (-1);
			(*str)++;
		}
		index++;
	}
	skip_space(str);
	if (**str && **str != '\n')
		return (-1);
	return (0);
}

int	get_colors(char **str, t_config *config)
{
	if (**str == 'F')
	{
		(*str)++;
		return (get_color(str, config->floor));
	}
	else if (**str == 'C')
	{
		(*str)++;
		return (get_color(str, config->ceil));
	}
	return (0);
}
void	free_textures(t_config *config)
{
	if (config->no_tex)
		free(config->no_tex);
	if (config->so_tex)
		free(config->so_tex);
	if (config->we_tex)
		free(config->we_tex);
	if (config->ea_tex)
		free(config->ea_tex);
}

char	*get_path_textures(char **str)
{
	int		len;
	char	*path;
	int		i;

	i = 0;
	skip_space(str);
	len = get_len(*str);
	path = malloc(len + 1);
	if (!path)
		return (NULL);
	while (i < len && (*str)[i])
	{
		path[i] = (*str)[i];
		i++;
	}
	path[i] = '\0';
	*str += len;
	return (path);
}
