#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <limits.h>

#include "minitalk/server.h"

t_server	server;

static void	sig_epilogue(void)
{
	if (++server.sig_count == CHAR_BIT)
	{
		if (server.chr == '\0')
		{
			string_print(server.string);
			server.string->length = 0;
		}
		else
			string_append(server.string, server.chr);
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

/* 0 */

void	sigusr1_handler(int sig)
{
	sig_epilogue();
	//printf("sig1\n");
}

/* 1 */

void	sigusr2_handler(int sig)
{
	server.chr |= (1 << server.sig_count);
	//printf("sig2\n");
	sig_epilogue();
}

int	main(void)
{
	server.sig_count = 0;
	server.string = string_new(1000);
	server.chr = '\0';
	signal(SIGUSR1, &sigusr1_handler);
	signal(SIGUSR2, &sigusr2_handler);
	print_pid(getpid());
	write(1, "\n", 1);
	while (1)
		sleep(1000);
}
