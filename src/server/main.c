#include <unistd.h>
#include <stdio.h>
#include <signal.h>

#include "minitalk/server.h"

t_server	server;

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

void	sigusr1_handler(int sig)
{
	string_append(server.string, '0');
}

void	sigusr2_handler(int sig)
{
	string_append(server.string, '1');
}

int	main(void)
{
	server.sig_count = 0;
	server.string = string_new(1000);
	signal(SIGUSR1, &sigusr1_handler);
	signal(SIGUSR2, &sigusr2_handler);
	print_pid(getpid());
	write(1, "\n", 1);
	string_append(server.string, 'a');
	string_append(server.string, 'b');
	string_append(server.string, 'b');
	string_append(server.string, 'b');
	string_append(server.string, 'b');
	string_append(server.string, 'b');
	string_print(server.string);
}
