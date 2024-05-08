#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

char    *search_char(char *str, int c)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == (char)c)
            return ((char *)str + i);
        i++;
    }
    return NULL;
}

void    ft_strcpy(char *dest, const char *src)
{
    int i = 0;
    while(src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

size_t  ft_strlen(const char *str)
{
    size_t  i = 0;

    while (str[i])
        i++;
    return (i);
}

char    *ft_strdup(const char *str)
{
    int len = ft_strlen(str) + 1;
    char *res = malloc(len);

    if (res == NULL)
        return (NULL);
    ft_strcpy(res, str);
    return (res);
}

char    *ft_strjoin(char *s1, const char *s2)
{
    size_t len = ft_strlen(s1) + ft_strlen(s2);
    char    *join = malloc(sizeof(char *) * len + 1);
    int i = 0;
    int j = 0;

    if (!s1 || !s2 || !join)
        return (NULL);

    while (s1[i])
    {
        join[i] = s1[i];
        i++;
    }
    while (s2[j])
    {
        join[i] = s2[j];
        i++;
        j++;
    }
    join[i] = '\0';
    free(s1);
    return (join);
}

char    *get_next_line(int fd)
{
    static char buf[BUFFER_SIZE + 1];
    char    *line;
    char    *newline;
    int     buf_len;
    int     newline_len;

    line = ft_strdup(buf);
    while(!(newline = search_char(line, '\n')) && (buf_len = read(fd, buf, BUFFER_SIZE)))
    {
        if (buf_len == -1)
        {
            free(line);
            return (NULL);
        }
        buf[buf_len] = '\0';
        line = ft_strjoin(line, buf);
    }
    if (ft_strlen(line) == 0)
        return (free(line), NULL);
    if (newline != NULL)
    {
        newline_len = newline - line + 1;
        ft_strcpy(buf, newline + 1);
    }
    else
    {
        newline_len = ft_strlen(line);
        buf[0] = '\0';
    }

    line[newline_len] = '\0';
    return (line);
}
/*
int main(int argc, char **argv)
{
    (void)argc;
    char    *line;
    int     fd;

    fd = open (argv[1], O_RDONLY);
    line = get_next_line(fd);
    while (line)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
}
*/