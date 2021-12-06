/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foulare <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 17:31:52 by foulare           #+#    #+#             */
/*   Updated: 2021/12/06 17:41:45 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "pipex_bonus.h"

static int	ft_getlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin_pipe(char const *s1, char const *s2)
{
	int		len;
	char	*tab;
	int		i;

	i = -1;
	if (!s1 || !s2)
		return (0);
	len = ft_getlen(s1) + ft_getlen(s2) + 2;
	tab = (char *)malloc(sizeof(char) * (len));
	if (!tab)
		ft_perror("erreur d'allocation");
	while (s1[++i])
		tab[i] = s1[i];
	tab[i++] = '/';
	len = 0;
	while (s2[len])
	{
		tab[i] = s2[len];
		i++;
		len++;
	}
	tab[i] = '\0';
	return (tab);
}
