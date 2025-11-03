/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houarrak <houarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:20:09 by houarrak          #+#    #+#             */
/*   Updated: 2025/10/05 18:34:49 by houarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int handle_keypress(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
    {
        mlx_destroy_window(game->mlx, game->win);
        exit(0);
    }
    else if (keycode == W)
        move_forward(game);
    else if (keycode == S)
        move_backward(game);
    else if (keycode == A)
        strafe_left(game);
    else if (keycode == D)
        strafe_right(game);
    else if (keycode == LEFT)
        rotate_left(game);
    else if (keycode == RIGHT)
        rotate_right(game);


    draw_background(game);
    raycast(game, &game->player);
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return 0;
}