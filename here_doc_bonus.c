/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foulare <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 17:42:11 by foulare           #+#    #+#             */
/*   Updated: 2021/12/05 20:44:53 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex_bonus.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

void	ft_file_heredoc(char **arg, int ac, int *df)
{
	int	first;
	int	last;

	first = open(".heredoc", O_WRONLY | O_CREAT, 0644);
	if (first < 0)
		ft_perror("file");
	last = open(arg[ac - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (last < 0)
		ft_perror("file");
	df[0] = first;
	df[1] = last;
}

void	here_doc(int ac, char **arg, int *df, int *i)
{
	char	*line;

	ft_file_heredoc(arg, ac, df);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(1);
		if (ft_strncmp(line, arg[2], ft_strlen(arg[2])) == 0)
			break ;
		write (df[0], line, ft_strlen(line));
		free(line);
	}
	close(df[0]);
	df[0] = open(".heredoc", O_RDONLY);
	if (df[0] < 0)
		ft_perror("file");
	*i = 2;
}
