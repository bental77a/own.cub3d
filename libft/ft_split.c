/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:15:55 by mohben-t          #+#    #+#             */
/*   Updated: 2025/10/01 14:15:56 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count(char const *s, char c)
{
	int	i;
	int	count;
	int	next;

	i = 0;
	count = 0;
	next = 1;
	while (s[i])
	{
		if (s[i] != c && next == 1)
		{
			next = 0;
			count++;
		}
		else if (s[i] == c)
		{
			next = 1;
		}
		i++;
	}
	return (count);
}

char	*copy(char *str, int start, int end)
{
	char	*word;
	int		i;

	word = (char *)malloc((end - start + 2) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	int i, (start), (word), (j);
	if (!s)
		return (NULL);
	word = count(s, c);
	result = (char **)malloc((word + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (start < i)
			result[j++] = copy((char *)s, start, i);
	}
	result[j] = (NULL);
	return (result);
}
