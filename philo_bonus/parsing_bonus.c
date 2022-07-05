/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 12:31:30 by ckarol            #+#    #+#             */
/*   Updated: 2022/07/04 12:31:31 by ckarol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_argv(char *argv[])
{
	int	i;

	while (*argv)
	{
		i = -1;
		if ((*argv)[0] == '+')
			i++;
		while ((*argv)[++i])
			if (((*argv)[i] < '0') || ((*argv)[i] > '9'))
				return (1);
		argv++;
	}
	return (0);
}

static int	start_sems(t_data *data)
{
	sem_unlink(PHILO_INF_FORK);
	sem_unlink(PHILO_INF_WRITE);
	sem_unlink(PHILO_INF_DEADS);
	sem_unlink(PHILO_INF_DEADW);
	data->forks_k = my_ssopen(PHILO_INF_FORK, data->num_philos);
	data->write_k = my_ssopen(PHILO_INF_WRITE, 1);
	data->dead_smb = my_ssopen(PHILO_INF_DEADS, 0);
	data->dead_w = my_ssopen(PHILO_INF_DEADW, 1);
	if (data->forks_k < 0 || data->write_k < 0 || data->dead_smb < 0
		|| data->dead_w < 0)
		return (1);
	return (0);
}

static int	pre_start_philos(t_data *data)
{
	int		i;
	char	buff[300];

	i = -1;
	while (++i < data->num_philos)
	{
		data->philos[i].is_eating = 0;
		data->philos[i].pos = i;
		data->philos[i].eat_count = 0;
		data->philos[i].data = data;
		name_constructor(i, (char *)buff, PHILO_STD_NAME);
		sem_unlink(buff);
		data->philos[i].access = my_ssopen(buff, 1);
		if (data->philos[i].access < 0)
			return (1);
		name_constructor(i, (char *)buff, PHILO_STD_EAT);
		sem_unlink(buff);
		data->philos[i].emech = my_ssopen(buff, 0);
		if (data->philos[i].emech < 0)
			return (1);
	}
	return (0);
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
	if (pre_start_philos(data) || start_sems(data))
		return (1);
	return (0);
}
