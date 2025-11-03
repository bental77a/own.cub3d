// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/10/01 14:12:15 by mohben-t          #+#    #+#             */
// /*   Updated: 2025/11/03 17:50:12 by mohben-t         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */


// #include "../includes/cub.h"




// void	print_config(t_config *config)
// {
//     int	i;

//     printf("\n=== PARSING RESULTS ===\n");
//     printf("NO texture: %s\n", config->no_tex ? config->no_tex : "NULL");
//     printf("SO texture: %s\n", config->so_tex ? config->so_tex : "NULL");
//     printf("WE texture: %s\n", config->we_tex ? config->we_tex : "NULL");
//     printf("EA texture: %s\n", config->ea_tex ? config->ea_tex : "NULL");
    
//     printf("Floor RGB: %d,%d,%d\n", config->floor[0], config->floor[1], config->floor[2]);
//     printf("Ceiling RGB: %d,%d,%d\n", config->ceil[0], config->ceil[1], config->ceil[2]);
    
//     printf("Map size: %d x %d\n", config->map_w, config->map_h);
//     printf("Player position: (%d, %d) facing %c\n", 
//         config->player_x, config->player_y, config->player_dir ? config->player_dir : '?');
    
//     printf("\nMap:\n");
//     if (config->map)
//     {
//         i = 0;
//         while (i < config->map_h)
//         {
//             printf("[%d] %s\n", i, config->map[i]);
//             i++;
//         }
//     }
//     printf("======================\n\n");
// }

// static void	init_config(t_config *config)
// {
//     config->no_tex = NULL;
//     config->so_tex = NULL;
//     config->we_tex = NULL;
//     config->ea_tex = NULL;
//     config->floor[0] = -1;
//     config->floor[1] = -1;
//     config->floor[2] = -1;
//     config->ceil[0] = -1;
//     config->ceil[1] = -1;
//     config->ceil[2] = -1;
//     config->map = NULL;
//     config->map_h = 0;
//     config->map_w = 0;
//     config->player_x = -1;
//     config->player_y = -1;
//     config->player_dir = '\0';
// }


// int main(int ac, char **av)
// {
//     t_game game;
    
//     if (ac != 2)
//         return (ft_putendl_fd(USAGE_ERR, 2), 1);
//     if (has_cub_extension(av[1]))
//         return (1);
//     init_config(&game.config);
//     if (parse_file(av[1], &game.config))
//         return (1);
//     validate_map(&game.config);
//     print_config(&game.config);
//     init_game(&game);
//     init_player(&game.player, &game.config);

//     draw_background(&game);

//     raycast(&game, &game.player);
//     mlx_key_hook(game.win, handle_keypress, &game);
//     mlx_put_image_to_window(game.mlx, game.win, game.img, 0, 0);

//     mlx_loop(game.mlx);
//     return (0);
// }


#include "../includes/cub.h"

int	has_cub_extension(char *path)
{
	char	*extension;

	extension = ft_strrchr(path, '.');
	if (extension == NULL)
		return (ft_putendl_fd(INVALID_PATH, 2), 1);
	if (ft_strcmp(extension, ".cub") == 0)
		return (0);
	return (ft_putendl_fd(INVALID_EXT, 2), 1);
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/* -------------------- SKIP & UTILS -------------------- */

void	skip_space(char **str)
{
	while (**str && (**str == ' ' || **str == '\t'))
		(*str)++;
}

int	skip_and_check(char **str)
{
	skip_space(str);
	if (!**str)
		return (1);
	return (0);
}

int	get_len(char *str)
{
	int	len = 0;

	while (str[len] && str[len] != ' ' && str[len] != '\t' && str[len] != '\n')
		len++;
	return (len);
}

/* -------------------- TEXTURE UTILS -------------------- */

void	free_textures(t_config *config)
{
	if (config->no_tex)
		free(config->no_tex);
	if (config->so_tex)
		free(config->so_tex);
	if (config->we_tex)
		free(config->we_tex);
	if (config->ea_tex)
		free(config->ea_tex);
}

char	*get_path_textures(char **str)
{
	int		len;
	char	*path;
	int		i = 0;

	skip_space(str);
	len = get_len(*str);
	path = malloc(len + 1);
	if (!path)
		return (NULL);
	while (i < len && (*str)[i])
	{
		path[i] = (*str)[i];
		i++;
	}
	path[i] = '\0';
	*str += len;
	return (path);
}

int	get_textures(char **str, t_config *config)
{
    skip_space(str);
    if (!ft_strncmp(*str, "NO", 2))
    {
        *str += 2;
        config->no_tex = get_path_textures(str);
    }
    else if (!ft_strncmp(*str, "SO", 2))
    {
        *str += 2;
        config->so_tex = get_path_textures(str);
    }
    else if (!ft_strncmp(*str, "EA", 2))
    {
        *str += 2;
        config->ea_tex = get_path_textures(str);
    }
    else if (!ft_strncmp(*str, "WE", 2))
    {
        *str += 2;
        config->we_tex = get_path_textures(str);
    }
    else
        return (-1);
    return (0);
}

/* -------------------- COLORS -------------------- */

static int	parse_component(char **str, int *value)
{
	int	component;

	skip_space(str);
	if (**str < '0' || **str > '9')
		return (-1);
	component = 0;
	while (**str >= '0' && **str <= '9')
	{
		component = component * 10 + (**str - '0');
		if (component > 255)
			return (-1);
		(*str)++;
	}
	if (**str && **str != ' ' && **str != '\t' && **str != ',' && **str != '\n')
		return (-1);
	*value = component;
	return (0);
}

int	get_color(char **str, int color[3])
{
	int	index;

	index = 0;
	while (index < 3)
	{
		if (parse_component(str, &color[index]) == -1)
			return (-1);
		skip_space(str);
		if (index < 2)
		{
			if (**str != ',')
				return (-1);
			(*str)++;
		}
		index++;
	}
	skip_space(str);
	if (**str && **str != '\n')
		return (-1);
	return (0);
}

int	get_colors(char **str, t_config *config)
{
	if (**str == 'F')
	{
		(*str)++;
		return (get_color(str, config->floor));
	}
	else if (**str == 'C')
	{
		(*str)++;
		return (get_color(str, config->ceil));
	}
	return (0);
}

/* -------------------- PARSE -------------------- */
char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (*(src + i) != '\0' && i < n)
	{
		*(dest + i) = *(src + i);
		i++;
	}
	while (i < n)
	{
		*(dest + i) = '\0';
		i++;
	}
	return (dest);
}

char	*get_next_line_from_string(char **map_str)
{
	char	*line;
	char	*newline;
	int		len;

	if (!map_str || !*map_str || **map_str == '\0')
		return (NULL);

	newline = ft_strchr(*map_str, '\n');
	if (newline)
		len = newline - *map_str + 1;  
	else
		len = ft_strlen(*map_str);

	line = malloc(len + 1);
	if (!line)
		return (NULL);
	ft_strncpy(line, *map_str, len);
	line[len] = '\0';

	if (newline)
		*map_str = newline + 1;
	else
		*map_str += len;

	return (line);
}

int	check_textures_and_color(char **map_str, t_config *config)
{
    char *line;
    char *original_line;
    int len = 0;
    
    while ((line = get_next_line_from_string(map_str)))
    {
        original_line = line;
        if(len == 6)
        {
            free(original_line);
            break;
        }
        skip_space(&line);
        if(line[0] == '\n')
        {
            free(original_line);
            continue;
        }
        if (!*line)
        {
            free(original_line);
            continue;
        }
        if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
            || !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
        {
            if (get_textures(&line, config) == -1)
            {
                free(original_line);
                return (-1);
            }
        }
        else if (*line == 'F' || *line == 'C')
        {
            if (get_colors(&line, config) == -1)
            {
                free(original_line);
                return (-1);
            }
        }
        free(original_line);
        len++;
    }
    if (!config->no_tex || !config->so_tex || !config->we_tex || !config->ea_tex)
            return (-1);
    return (0);
}

/* -------------------- FILE PARSING -------------------- */

int	parse_file(char *filename, t_config *config)
{
	int		fd;
	char	*line;
	char	*tmp;
	char	*all_map;
	char	*map_cursor;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (print_error(ERR_INVALID_PATH), 1);

	config->map = NULL;
	config->map_h = 0;
	config->map_w = 0;
	all_map = NULL;

	while ((line = get_next_line(fd)))
	{
		tmp = all_map;
		all_map = ft_strjoin(tmp ? tmp : "", line);
		free(tmp);
		free(line);
	}
	close(fd);

	if (!all_map)
		return (1);

	map_cursor = all_map;
	if (check_textures_and_color(&map_cursor, config) == -1)
		return (put_error("Invalid textures/colors"), free(all_map), 1);

	// TODO: implement map parsing next
	free(all_map);
	return (0);
}

/* -------------------- PRINT -------------------- */

void	print_config(t_config *config)
{
    printf("\n=== PARSING RESULTS ===\n");
	printf("NO texture: %s\n", config->no_tex ? config->no_tex : "NULL");
	printf("SO texture: %s\n", config->so_tex ? config->so_tex : "NULL");
	printf("WE texture: %s\n", config->we_tex ? config->we_tex : "NULL");
	printf("EA texture: %s\n", config->ea_tex ? config->ea_tex : "NULL");

	printf("Floor RGB: %d,%d,%d\n", config->floor[0], config->floor[1], config->floor[2]);
	printf("Ceiling RGB: %d,%d,%d\n", config->ceil[0], config->ceil[1], config->ceil[2]);
	printf("======================\n\n");
}

/* -------------------- INIT -------------------- */

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

/* -------------------- MAIN -------------------- */

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
	if (game.config.floor[0] == -1 && game.config.floor[1] == -1 && game.config.floor[2] == -1)
		return (put_error("Floor color not set"), 1);
	if (game.config.ceil[0] == -1 && game.config.ceil[1] == -1 && game.config.ceil[2] == -1)
		return (put_error("Ceiling color not set"), 1);
	print_config(&game.config);

	init_game(&game);
    init_player(&game.player, &game.config);
	draw_background(&game);
	raycast(&game, &game.player);
	mlx_key_hook(game.win, handle_keypress, &game);
	mlx_put_image_to_window(game.mlx, game.win, game.img, 0, 0);
	mlx_loop(game.mlx);
	return (0);
}
