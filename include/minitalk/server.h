#ifndef SERVER_H
# define SERVER_H

typedef struct s_string
{
	size_t			length;
	size_t			cap;
	unsigned char	*chrs;

}	t_string;

typedef struct s_server
{
	int				sig_count;
	t_string		*string;
	unsigned char	chr;

}	t_server;

t_string	*string_new(size_t size);
void		string_append(t_string *string, const int c);
void		string_print(t_string *string);

#endif
