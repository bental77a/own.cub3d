/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houarrak <houarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:08:23 by houarrak          #+#    #+#             */
/*   Updated: 2025/10/04 15:28:01 by houarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

// int rgb_to_int(int r, int g, int b)
// {
//     return (r << 16 | g << 8 | b);
// }


// void draw_background(t_game *game)
// {
//     int x, y;
//     int ceil = rgb_to_int(game->config.ceil[0], game->config.ceil[1], game->config.ceil[2]);
//     int floor = rgb_to_int(game->config.floor[0], game->config.floor[1], game->config.floor[2]);

//     for (y = 0; y < HEIGHT; y++)
//     {
//         for (x = 0; x < WIDTH; x++)
//         {
//             if (y < HEIGHT / 2)
//                 put_pixel(x, y, ceil, game);
//             else
//                 put_pixel(x, y, floor, game);
//         }
//     }
//     mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
// }
