#include "shell.h"

/**
 * get_history_file - The file or files history to find or get
 * @info: The structure of a parameter
 * Return: The history of a file that takes string as an allocated ones.
 */

char *get_history_file(info_t *info)
{
	char *bb, *atlas;

	atlas = _getenv(info, "HOME=");

	if (!atlas)
		return (NULL);
	bb = malloc(sizeof(char) * (_strlen(atlas) + _strlen(HIST_FILE) + 2));
	if (!bb)
		return (NULL);
	bb[0] = 0;
	_strcpy(bb, atlas);
	_strcat(bb, "/");
	_strcat(bb, HIST_FILE);
	return (bb);
}

/**
 * write_history - The file or files that creates, or put to an existing file.
 * @info: The structure of the parameter
 * Return: 1 for success, or -1 for fail.
 */

int write_history(info_t *info)
{
	ssize_t ffdd;
	char *fk = get_history_file(info);
	list_t *knot = NULL;

	if (!fk)
		return (-1);
	ffdd = open(fk, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fk);
	if (ffdd == -1)
		return (-1);
	for (knot = info->history; knot; knot = knot->next)
	{
		_putsfd(knot->str, ffdd);
		_putfd('\n', ffdd);
	}
	_putfd(BUF_FLUSH, ffdd);
	close(ffdd);
	return (1);
}

/**
 * read_history - The file that reads the history from.
 * @info:  The structure that takes a parameter
 * Return: success for his_count, or 0 else.
 */

int read_history(info_t *info)
{
	int k, least = 0, lc = 0;
	ssize_t ffdd, len_rd, f_s = 0;
	struct stat procee;
	char *bb = NULL, *fk = get_history_file(info);

	if (!fk)
		return (0);
	ffdd = open(fk, O_RDONLY);
	free(fk);
	if (ffdd == -1)
		return (0);
	if (!fstat(ffdd, &procee))
		f_s = procee.st_size;
	if (f_s < 2)
		return (0);
	bb = malloc(sizeof(char) * (f_s + 1));
	if (!bb)
		return (0);
	len_rd = read(ffdd, bb, f_s);
	bb[f_s] = 0;
	if (len_rd <= 0)
		return (free(bb), 0);
	close(ffdd);
	for (k = 0; k < f_s; k++)
		if (bb[k] == '\n')
		{
			bb[k] = 0;
			build_history_list(info, bb + least, lc++);
			least = k + 1;
		}
	if (least != k)
		build_history_list(info, bb + least, lc++);
	free(bb);
	info->histcount = lc;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - The entry to add a history to linked list
 * @info: Structure containing potential arguments.
 * @buf: Just the buffer
 * @linecount: This line is just for hist_count or line_count of a history
 * Return: just 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *knot = NULL;

	if (info->history)
		knot = info->history;
	add_node_end(&knot, buf, linecount);
	if (!info->history)
		info->history = knot;
	return (0);
}

/**
 * renumber_history - It changes afetr the linked list of a history has been rn
 * @info: Structure containing potential arguments.
 * Return: Just new hist_count
 */

int renumber_history(info_t *info)
{
	list_t *knot = info->history;
	int k = 0;

	while (knot)
	{
		knot->num = k++;
		knot = knot->next;
	}
	return (info->histcount = k);
}
