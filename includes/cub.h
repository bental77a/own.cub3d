/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:13:36 by mohben-t          #+#    #+#             */
/*   Updated: 2025/11/06 17:17:44 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include "get_next_line.h"
# include "libft.h"
# include <math.h>
# include <mlx.h>

# define  WIDTH 1024
# define  HEIGHT 700

# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
#define KEY_ESC    65307

# define PI 3.14159265359

# define ERR_INVALID_PATH    1
# define ERR_INVALID_EXT     2
# define ERR_INVALID_RGB     3
# define ERR_INVALID_MAP     4
# define ERR_MISSING_TEXTURE 5
# define ERR_MISSING_COLOR   6
# define ERR_NO_PLAYER       7
# define ERR_MULTIPLAYER     8
# define ERR_UNKNOWN         99

#define COLOR_CEILING 0x87CEEB
#define COLOR_FLOOR   0x228B22
#define COLOR_WALL    0xFFD700

# define INVALID_PATH        "Error\nInvalid file path"
# define INVALID_EXT         "Error\nInvalid file extension"
# define USAGE_ERR           "Error\nUsage: ./cub3D <file.cub>"

typedef struct s_config
{
    char	*no_tex;
    char	*so_tex;
    char	*we_tex;
    char	*ea_tex;
    int		floor[3];
    int		ceil[3];
    char	**map;
    int		map_h;
    int		map_w;
    int		player_x;
    int		player_y;
    char	player_dir;
}	t_config;


typedef struct s_player {
    //float x;    
    //float y;     
    float angle;
    double  x;
    double  y;
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;
    bool key_up;
    bool key_down;
    bool key_left;
    bool key_right;

    bool left_rotate;
    bool right_rotate;  
}   t_player;

typedef struct s_game
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *img_data;
    int     img_width;
    int     img_height;
    int     bpp;
    int     line_len;
    int     endian;
    char	**map;
    t_config config;
    t_player player;
}   t_game;



void	measure_map(char **arr, t_config *config);
int	load_map_content(int fd, char **all_map);
int	append_line(char **buffer, char *line);
int	is_valid_map_char(char c);
void	skip_space(char **str);
int	get_len(char *str);
char	*get_path_textures(char **str);
void	free_textures(t_config *config);
int	get_colors(char **str, t_config *config);
int	get_color(char **str, int color[3]);
int	parse_component(char **str, int *value);
int	get_textures(char **str, t_config *config);
int	handle_identifier_line(char **cursor, t_config *config);
int find_tall_line(char **str);
int	find_consecutive_newlines(const char *str);
char *skip_lines(char **str);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
bool is_valid_neighbor(char cell, char pos_pl);
bool check_map(int i, int j, char **map, char pos_pl);
int	check_last_zero(char **map, char pos_pl);
char find_player_char(char **map);
int	check_map_walls(char **map, int height);
char	*get_next_line_from_string(char **map_str);
int check_reachble(char **arr, t_config *config);
int	check_textures_and_color(char **map_str, t_config *config);
int line_valide(char *line);
int	border_valid(char c);
void free_array(char **arr);
char	**resize_line(char **arr,int size, int height);
char *ft_strndup(char *s1, int size);
int		has_cub_extension(char *path);
int		is_player_char(char c);
int		parse_file(char *filename, t_config *config);
void	print_error(int code);
int parse_map(char **map_cursor, t_config *config);
void	put_error(char *msg);
int	find_consecutive_newlines(const char *str);


//void init_player(t_player *player);
//void put_pixel(int x, int y, int color, t_game *game);
// int key_press(int keycode, t_player *player);
// int key_release(int keycode, t_player *player);
void move_player(t_player *player);
int rgb_to_int(int r, int g, int b);
void draw_background(t_game *game);


//GAME
void init_game(t_game *game);
void init_player(t_player *player, t_config *config);
void put_pixel(t_game *game, int x, int y, int color);
void raycast(t_game *game, t_player *player);


// PLAYER
int is_empty_cell(t_game *game, double x, double y);
void move_forward(t_game *game);
void move_backward(t_game *game);
void strafe_left(t_game *game);
void strafe_right(t_game *game);
void rotate_left(t_game *game);
void rotate_right(t_game *game);

// HOOKS
int handle_keypress(int keycode, t_game *game);


#endif