/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/08 11:48:31 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/01/12 12:44:51 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_strlen(char *input)
{
	int	count;

	count = 0;
	if (!input)
		return (0);
	while (input && input[count])
		count++;
	return (count);
}

int	newline(char *buf, int found)
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
