#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>

#include "minitalk/client.h"

static int	parse_pid(const char *s)
{
	int	sign;
	int	pid;

	sign = 1;
	pid = 0;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		++s;
	}
	while (*s >= '0' && *s <= '9')
		pid = pid * 10 + (*s++ - 48);
	if (*s != '\0')
		return (-1);
	return (pid * sign);
}

/*
** SIG_USR2 is used to pass bits that are set.
** SIG_USR1 is used to pass bits that are not set.
**
** The server will rebuild the string on its own using these two
** signals.
*/

static void	send_string_to_server(int pid, const char *s)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < CHAR_BIT)	
		{
			if (*s & (1 << i))
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			++i;
			usleep(100);
		}
		if (*s == '\0')
			break ;
		++s;
	}
}

int main(int argc, char *argv[])
{
	int	pid;

	if (argc != 3)
	{
		write(STDERR_FILENO, ERROR_USAGE, ERROR_USAGE_LEN);
		return (1);
	}
	pid = parse_pid(argv[1]);
	if (pid == -1)
	{
		write(STDERR_FILENO, ERROR_INVALID_PID, ERROR_INVALID_PID_LEN);
		return (2);
	}
	send_string_to_server(pid, argv[2]);
}
