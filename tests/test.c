/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/12 13:56:40 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/01/24 16:22:03 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    int fd1 = open("test.txt", O_RDONLY);
    int fd2 = open("test2.txt", O_RDONLY);
    int fd3 = open("test3.txt", O_RDONLY);
    int fd4 = open("test4.txt", O_RDONLY);
    int i = 0;
    char *nl;
    
    while (i < 10)
    {
        nl = get_next_line(fd1);
        printf("gnl:%s", nl);
        i++;
    }
    i = 0;
    while (i < 10)
    {
        nl = get_next_line(fd2);
        printf("gnl:%s", nl);
        i++;
    }
    i = 0;
    while (i < 10)
    {
        nl = get_next_line(fd3);
        printf("gnl:%s", nl);
        i++;
    }
    i = 0;
    while (i < 10)
    {
        nl = get_next_line(fd4);
        printf("gnl:%s", nl);
        i++;
    }
    close (fd1);
    close (fd2);
    close (fd3);
    close (fd4);
}
