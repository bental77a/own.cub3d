#include "../../includes/cub.h"

int	append_line(char **buffer, char *line)
{
	char	*tmp;
	char	*joined;

	tmp = *buffer;
	joined = ft_strjoin(tmp ? tmp : "", line);
	free(tmp);
	if (!joined)
		return (-1);
	*buffer = joined;
	return (0);
}

int	load_map_content(int fd, char **all_map)
{
	char	*line;

	*all_map = NULL;
	while ((line = get_next_line(fd)))
	{
		if (append_line(all_map, line) == -1)
		{
			free(line);
			free(*all_map);
			*all_map = NULL;
			return (-1);
		}
		free(line);
	}
	return (0);
}

void	measure_map(char **arr, t_config *config)
{
	int		i;
	size_t	len;

	config->map_h = 0;
	config->map_w = 0;
	i = 0;
	while (arr[i])
	{
		len = ft_strlen(arr[i]);
		if ((int)len > config->map_w)
			config->map_w = len;
		i++;
	}
	config->map_h = i;
}