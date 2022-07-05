/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:46:17 by ckarol            #+#    #+#             */
/*   Updated: 2022/07/02 20:46:19 by ckarol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_argv(char *argv[])
{
	int	i;

	while (*argv)
	{
		i = -1;
		while ((*argv)[++i])
			if (((*argv)[i] < '0') || ((*argv)[i] > '9'))
				return (1);
		argv++;
	}
	return (0);
}

static int	start_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->write_k, NULL);
	pthread_mutex_init(&data->dead_smb, NULL);
	pthread_mutex_lock(&data->dead_smb);
	data->forks_k = (pthread_mutex_t *)malloc(
			sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks_k)
		return (1);
	i = -1;
	while (++i < data->num_philos)
		pthread_mutex_init(&data->forks_k[i], NULL);
	return (0);
}

static void	pre_start_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		data->philos[i].is_eating = 0;
		data->philos[i].pos = i;
		data->philos[i].lfork = i;
		data->philos[i].rfork = (i + 1) % data->num_philos;
		data->philos[i].eat_count = 0;
		data->philos[i].data = data;
		pthread_mutex_init(&data->philos[i].access, NULL);
		pthread_mutex_init(&data->philos[i].emech, NULL);
		pthread_mutex_lock(&data->philos[i].emech);
	}
}

int	parse_n_init(t_data *data, int argc, char *argv[])
{
	if (check_argv(argv + 1))
		return (1);
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_eat_count = ft_atoi(argv[5]);
	else
		data->max_eat_count = 0;
	if (data->num_philos < 1 || data->num_philos > 200 || data->time_to_die < 60
		|| data->time_to_eat < 60 || data->time_to_sleep < 60
		|| data->max_eat_count < 0)
		return (1);
	if ((data->max_eat_count == 0) && argc == 6)
		return (-1);
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (1);
	pre_start_philos(data);
	if (start_mutexes(data))
		return (int_free(data->philos));
	return (0);
}
