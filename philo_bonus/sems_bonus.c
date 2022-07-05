/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sems_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 12:31:42 by ckarol            #+#    #+#             */
/*   Updated: 2022/07/04 12:31:43 by ckarol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

sem_t	*my_ssopen(const char *s, int st_value)
{
	return (sem_open(s, O_CREAT | O_EXCL, 0644, st_value));
}

static int	ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = 0;
	return (i);
}

char	*name_constructor(int pos, char *dst, const char *src)
{
	int	i;

	i = ft_strcpy(dst, src);
	while (pos)
	{
		dst[i] = (pos % 24) + 'a';
		pos /= 24;
		i++;
	}
	dst[i] = 0;
	return (dst);
}
