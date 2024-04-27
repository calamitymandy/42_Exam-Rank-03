#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

char    *search_char(char *str, int c)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == (char)c)
            return ((char *)str);
        i++;
    }
    return (NULL);
}

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

void    ft_strcpy(char *dst, char *src)
{
    int i = 0;
    while (src[i])
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
}

char    *ft_strdup(char *str)
{
    int len = ft_strlen(str) + 1;
    char    *dest = malloc(len);

    if (dest == NULL)
        return (NULL);
    ft_strcpy(dest, str);
    return (dest);
}

char    *ft_join(char *s1, char *s2)
{
    char *join = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    int i = 0;
    int j = 0;

    while (s1[i])
    {
        join[i] = s1[i];
        i++;
    }
    while(s2[j])
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
    static char buffer[BUFFER_SIZE + 1];
    char    *line;
    char    *newline;
    int     buf_len;
    int     newline_len;

    line = ft_strdup(buffer);
    while(!(newline = search_char(line, '\n')) && (buf_len = read(fd, buffer, BUFFER_SIZE)))
    {
        buffer[buf_len] = '\0';
        line = ft_join(line, buffer);
    }
    if (ft_strlen(line) == 0)
        return (free(line), NULL);
    if (newline != NULL)
    {
        newline_len = newline - line + 1;
        ft_strcpy(buffer, newline + 1);
    }
    else 
    {
        newline_len = ft_strlen(line);
        buffer[0] = '\0';
    }
    line[newline_len] = '\0';
    return (line);
}
/*
int main(int argc, char **argv)
{
    (void)argc;
    char *line;
    int fd;

    fd = open(argv[1], BUFFER_SIZE);
    line = get_next_line(fd);
    while (line)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
}
*/