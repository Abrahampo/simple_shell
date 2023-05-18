#include "shell.h"

/**
 * input_buf - The buffers to inclosed the commands
 * @info: The structure fo the parameter
 * @buf: the buffer address
* @len: the address of the length
 * Return: bytes
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t a = 0;
	size_t length_v = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		a = getline(buf, &length_v, stdin);
#else
		a = _getline(info, buf, &length_v);
#endif
		if (a > 0)
		{
			if ((*buf)[a - 1] == '\n')
			{
				(*buf)[a - 1] = '\0';
				a--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = a;
				info->cmd_buf = buf;
			}
		}
	}
	return (a);
}

/**
 * get_input - The newline to get and subtract
 * @info: The structure for parameter
 * Return: bytes
 */

ssize_t get_input(info_t *info)
{
	static char *buffer;
	static size_t k, v, le;
	ssize_t ret = 0;
	char **buf_pointer = &(info->arg), *ptr;

	_putchar(BUF_FLUSH);
	ret = input_buf(info, &buffer, &le);
	if (ret == -1)
		return (-1);
	if (le)
	{
		v = k;
		ptr = buffer + k;
		check_chain(info, buffer, &v, k, le);
		while (v < le)
		{
			if (is_chain(info, buffer, &v))
				break;
			v++;
		}
		k = v + 1;
		if (k >= le)
		{
			k = le = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*buf_pointer = ptr;
		return (_strlen(ptr));
	}
	*buf_pointer = buffer;
	return (ret);
}

/**
 * read_buf - the buffer that is ues to read
 * @info: The structure of the parameter
 * @buf: the buffer
 * @i: the integer size
 * Return: just r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t ret = 0;

	if (*i)
		return (0);
	ret = read(info->readfd, buf, READ_BUF_SIZE);
	if (ret >= 0)
		*i = ret;
	return (ret);
}

/**
 * _getline - The STDINPUT that find the valuve from the new or next line
 * @info:  The struct of the parameter
 * @ptr: The of the pointer that is , preallocated maybe NULL
 * @length: the amount or size of the preallocated ptr of buffer that is not NU
 * Return: just y
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t k, le;
	size_t m = 0;
	ssize_t ret = 0, y = 0;
	char *pp = NULL, *new_ptr = NULL, *h;

	pp = *ptr;
	if (pp && length)
		y = *length;
	if (k == le)
		k = le = 0;
	ret = read_buf(info, buffer, &le);
	if (ret == -1 || (ret == 0 && le == 0))
		return (-1);
	h = _strchr(buffer + k, '\n');
	k = h ? 1 + (unsigned int)(h - buffer) : le;
	new_ptr = _realloc(pp, y, y ? y + k : k + 1);
	if (!new_ptr)
		return (pp ? free(pp), -1 : -1);
	if (y)
		_strncat(new_ptr, buffer + k, k - k);
	else
		_strncpy(new_ptr, buffer + k, m - k + 1);

	y += k - m;
	k = m;
	pp = new_ptr;
	if (length)
		*length = y;
	*ptr = pp;
	return (y);
}

/**
 * sigintHandler - The ctrl-C blocks
 * @sig_num: The number of signal or signal number
 * Return: void
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
