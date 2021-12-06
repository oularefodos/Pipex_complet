/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foulare <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:52:46 by foulare           #+#    #+#             */
/*   Updated: 2021/12/06 17:45:01 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

char	*getpath(char **path, char **cmd)
{
	char	*str;
	int		i;
	int		p;

	p = 0;
	i = -1;
	while (path[++i])
	{
		str = ft_strjoin(path[i], cmd[0]);
		if (access(str, X_OK) == 0)
		{
			p++;
			break ;
		}
		free(str);
	}
	if (p == 0)
		ft_perror("commande invalide");
	return (str);
}

void	ft_file(char **arg, int ac, int *df)
{
	int	first;
	int	last;

	if (access(arg[ac - 1], F_OK) == 0)
		unlink(arg[ac - 1]);
	first = open(arg[1], O_RDONLY);
	if (first < 0)
		ft_perror("file");
	last = open(arg[ac - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (last < 0)
		ft_perror("file");
	df[0] = first;
	df[1] = last;
}

void	ft_execve(char *arg, char **path)
{
	char	*str;
	char	**cmd;

	cmd = ft_split(arg, ' ');
	str = getpath(path, cmd);
	execve(str, cmd, NULL);
}

void	ft_pipex(char **arg, char **path, int *fd, int *df)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_perror("fork");
	if (pid)
	{
		waitpid(pid, NULL, 0);
		close(fd[1]);
		dup2(fd[0], 0);
		dup2(df[1], 1);
	}
	else
	{
		close(fd[0]);
		dup2(df[0], 0);
		dup2(fd[1], 1);
		ft_execve(arg[2], path);
	}
}

int	main(int ac, char **arg, char **envp)
{
	int		i;
	int		ret;
	char	**path;
	int		fd[2];
	int		df[2];

	if (ac != 5)
		ft_perror("nombre d'argument inavalide");
	ft_file(arg, ac, df);
	ret = pipe(fd);
	if (ret < 0)
		ft_perror("pipe");
	i = -1;
	while (envp[++i])
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
	path = ft_split(&envp[i][5], ':');
	ft_pipex(arg, path, fd, df);
	ft_execve(arg[3], path);
	return (0);
}
