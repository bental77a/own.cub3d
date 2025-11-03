/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houarrak <houarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 14:02:59 by houarrak          #+#    #+#             */
/*   Updated: 2025/10/04 14:03:49 by houarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int rgb_to_int(int r, int g, int b)
{
    return ((r << 16) | (g << 8) | b);
}

void put_pixel(t_game *game, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    dst = game->img_data + (y * game->line_len + x * (game->bpp / 8));
    *(unsigned int*)dst = color;
}

void draw_background(t_game *game)
{
    int x, y;
    int ceil = rgb_to_int(game->config.ceil[0], game->config.ceil[1], game->config.ceil[2]);
    int floor = rgb_to_int(game->config.floor[0], game->config.floor[1], game->config.floor[2]);

    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            if (y < HEIGHT / 2)
                put_pixel(game, x, y, ceil);
            else
                put_pixel(game, x, y, floor);
        }
    }
}