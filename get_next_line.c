/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/08 11:48:43 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/01/08 16:59:08 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strlen(char *input)
{
	int	count;

	count = 0;
	if (!input)
		return (0);
	while (input && input[count])
		count++;
	//printf("strlen of this string:%s\n%d\n", input, count);
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

static void make_leftover(char **leftover, char *endbuf, int len)
{
	int	i;

	i = 0;
	// if (*leftover)
	free(leftover);
	*leftover = malloc(len + 1);
	//printf("leftover:%p\n", leftover);
	while (i < len)
	{
		(*leftover)[i] = endbuf[i];
		i++;
	}
	(*leftover)[i] = '\0';
	//printf("l:%s  ", *leftover);
	return ;
}

char	*make_new(char *out, char *buf, int found, char	**leftover)
{
	char	*new;
	int		outlen;
	int		i;
	int		done;

	i = 0;
	done = 0;
	//printf("out before ft_strlen:%s\n", out);
	outlen = ft_strlen(out);
	//printf("len: %d\n", outlen + found);
	new = malloc(outlen + found + 1);
	//printf("new:%p\n", new);
	if (new == NULL)
		return (out);
	while (i < outlen)
	{
		new[i] = out[i];
		i++;
	}
	while (i < outlen + found)
	{
		new[i] = buf[i - outlen];
		i++;
		if (buf[i - 1 - outlen] == '\n')
		{
			make_leftover(leftover, buf + i - outlen, found - i + outlen);
			break;
		}
	}
	new[i] = '\0';
	//printf("returning this:%s\n", new);
	free (out);
	return (new);
}

char	*get_next_line(int fd)
{
	int			found;
	char		buf[BUFFER_SIZE + 1];
	char		*out;
	static char	*leftover;
	//char	*tmp;
	if (fd < 0)
		return (NULL);
	//if (leftover && leftover[0] == '\0')
	//	free(leftover);
	out = make_new(NULL, leftover, ft_strlen(leftover), &leftover);
	if (newline(out, ft_strlen(out)) != -1)
		return (out);
	//buf = malloc(BUFFER_SIZE + 1);
	// if (buf == NULL)
	// 	return (NULL);
	found = read(fd, buf, BUFFER_SIZE);
	buf[found] = '\0';
	if ((found <= 0 && out == NULL) || found == -1 || (found == 0 && leftover == NULL) || (found == 0 && leftover && leftover[0] == '\0'))
	{
		if (out)
			free (out);
		return (NULL);
	}
	else if (found == 0 && out)
	{
		
		//if (leftover)
		// 	free(leftover);
		return (out);
	}
	//printf("leftover len before sending:%d\n", ft_strlen(leftover));
	while (found == BUFFER_SIZE && newline(buf, found) == -1)
	{
		out = make_new(out, buf, found, &leftover);
		found = read(fd, buf, BUFFER_SIZE);
	}
	out = make_new(out, buf, found, &leftover);
	//printf("found: %d buf: %s out:\n%s", found, buf, out);
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