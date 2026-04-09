#include "libjr.h"
#include "get_next_line.h"

static char *read_and_stock(int fd, char *stash)
{
    char    *buffer;
    int     bytes;

	// Je créé un tampon de la taille du buffer + 1
    buffer = malloc(BUFFER_SIZE + 1);
	// Si le tampon n'est pas créé je retourne NULL
    if (!buffer)
        return (NULL);
	// J'initailise bytes à 1 pour satisfaire la condition
    bytes = 1;
	// Tant que stash ne contient pas de retour à la ligne
    while (!jr_strchr(stash, '\n') && bytes > 0)
    {
        bytes = read(fd, buffer, BUFFER_SIZE);
		// Si il y a un probleme a la lecture
        if (bytes < 0)
        {
            free(buffer);
            free(stash);
			// Je retourne NULL
            return (NULL);
        }
		// J'ajoute le bit de fin de chaine de character
        buffer[bytes] = '\0';
		// ???
        stash = jr_strjoin(stash, buffer);
    }
    free(buffer);
    return (stash);
}

static char *extract_line(char *stash)
{
    int     i;
    char    *line;

    if (!stash || !stash[0])
        return (NULL);
    i = 0;
	while(stash[i] && stash[i] != '\n')
		i++;
	line = malloc(i + (stash[i] == '\n') + 1);
    if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
    {
        line[i] = stash[i];
        i++;
    } 
    if (stash[i] == '\n')
		line[i++] = '\n';
    line[i] = '\0';
    return (line);
}

static char *clean_stash(char *stash)
{
    int     i;
    int     j;
    char    *new;

    i = 0;
	// Je cherche le retourn à la ligne
    while (stash[i] && stash[i] != '\n')
        i++;
	// Si il n'y en a pas, je libére stash et retourne NULL
    if (!stash[i])
    {
        free(stash);
        return (NULL);
    }
	// Je passe le retour à la ligne
    i++;
	// J'en créé un nouveau
    new = malloc(jr_strlen(stash) - i + 1);
    if (!new)
        return (NULL);
    j = 0;
	// J'ajoute au nouveau le contenu situé après le retour à
	// la ligne
    while (stash[i])
        new[j++] = stash[i++];
    new[j] = '\0';
    free(stash);
    return (new);
}

int	get_next_line(const int fd, char **line)
{
    static char *stash;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (-1);
    stash = read_and_stock(fd, stash);
    if (!stash)
        return (-1);
    *line = extract_line(stash);
    stash = clean_stash(stash);
	if (!*line)
		return (0);
    return (1);
}
