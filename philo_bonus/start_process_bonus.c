/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 12:31:48 by ckarol            #+#    #+#             */
/*   Updated: 2022/07/04 12:31:49 by ckarol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*tread_checker(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo *)ptr;
	while (1)
	{
		sem_wait(philo->access);
		if (!philo->is_eating && get_time() - 1 > philo->limit)
		{
			print_mess(philo, DEAD_MESS, 1);
			sem_post(philo->access);
			sem_post(philo->data->dead_smb);
			return ((void *)0);
		}
		sem_post(philo->access);
		usleep(1000);
	}
	return ((void *)0);
}

static void	philo_body_mech(t_philo *philo)
{
	sem_wait(philo->data->forks_k);
	print_mess(philo, FORK_MESS, 0);
	sem_wait(philo->data->forks_k);
	print_mess(philo, FORK_MESS, 0);
	sem_wait(philo->access);
	philo->is_eating = 1;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->data->time_to_die;
	print_mess(philo, EAT_MESS, 0);
	smart_sleep(philo->data->time_to_eat * 1000);
	philo->eat_count++;
	philo->is_eating = 0;
	sem_post(philo->access);
	sem_post(philo->emech);
	print_mess(philo, SLEEP_MESS, 0);
	sem_post(philo->data->forks_k);
	sem_post(philo->data->forks_k);
	smart_sleep(philo->data->time_to_sleep * 1000);
	print_mess(philo, THINK_MESS, 0);
}

static int	philo_tread(void *ptr)
{
	t_philo		*philo;
	pthread_t	tt;

	philo = (t_philo *)ptr;
	if (philo->pos % 2)
		usleep(1000);
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->data->time_to_die;
	if (pthread_create(&tt, NULL, &tread_checker, ptr) != 0)
		return (1);
	pthread_detach(tt);
	while (1)
		philo_body_mech(philo);
	return (0);
}

int	start_process(t_data *data)
{
	int			i;
	void		*philo;

	data->start = get_time();
	i = -1;
	while (++i < data->num_philos)
	{
		philo = (void *)(&data->philos[i]);
		data->philos[i].pid = fork();
		if (data->philos[i].pid < 0)
			return (1);
		if (data->philos[i].pid == 0)
		{
			philo_tread((void *)&data->philos[i]);
			exit(0);
		}
		usleep(100);
	}
	return (0);
}
