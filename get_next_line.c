/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/08 11:48:43 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/01/12 12:38:26 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	make_leftover(char *leftover, char *endbuf, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		leftover[i] = endbuf[i];
		i++;
	}
	leftover[i] = '\0';
	return ;
}

static char	*make_new(char *out, char *buf, int found, char	*leftover)
{
	char	*new;
	int		outlen;
	int		i;

	i = 0;
	outlen = gnl_strlen(out);
	new = malloc(outlen + found + 1);
	while (new != NULL && i < outlen + found)
	{
		if (i < outlen)
			new[i] = out[i];
		else
			new[i] = buf[i - outlen];
		i++;
		if (i > outlen && buf[i - 1 - outlen] == '\n')
		{
			make_leftover(leftover, buf + i - outlen, found - i + outlen);
			break ;
		}
	}
	if (new != NULL)
		new[i] = '\0';
	free(out);
	return (new);
}

char	*get_next_line(int fd)
{
	int			found;
	char		*out;
	char		buf[BUFFER_SIZE + 1];
	static char	leftover[BUFFER_SIZE + 1];

	out = make_new(NULL, leftover, gnl_strlen(leftover), leftover);
	if (out == NULL || newline(out, gnl_strlen(out)) != -1)
		return (out);
	found = read(fd, buf, BUFFER_SIZE);
	if (found == -1 || (found == 0 && leftover[0] == '\0'))
	{
		free(out);
		return (NULL);
	}
	while (found == BUFFER_SIZE && newline(buf, found) == -1)
	{
		out = make_new(out, buf, found, leftover);
		if (out == NULL)
			return (NULL);
		found = read(fd, buf, BUFFER_SIZE);
	}
	out = make_new(out, buf, found, leftover);
	if (out != NULL && newline(out, gnl_strlen(out)) == -1)
		leftover[0] = '\0';
	return (out);
}

/*
	READ
		- read x bytes from the object referenced by the fd into the buffer

		RETURN VALUES
		- number of byter actually read
		- zero upon reading end-of-file
		- -1 if an error occured

	MALLOC
		- allocates memory that can be used for any data type
		- allocates x bytes of memory and returns pointer to allocated memory

		RETURN VALUES
		- if succesfull, malloc returns a pointer to allocated memory
		- if there is an error, malloc returns NULL

	FREE 
		- frees allocations that were created via the malloc function

		RETURN VALUE
		- free does not return a value
*/