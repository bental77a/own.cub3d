#include "libft.h"

char *ft_strdup(const char *s1, int size)
{
    char *dup;
    int i;
    int j;
    int len;

    if (!s1)
        return (NULL);
    len = ft_strlen(s1);
    dup = malloc(sizeof(char) * (len + size + 1));
    if (!dup)
        return (NULL);
    for (i = 0; i < len; i++)
        dup[i] = s1[i];
    for (j = 0; j < size; j++)
        dup[i + j] = '1';
    dup[i + size] = '\0';
    return (dup);
}