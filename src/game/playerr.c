/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houarrak <houarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 18:18:55 by houarrak          #+#    #+#             */
/*   Updated: 2025/10/05 18:23:59 by houarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

#define MOVE_SPEED 0.08
#define ROT_SPEED 0.045

// Collision check : renvoie 1 si la case est libre
int is_empty_cell(t_game *game, double x, double y)
{
    int map_x = (int)x;
    int map_y = (int)y;
    if (map_x < 0 || map_x >= game->config.map_w || map_y < 0 || map_y >= game->config.map_h)
        return 0;
    return (game->config.map[map_y][map_x] != '1');
}

void move_forward(t_game *game)
{
    double nx = game->player.x + game->player.dir_x * MOVE_SPEED;
    double ny = game->player.y + game->player.dir_y * MOVE_SPEED;
    if (is_empty_cell(game, nx, game->player.y))
        game->player.x = nx;
    if (is_empty_cell(game, game->player.x, ny))
        game->player.y = ny;
}

void move_backward(t_game *game)
{
    double nx = game->player.x - game->player.dir_x * MOVE_SPEED;
    double ny = game->player.y - game->player.dir_y * MOVE_SPEED;
    if (is_empty_cell(game, nx, game->player.y))
        game->player.x = nx;
    if (is_empty_cell(game, game->player.x, ny))
        game->player.y = ny;
}

void strafe_left(t_game *game)
{
    double nx = game->player.x - game->player.plane_x * MOVE_SPEED;
    double ny = game->player.y - game->player.plane_y * MOVE_SPEED;
    if (is_empty_cell(game, nx, game->player.y))
        game->player.x = nx;
    if (is_empty_cell(game, game->player.x, ny))
        game->player.y = ny;
}

void strafe_right(t_game *game)
{
    double nx = game->player.x + game->player.plane_x * MOVE_SPEED;
    double ny = game->player.y + game->player.plane_y * MOVE_SPEED;
    if (is_empty_cell(game, nx, game->player.y))
        game->player.x = nx;
    if (is_empty_cell(game, game->player.x, ny))
        game->player.y = ny;
}

void rotate_left(t_game *game)
{
    double old_dir_x = game->player.dir_x;
    double old_plane_x = game->player.plane_x;
    game->player.dir_x = old_dir_x * cos(-ROT_SPEED) - game->player.dir_y * sin(-ROT_SPEED);
    game->player.dir_y = old_dir_x * sin(-ROT_SPEED) + game->player.dir_y * cos(-ROT_SPEED);
    game->player.plane_x = old_plane_x * cos(-ROT_SPEED) - game->player.plane_y * sin(-ROT_SPEED);
    game->player.plane_y = old_plane_x * sin(-ROT_SPEED) + game->player.plane_y * cos(-ROT_SPEED);
}

void rotate_right(t_game *game)
{
    double old_dir_x = game->player.dir_x;
    double old_plane_x = game->player.plane_x;
    game->player.dir_x = old_dir_x * cos(ROT_SPEED) - game->player.dir_y * sin(ROT_SPEED);
    game->player.dir_y = old_dir_x * sin(ROT_SPEED) + game->player.dir_y * cos(ROT_SPEED);
    game->player.plane_x = old_plane_x * cos(ROT_SPEED) - game->player.plane_y * sin(ROT_SPEED);
    game->player.plane_y = old_plane_x * sin(ROT_SPEED) + game->player.plane_y * cos(ROT_SPEED);
}