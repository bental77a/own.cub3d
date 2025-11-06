/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:09:18 by mohben-t          #+#    #+#             */
/*   Updated: 2025/11/06 12:09:56 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

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
	int	len;

	len = 0;
	while (str[len] && str[len] != ' ' && str[len] != '\t' && str[len] != '\n')
		len++;
	return (len);
}
