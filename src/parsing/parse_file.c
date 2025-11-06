/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:12:38 by mohben-t          #+#    #+#             */
/*   Updated: 2025/11/06 17:16:25 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	normalize_map(char **arr, t_config *config)
{
	config->map = resize_line(arr, config->map_w, config->map_h);
	if (!config->map)
	{
		free_array(arr);
		return (printf("Error alloc map\n"), -1);
	}
	free_array(arr);
	if (!check_last_zero(config->map, config->player_dir))
	{
		free_array(config->map);
		config->map = NULL;
		return (printf("Error map not closed\n"), -1);
	}
	return (0);
}

int	validate_map_array(char **arr, t_config *config)
{
	measure_map(arr, config);
	if (!check_map_walls(arr, config->map_h))
	{
		free_array(arr);
		return (printf("walllllllllllllllllls\n"), -1);
	}
	if (check_reachble(arr, config) == -1)
	{
		free_array(arr);
		return (printf("Error elements\n"), -1);
	}
	return (normalize_map(arr, config));
}

int	parse_map(char **map_cursor, t_config *config)
{
	char	**arr;

	skip_lines(map_cursor);
	if (find_consecutive_newlines(*map_cursor) == 1)
		return (printf("too lines"), -1);
	arr = ft_split(*map_cursor, '\n');
	if (!arr)
		return (-1);
	return (validate_map_array(arr, config));
}

int	parse_content(char *content, t_config *config)
{
	char	*cursor;

	cursor = content;
	if (check_textures_and_color(&cursor, config) == -1)
		return (-1);
	if (parse_map(&cursor, config) == -1)
		return (-1);
	return (0);
}

int	parse_file(char *filename, t_config *config)
{
	int		fd;
	char	*all_map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (print_error(ERR_INVALID_PATH), 1);
	if (load_map_content(fd, &all_map) == -1)
	{
		close(fd);
		put_error("Failed to read map");
	}
	close(fd);
	if (!all_map)
		return (1);
	if (parse_content(all_map, config) == -1)
	{
		free(all_map);
		put_error("Invalid textures/colors");
	}
	free(all_map);
	return (0);
}