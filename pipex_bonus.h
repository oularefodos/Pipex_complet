/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: foulare <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 17:45:54 by foulare           #+#    #+#             */
/*   Updated: 2021/12/05 19:52:47 by foulare          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <stddef.h>

char			**ft_split(const char *s, char c);
char			*ft_strjoin_pipe(char const *s1, char const *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strdup(char *src);
char			*ft_strchr(char *str, int c);
char			*get_next_line(int fd);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_substr(char *s, unsigned int start, size_t len);
void			here_doc(int ac, char **arg, int *df, int *i);
unsigned int	ft_strlen(const char *str);
void			ft_perror(char *str);
#endif
