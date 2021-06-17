#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <limits.h>

#include "minitalk/server.h"

t_server	server;

/*
** Handler for SIGUSR1 and SIGUSR2
*/

static void	sig_handler(int sig)
{
	if (sig == SIGUSR2)
		server.chr |= (1 << server.sig_count);
	if (++server.sig_count == CHAR_BIT)
	{
		if (server.chr == '\0')
		{
			string_print(server.string);
			server.string->length = 0;
		}
		else
		{
			string_append(server.string, server.chr);
		}
		server.chr = '\0';
		server.sig_count = 0;
	}
}

/*
** Print the pid using a dirty recursive method, using many
** write syscalls. We don't care about using such a method to print
** the pid as it is only done when the server is fired up for the first
** time.
*/

static void	print_pid(int pid)
{
	if (pid > 9)
	{
		print_pid(pid / 10);
		print_pid(pid % 10);
	}
	else
	{
		pid += 48;
		write(1, &pid, 1);
	}
}

static void	sig_setup(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = &sig_handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
}

int	main(void)
{
	sig_setup();
	server.sig_count = 0;
	server.string = string_new(2000);
	if (server.string == NULL)
		return (1);
	server.chr = '\0';
	print_pid(getpid());
	write(1, "\n", 1);
	while (1)
		pause();
}
