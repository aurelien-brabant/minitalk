#include <stdlib.h>
#include <unistd.h>

#include "minitalk/server.h"

static int	resize(t_string *string)
{
	unsigned char	*new_chrs;
	size_t			i;

	string->cap *= 2;
	new_chrs = malloc(sizeof (*new_chrs) * string->cap);
	if (new_chrs == NULL)
		return (1);
	i = 0;
	while (i < string->length)
	{
		new_chrs[i] = string->chrs[i];
		++i;
	}
	free(string->chrs);
	string->chrs = new_chrs;
	return (0);
}

t_string	*string_new(size_t cap)
{
	t_string	*string;

	string = malloc(sizeof (*string));
	if (string == NULL)
		return (NULL);
	string->chrs = malloc(sizeof (*string->chrs) * cap);
	if (string->chrs == NULL)
		return (NULL);
	string->length = 0;
	string->cap = cap;
	return (string);
}

void	string_append(t_string *string, const int c)
{
	if (string->length == string->cap)
	{
		if (resize(string) != 0)
			return ;
	}
	string->chrs[string->length++] = c;
}

void	string_print(t_string *string)
{
	write(STDOUT_FILENO, string->chrs, string->length);
	write(STDOUT_FILENO, "\n", 1);
}
