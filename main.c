#include "shell.h"

/**
 * main - Just for entry point or points
 * @ac: The counting of the argument or args.
 * @av: This is the vector for the argument.
 * Return: Just 0 for success, and 1 for error or error
 */

int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int ffdd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (ffdd)
			: "r" (ffdd));

	if (ac == 2)
	{
		ffdd = open(av[1], O_RDONLY);
		if (ffdd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = ffdd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
