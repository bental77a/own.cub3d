/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:13:00 by mohben-t          #+#    #+#             */
/*   Updated: 2025/11/06 17:15:08 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static int	handle_texture_entry(char *line, t_config *config, int *count)
{
	char	*cursor;

	cursor = line;
	skip_space(&cursor);
	if (*cursor == '\0' || *cursor == '\n')
		return (0);
	if (handle_identifier_line(&cursor, config) == -1)
		return (-1);
	(*count)++;
	return (0);
}

int	check_textures_and_color(char **map_str, t_config *config)
{
	char	*line;
	int		count;

	count = 0;
	while ((line = get_next_line_from_string(map_str)))
	{
		if (count == 6)
		{
			free(line);
			break ;
		}
		if (handle_texture_entry(line, config, &count) == -1)
		{
			free(line);
			return (-1);
		}
		free(line);
	}
	if (!config->no_tex || !config->so_tex || !config->we_tex
		|| !config->ea_tex)
		return (-1);
	return (0);
}

static int	process_cell(char cell, int row, int col, t_config *config)
{
	if (!is_valid_map_char(cell))
		return (-1);
	if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
	{
		if (config->player_dir != '\0')
			return (-1);
		config->player_x = row;
		config->player_y = col;
		config->player_dir = cell;
	}
	return (0);
}

int	check_reachble(char **arr, t_config *config)
{
	int	row;
	int	col;

	if (!arr || !config)
		return (-1);
	config->player_x = -1;
	config->player_y = -1;
	config->player_dir = '\0';
	row = 0;
	while (arr[row])
	{
		col = 0;
		while (arr[row][col])
		{
			if (process_cell(arr[row][col], row, col, config) == -1)
				return (-1);
			col++;
		}
		row++;
	}
	if (config->player_dir == '\0')
		return (-1);
	return (0);
}

char	*get_next_line_from_string(char **map_str)
{
	char	*line;
	char	*newline;
	int		len;

	if (!map_str || !*map_str || **map_str == '\0')
		return (NULL);
	newline = ft_strchr(*map_str, '\n');
	if (newline)
		len = newline - *map_str + 1;
	else
		len = ft_strlen(*map_str);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	ft_strncpy(line, *map_str, len);
	line[len] = '\0';
	if (newline)
		*map_str = newline + 1;
	else
		*map_str += len;
	return (line);
}
