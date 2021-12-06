/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foulare <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 17:44:53 by foulare           #+#    #+#             */
/*   Updated: 2021/12/06 17:45:40 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
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
		str = ft_strjoin_pipe(path[i], cmd[0]);
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

void	ft_file(char **arg, int ac, int *df, int *i)
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
	*i = 1;
}

void	ft_execve(char *arg, char **path)
{
	char	*str;
	char	**cmd;

	cmd = ft_split(arg, ' ');
	str = getpath(path, cmd);
	execve(str, cmd, NULL);
}

void	ft_pipex(char *arg, char **path, int *fd)
{
	pid_t	pid;

	if (pipe(fd) < 0)
		ft_perror("pipe");
	pid = fork();
	if (pid < 0)
		ft_perror("fork");
	if (pid)
	{
		waitpid(pid, NULL, 0);
		close(fd[1]);
		dup2(fd[0], 0);
		if (access(".heredoc", F_OK) == 0)
			unlink(".heredoc");
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], 1);
		ft_execve(arg, path);
	}
}

int	main(int ac, char **arg, char **envp)
{
	int		i;
	char	**path;
	int		fd[2];
	int		df[2];
	int		p;

	if (ac < 5)
		ft_perror("nombre d'argument invalide");
	if (!ft_strncmp("here_doc", arg[1], ft_strlen(arg[1])) && ac == 6)
		here_doc(ac, arg, df, &i);
	else
		ft_file(arg, ac, df, &i);
	p = -1;
	while (envp[++p])
		if (!ft_strncmp(envp[p], "PATH=", 5))
			break ;
	path = ft_split(&envp[p][5], ':');
	dup2(df[0], 0);
	while (ac - 2 > ++i)
		ft_pipex(arg[i], path, fd);
	dup2(df[1], 1);
	ft_execve(arg[ac - 2], path);
	return (0);
}
