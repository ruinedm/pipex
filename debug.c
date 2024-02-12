/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 02:03:37 by mboukour          #+#    #+#             */
/*   Updated: 2024/02/12 02:05:07 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "pipex.h"
void print_to_debug(char *str)
{
    int fd = open("debug_file.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Get current time
    time_t rawtime;
    struct tm *info;
    char timestamp[20];
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(timestamp, 20, "%Y-%m-%d %H:%M:%S", info);

    // Marker for the start of a new call
    dprintf(fd, "[%s] NEW CALL\n", timestamp);

    if (!str)
    {
        dprintf(fd, "[%s] ERROR: NULL IN DEBUG\n", timestamp);
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Log message content
    dprintf(fd, "[%s] %s\n", timestamp, str);

    // Marker for the end of a call
    dprintf(fd, "[%s] END CALL\n\n", timestamp);

    close(fd);
}
