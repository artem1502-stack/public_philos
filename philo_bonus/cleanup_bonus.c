/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 12:31:03 by ckarol            #+#    #+#             */
/*   Updated: 2022/07/04 12:31:04 by ckarol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	final_free(t_data *data, const char *s)
{
	int		i;
	char	buff[300];

	sem_unlink(PHILO_INF_FORK);
	sem_unlink(PHILO_INF_WRITE);
	sem_unlink(PHILO_INF_DEADS);
	sem_unlink(PHILO_INF_DEADW);
	if (data->philos)
	{
		i = -1;
		while (++i < data->num_philos)
		{
			name_constructor(i, (char *)buff, PHILO_STD_NAME);
			sem_unlink(buff);
			name_constructor(i, (char *)buff, PHILO_STD_EAT);
			sem_unlink(buff);
		}
		free(data->philos);
	}
	printf("%s", s);
	return (1);
}
