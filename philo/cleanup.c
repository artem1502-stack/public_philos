/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:45:45 by ckarol            #+#    #+#             */
/*   Updated: 2022/07/02 20:45:47 by ckarol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	final_free(t_data *data, const char *s)
{
	int	i;

	if (data->forks_k)
	{
		i = -1;
		while (++i < data->num_philos)
			pthread_mutex_destroy(&data->forks_k[i]);
		free(data->forks_k);
	}
	if (data->philos)
	{
		i = -1;
		while (++i < data->num_philos)
		{
			pthread_mutex_destroy(&data->philos[i].access);
			pthread_mutex_destroy(&data->philos[i].emech);
		}
		free(data->philos);
		pthread_mutex_destroy(&data->write_k);
		pthread_mutex_destroy(&data->dead_smb);
	}
	printf("%s", s);
	return (1);
}
