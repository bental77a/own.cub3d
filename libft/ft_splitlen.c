/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohben-t <mohben-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 14:16:01 by mohben-t          #+#    #+#             */
/*   Updated: 2025/10/01 14:16:02 by mohben-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_splitlen(char **split)
{
	int	len;

	if (!split)
		return (0);
	len = 0;
	while (split[len])
		len++;
	return (len);
}
