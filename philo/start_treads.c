/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_treads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:46:31 by ckarol            #+#    #+#             */
/*   Updated: 2022/07/02 20:46:32 by ckarol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*counter_tread(void *ptr)
{
	t_data	*data;
	int		i;
	int		total;

	data = (t_data *)ptr;
	total = -1;
	while (++total < data->max_eat_count)
	{
		i = -1;
		while (++i < data->num_philos)
			pthread_mutex_lock(&data->philos[i].emech);
	}
	print_mess(&data->philos[0], "eat count reached", 2);
	pthread_mutex_unlock(&data->dead_smb);
	return ((void *)0);
}

static void	*tread_checker(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		pthread_mutex_lock(&philo->access);
		if (!philo->is_eating && get_time() - 1 > philo->limit)
		{
			print_mess(philo, DEAD_MESS, 1);
			pthread_mutex_unlock(&philo->access);
			pthread_mutex_unlock(&philo->data->dead_smb);
			return ((void *)0);
		}
		pthread_mutex_unlock(&philo->access);
		usleep(1000);
	}
	return ((void *)0);
}

static void	philo_body_mech(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks_k[philo->lfork]);
	print_mess(philo, FORK_MESS, 0);
	pthread_mutex_lock(&philo->data->forks_k[philo->rfork]);
	print_mess(philo, FORK_MESS, 0);
	pthread_mutex_lock(&philo->access);
	philo->is_eating = 1;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->data->time_to_die;
	print_mess(philo, EAT_MESS, 0);
	smart_sleep(philo->data->time_to_eat * 1000);
	philo->eat_count++;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->access);
	pthread_mutex_unlock(&philo->emech);
	print_mess(philo, SLEEP_MESS, 0);
	pthread_mutex_unlock(&philo->data->forks_k[philo->lfork]);
	pthread_mutex_unlock(&philo->data->forks_k[philo->rfork]);
	smart_sleep(philo->data->time_to_sleep * 1000);
	print_mess(philo, THINK_MESS, 0);
}

static void	*philo_tread(void *ptr)
{
	t_philo		*philo;
	pthread_t	tt;

	philo = (t_philo *)ptr;
	if (philo->pos % 2)
		usleep(1000);
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->data->time_to_die;
	if (pthread_create(&tt, NULL, &tread_checker, ptr) != 0)
		return ((void *)1);
	pthread_detach(tt);
	while (1)
		philo_body_mech(philo);
	return ((void *)0);
}

int	start_threads(t_data *data)
{
	int			i;
	pthread_t	tt;
	void		*philo;

	data->start = get_time();
	if (data->max_eat_count > 0)
	{
		if (pthread_create(&tt, NULL, &counter_tread, (void *)data) != 0)
			return (1);
		pthread_detach(tt);
	}
	i = -1;
	while (++i < data->num_philos)
	{
		philo = (void *)(&data->philos[i]);
		if (pthread_create(&tt, NULL, &philo_tread, philo) != 0)
			return (1);
		pthread_detach(tt);
		usleep(100);
	}
	return (0);
}
