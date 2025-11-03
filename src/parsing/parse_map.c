/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:13:00 by mohben-t          #+#    #+#             */
/*   Updated: 2025/10/21 11:18:44 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	find_player(t_config *config)
{
    int	y;
    int	x;
    int	player_count;

    player_count = 0;
    y = 0;
    while (y < config->map_h)
    {
        x = 0;
        while (config->map[y] && config->map[y][x])
        {
            if (is_player_char(config->map[y][x]))
            {
                config->player_x = x;
                config->player_y = y;
                config->player_dir = config->map[y][x];
                player_count++;
            }
            x++;
        }
        y++;
    }
    if (player_count == 0)
        print_error(ERR_NO_PLAYER);
    if (player_count > 1)
        print_error(ERR_MULTIPLAYER);
}

static int	is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || c == ' ' || is_player_char(c));
}

static void	validate_map_borders(t_config *config)
{
    int	y;
    int	x;

    y = 0;
    while (y < config->map_h)
    {
        if (y == 0 || y == config->map_h - 1)
        {
            x = 0;
            while (config->map[y][x])
            {
                if (config->map[y][x] != '1' && config->map[y][x] != ' ')
                    print_error(ERR_INVALID_MAP);
                x++;
            }
        }
        y++;
    }
    
}
int	first_non_space(char *s)
{
    int	i;

    if (!s)
        return (-1);
    i = 0;
    while (s[i] && (s[i] == ' ' || s[i] == '\t'))
        i++;
    if (s[i])
        return (i);
    return (-1);
}
int	last_non_space(char *s)
{
    int	i;

    if (!s)
        return (-1);
    i = ft_strlen(s) - 1;
    while (i >= 0 && (s[i] == ' ' || s[i] == '\t'))
        i--;
    if (i >= 0) 
        return (i);
    return (-1);
}

int	find_consecutive_newlines(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' && str[i + 1] == '\n')
			return (1);
		str++;
	}
	return (0);
}

void	validate_map(t_config *config)
{
    int	y;
    int	x;
    int left;
    int right;

    if (!config->map || config->map_h == 0)
        print_error(ERR_INVALID_MAP);
    
    y = 0;
    while (y < config->map_h)
    {
        left = first_non_space(config->map[y]);
        right = last_non_space(config->map[y]);
        if (left == -1 || right == -1)
            print_error(ERR_INVALID_MAP);
        if (config->map[y][left] != '1' || config->map[y][right] != '1')
            print_error(ERR_INVALID_MAP);
        y++;
    }
    y = 0;
    while (y < config->map_h)
    {
        x = 0;
        while (config->map[y][x])
        {
            if (!is_valid_map_char(config->map[y][x]))
                print_error(ERR_INVALID_MAP);
            x++;
        }
        y++;
    }
    y = 0;
    while (y < config->map_h)
    {
        x = 0;
        while (config->map[y][x])
        {
            if (config->map[y][x] == ' ')
                config->map[y][x] = '1';
            x++;
        }
        y++;
    }
    find_player(config);
    validate_map_borders(config);
}

