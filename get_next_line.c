/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/08 11:48:43 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/01/11 22:10:25 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//LITTLE COMMENT TO READER: MAKE_NEW is something like strjoin, MAKE_LEFTOVER like strlcpy, NEWLINE like strchr and STRLEN a simple version of strlen

static int	ft_strlen(char *input)
{
	int	count;

	count = 0;
	if (!input)
		return (0);
	while (input && input[count])
		count++;
	return (count);
}

static int	newline(char *buf, int found)
{
	int	i;

	i = 0;
	while (i < found)
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

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

char	*make_new(char *out, char *buf, int found, char	*leftover)
{
	char	*new;
	int		outlen;
	int		i;

	i = 0;
	outlen = ft_strlen(out);
	new = malloc(outlen + found + 1);
	if (new == NULL)
		return (out);
	while (i < outlen + found)
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

	out = make_new(NULL, leftover, ft_strlen(leftover), leftover);
	if (newline(out, ft_strlen(out)) != -1)
		return (out);
	found = read(fd, buf, BUFFER_SIZE);
	if (found == -1 || out == NULL || (found == 0 && leftover[0] == '\0'))
	{
		free(out);
		return (NULL);
	}
	while (found == BUFFER_SIZE && newline(buf, found) == -1)
	{
		out = make_new(out, buf, found, leftover);
		found = read(fd, buf, BUFFER_SIZE);
	}
	out = make_new(out, buf, found, leftover);
	if (newline(out, ft_strlen(out)) == -1)
		leftover[0] = '\0';
	return (out);
}

// /*
// 	READ
// 		- read x bytes from the object referenced by the fd into the buffer

// 		RETURN VALUES
// 		- number of byter actually read
// 		- zero upon reading end-of-file
// 		- -1 if an error occured

// 	MALLOC
// 		- allocates memory that can be used for any data type
// 		- allocates x bytes of memory and returns pointer to allocated memory

// 		RETURN VALUES
// 		- if succesfoll, malloc returns a pointer to allocated memory
// 		- if there is an error, malloc returns NULL

// 	FREE 
// 		- frees allocations that were created via the malloc function

// 		RETURN VALUE
// 		- free does not return a value
// */