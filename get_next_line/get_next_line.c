#include "get_next_line.h"

char    *get_next_line(int fd)
{
    int i = 0;
    int bytes;
    char    *buffer;
    char    character;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);
    bytes = read(fd, &character, 1);
    while (bytes > 0)
    {
        buffer[i++] = character;
        if (character == '\n')
            break;
        bytes = read(fd, &character, 1);
    }
    if (bytes < 0 || i == 0)
        return (free(buffer), NULL);
    buffer[i] = '\0';
    return (buffer);
}

int main(int argc, char **argv)
{
    (void)argc;
    char *line;
    int fd;

    fd = open(argv[1], BUFFER_SIZE);
    line = get_next_line(fd);
    while (line)
    {
        printf("%s\n", line);
        free(line);
        line = get_next_line(fd);
    }
}