/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houarrak <houarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 18:54:19 by houarrak          #+#    #+#             */
/*   Updated: 2025/10/04 19:00:19 by houarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub.h"



void init_player(t_player *player, t_config *config)
{
    player->x = config->player_x + 0.5;
    player->y = config->player_y + 0.5;
    if (config->player_dir == 'N')
    {
        player->dir_x = 0;
        player->dir_y = -1;
        player->plane_x = 0.66;
        player->plane_y = 0;
    }
    else if (config->player_dir == 'S')
    {
        player->dir_x = 0;
        player->dir_y = 1;
        player->plane_x = -0.66;
        player->plane_y = 0;
    }
    else if (config->player_dir == 'E')
    {
        player->dir_x = 1;
        player->dir_y = 0;
        player->plane_x = 0;
        player->plane_y = 0.66;
    }
    else if (config->player_dir == 'W')
    {
        player->dir_x = -1;
        player->dir_y = 0;
        player->plane_x = 0;
        player->plane_y = -0.66;
    }
}

// int key_press(int keycode, t_player *player)
// {
//     if(keycode == W)
//         player->key_up = true;
//     if(keycode == S)
//         player->key_down = true;
//     if(keycode == A)
//         player->key_left = true;
//     if(keycode == D)
//         player->key_right = true;
//     if(keycode == LEFT)
//         player->left_rotate = true;
//     if(keycode == RIGHT)
//         player->right_rotate = true;
//     return 0;
// }

// int key_release(int keycode, t_player *player)
// {
//     if(keycode == W)
//         player->key_up = false;
//     if(keycode == S)
//         player->key_down = false;
//     if(keycode == A)
//         player->key_left = false;
//     if(keycode == D)
//         player->key_right = false;
//     if(keycode == LEFT)
//         player->left_rotate = false;
//     if(keycode == RIGHT)
//         player->right_rotate = false;
//     return 0;
// }

// void move_player(t_player *player)
// {
//     int speed = 3;
//     float angle_speed = 0.03;
//     float cos_angle = cos(player->angle);
//     float sin_angle = sin(player->angle);

//     if (player->left_rotate)
//         player->angle -= angle_speed;
//     if (player->right_rotate)
//         player->angle += angle_speed;
//     if (player->angle > 2 * PI)
//         player->angle = 0;
//     if (player->angle < 0)
//         player->angle = 2 * PI;

//     if (player->key_up)
//     {
//         player->x += cos_angle * speed;
//         player->y += sin_angle * speed;
//     }
//     if (player->key_down)
//     {
//         player->x -= cos_angle * speed;
//         player->y -= sin_angle * speed;
//     }
//     if (player->key_left)
//     {
//         player->x += sin_angle * speed;
//         player->y -= cos_angle * speed;
//     }
//     if (player->key_right)
//     {
//         player->x -= sin_angle * speed;
//         player->y += cos_angle * speed;
//     }
// }