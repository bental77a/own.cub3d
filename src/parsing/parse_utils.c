/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:13:08 by mohben-t          #+#    #+#             */
/*   Updated: 2025/11/06 17:19:47 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

bool	is_valid_neighbor(char cell, char pos_pl)
{
	const int	empty = 0;
	const int	wall = 1;

	if (cell == '\0' || cell == ' ')
		return (false);
	if (cell == pos_pl)
		return (true);
	return ((cell - '0' == empty) || (cell - '0' == wall));
}

bool	check_map(int i, int j, char **map, char pos_pl)
{
	if (!map[i + 1] || i == 0 || !map[i - 1])
		return (false);
	if (j == 0 || map[i][j + 1] == '\0')
		return (false);
	if (!is_valid_neighbor(map[i + 1][j], pos_pl))
		return (false);
	if (!is_valid_neighbor(map[i - 1][j], pos_pl))
		return (false);
	if (!is_valid_neighbor(map[i][j + 1], pos_pl))
		return (false);
	if (!is_valid_neighbor(map[i][j - 1], pos_pl))
		return (false);
	return (true);
}

int	check_last_zero(char **map, char pos_pl)
{
	int			i;
	int			j;
	char		cell;
	const int	empty = 0;

	if (!map)
		return (0);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			cell = map[i][j];
			if (cell == pos_pl || (cell >= '0' && cell <= '9' && cell
					- '0' == empty))
			{
				if (!check_map(i, j, map, pos_pl))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

char	find_player_char(char **map)
{
	int	i;
	int	j;

	if (!map)
		return ('\0');
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				return (map[i][j]);
			j++;
		}
		i++;
	}
	return ('\0');
}

int	check_map_walls(char **map, int height)
{
	int		i;
	size_t	len;

	if (!map || height <= 0)
		return (0);
	if (!line_valide(map[0]) || !line_valide(map[height - 1]))
		return (0);
	i = 0;
	while (i < height)
	{
		if (!map[i])
			return (0);
		len = ft_strlen(map[i]);
		if (len == 0)
			return (0);
		if (!border_valid(map[i][0]) || !border_valid(map[i][len - 1]))
			return (0);
		i++;
	}
	return (1);
}
