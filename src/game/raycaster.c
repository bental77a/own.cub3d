/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houarrak <houarrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 20:47:57 by houarrak          #+#    #+#             */
/*   Updated: 2025/10/05 18:58:28 by houarrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void raycast(t_game *game, t_player *player)
{
    int x;
    for (x = 0; x < WIDTH; x++)
    {
        // 1. Ray direction for this column
        double camera_x = 2 * x / (double)WIDTH - 1;
        double ray_dir_x = player->dir_x + player->plane_x * camera_x;
        double ray_dir_y = player->dir_y + player->plane_y * camera_x;

        // 2. Map position
        int map_x = (int)player->x;
        int map_y = (int)player->y;

        // 3. Length of ray from one x/y-side to next x/y-side
        double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
        double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);

        // 4. Step and initial side_dist
        int step_x, step_y;
        double side_dist_x, side_dist_y;
        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (player->x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - player->x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (player->y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - player->y) * delta_dist_y;
        }

        // 5. DDA algorithm
        int hit = 0;
        int side;
        //printf("Player position: x=%f, y=%f\n", player->x, player->y);
        while (hit == 0)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
                if (map_x < 0 || map_y < 0 ||
        map_y >= game->config.map_h ||
        map_x >= (int)ft_strlen(game->config.map[map_y]) )
            {
        // Option
        break;
            }
            if (game->config.map[map_y][map_x] == '1'){
                hit = 1;
                 //printf("Mur tdrb en %d, %d\n", map_x, map_y);
            }
        }

        // 6. Calculate distance to wall
        double perp_wall_dist;
        if (side == 0)
            perp_wall_dist = (side_dist_x - delta_dist_x);
        else
            perp_wall_dist = (side_dist_y - delta_dist_y);

        // 7. Calculate wall height
        int line_height = (int)(HEIGHT / perp_wall_dist);

        // 8. Calculate lowest and highest pixel to fill in current stripe
        int draw_start = -line_height / 2 + HEIGHT / 2;
        if (draw_start < 0) draw_start = 0;
        int draw_end = line_height / 2 + HEIGHT / 2;
        if (draw_end >= HEIGHT) draw_end = HEIGHT - 1;

        // 9. Choose color (different for x/y wall)
        int color = (side == 0) ? 0x2550000 : 0x800000;

        // 10. Draw vertical line
        for (int y = draw_start; y < draw_end; y++)
            put_pixel(game, x, y, color);
    }
}