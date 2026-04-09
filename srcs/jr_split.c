#include "jr_split.h"

static int  is_sep(char c, char sep)
{
    return (c == sep);
}

static int  count_words(const char *s, char sep)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (s[i])
    {
        if (!is_sep(s[i], sep) && (i == 0 || is_sep(s[i - 1], sep)))
            count++;
        i++;
    }
    return (count);
}

static char *word_dup(const char *s, int start, int end)
{
    char    *word;
    int     i;

    word = malloc(sizeof(char) * (end - start + 1));
    if (!word)
        return (NULL);
    i = 0;
    while (start < end)
        word[i++] = s[start++];
    word[i] = '\0';
    return (word);
}

static void free_all(char **tab, int i)
{
    while (i >= 0)
        free(tab[i--]);
    free(tab);
}

char    **jr_split(const char *s, char sep)
{
    char    **tab;
    int     i;
    int     j;
    int     start;

    tab = malloc(sizeof(char *) * (count_words(s, sep) + 1));
    if (!tab)
        return (NULL);
    i = 0;
    j = 0;
    while (s[i])
    {
        if (!is_sep(s[i], sep))
        {
            start = i;
            while (s[i] && !is_sep(s[i], sep))
                i++;
            tab[j] = word_dup(s, start, i);
            if (!tab[j])
                return (free_all(tab, j - 1), NULL);
            j++;
        }
        else
            i++;
    }
    tab[j] = NULL;
    return (tab);
}
