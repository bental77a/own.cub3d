/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:08:23 by houarrak          #+#    #+#             */
/*   Updated: 2025/11/06 12:04:32 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

char	*ft_strndup(char *s1, int size)
{
	char	*dup;
	int		i;
	int		j;
	int		len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	dup = malloc(sizeof(char) * (len + size + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < size)
	{
		dup[i + j] = ' ';
		j++;
	}
	dup[i + size] = '\0';
	return (dup);
}

char	**resize_line(char **arr, int size, int height)
{
	int		resize;
	int		i;
	char	**str;

	str = malloc(sizeof(char *) * (height + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		resize = size - ft_strlen(arr[i]);
		str[i] = ft_strndup(arr[i], resize);
		if (!str[i])
		{
			while (i > 0)
				free(str[--i]);
			free(str);
			return (NULL);
		}
		i++;
	}
	str[i] = NULL;
	return (str);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	border_valid(char c)
{
	return (c == '1' || c == ' ');
}

int	line_valide(char *line)
{
	int	i;

	if (!line || !*line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
