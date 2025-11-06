/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:42:58 by mohben-t          #+#    #+#             */
/*   Updated: 2025/11/06 17:19:08 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

// void	print_config(t_config *config)
// {
//     printf("\n=== PARSING RESULTS ===\n");
// 	printf("NO texture: %s\n", config->no_tex ? config->no_tex : "NULL");
// 	printf("SO texture: %s\n", config->so_tex ? config->so_tex : "NULL");
// 	printf("WE texture: %s\n", config->we_tex ? config->we_tex : "NULL");
// 	printf("EA texture: %s\n", config->ea_tex ? config->ea_tex : "NULL");

// 	printf("Floor RGB: %d,%d,%d\n", config->floor[0], config->floor[1],
		// config->floor[2]);
// 	printf("Ceiling RGB: %d,%d,%d\n", config->ceil[0], config->ceil[1],
		// config->ceil[2]);
// 	printf("======================\n\n");
// }

int	handle_identifier_line(char **cursor, t_config *config)
{
	if (!ft_strncmp(*cursor, "NO", 2) || !ft_strncmp(*cursor, "SO", 2)
		|| !ft_strncmp(*cursor, "WE", 2) || !ft_strncmp(*cursor, "EA", 2))
		return (get_textures(cursor, config));
	if (**cursor == 'F' || **cursor == 'C')
		return (get_colors(cursor, config));
	return (0);
}

int	is_valid_map_char(char c)
{
	return (c == ' ' || c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W');
}

static void	init_config(t_config *config)
{
	config->no_tex = NULL;
	config->so_tex = NULL;
	config->we_tex = NULL;
	config->ea_tex = NULL;
	config->floor[0] = -1;
	config->floor[1] = -1;
	config->floor[2] = -1;
	config->ceil[0] = -1;
	config->ceil[1] = -1;
	config->ceil[2] = -1;
	config->map = NULL;
	config->map_h = 0;
	config->map_w = 0;
	config->player_x = -1;
	config->player_y = -1;
	config->player_dir = '\0';
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (ft_putendl_fd(USAGE_ERR, 2), 1);
	if (has_cub_extension(av[1]))
		return (1);
	init_config(&game.config);
	if (parse_file(av[1], &game.config))
		return (1);
	if (game.config.floor[0] == -1 && game.config.floor[1] == -1
		&& game.config.floor[2] == -1)
		return (put_error("Floor color not set"), 1);
	if (game.config.ceil[0] == -1 && game.config.ceil[1] == -1
		&& game.config.ceil[2] == -1)
		return (put_error("Ceiling color not set"), 1);
	// print_config(&game.config);
	init_game(&game);
	init_player(&game.player, &game.config);
	draw_background(&game);
	raycast(&game, &game.player);
	mlx_key_hook(game.win, handle_keypress, &game);
	mlx_put_image_to_window(game.mlx, game.win, game.img, 0, 0);
	mlx_loop(game.mlx);
	return (0);
}
