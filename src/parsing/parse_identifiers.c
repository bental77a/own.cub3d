/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:12:53 by mohben-t          #+#    #+#             */
/*   Updated: 2025/11/06 11:37:24 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

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

char	*skip_lines(char **str)
{
	while (**str && **str == '\n')
		(*str)++;
	return (*str);
}

int	find_consecutive_newlines(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' && str[i + 1] == '\n')
		{
			while (str[i] && str[i] == '\n')
				i++;
			if (str[i] == '1' || str[i] == '0' || str[i] == ' ')
				return (1);
			return (0);
		}
		str++;
	}
	return (0);
}

int	find_tall_line(char **str)
{
	int	i;
	int	len;
	int	max_len;

	i = 0;
	max_len = 0;
	while (str[i])
	{
		len = ft_strlen(str[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	return (max_len);
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
