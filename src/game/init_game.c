/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houarrak <houarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 15:14:03 by houarrak          #+#    #+#             */
/*   Updated: 2025/10/04 15:19:20 by houarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void init_game(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
        put_error("MLX init failed\n");
    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
    if (!game->win)
        put_error("Window creation failed\n");
    game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    if (!game->img)
        put_error("Image creation failed\n");
    game->img_data = mlx_get_data_addr(game->img, &game->bpp, &game->line_len, &game->endian);
    if (!game->img_data)
        put_error("Image data addr failed\n");
}