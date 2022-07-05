/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 12:31:08 by ckarol            #+#    #+#             */
/*   Updated: 2022/07/04 12:31:09 by ckarol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*counter_tread(void *ptr)
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
			sem_wait(data->philos[i].emech);
	}
	print_mess(&data->philos[0], "eat count reached", 2);
	sem_post(data->dead_smb);
	return ((void *)0);
}

int	start_counting(t_data *data)
{
	pthread_t	tt;

	if (data->max_eat_count)
	{
		if (pthread_create(&tt, NULL, &counter_tread, (void *)data))
			return (1);
		pthread_detach(tt);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	int		res;

	if (argc < 5 || argc > 6)
		return (1);
	data.philos = NULL;
	data.forks_k = NULL;
	res = parse_n_init(&data, argc, argv);
	if (res == -1)
		return (final_free(&data, "No need to eat\n"));
	if (res)
		return (final_free(&data, "Error due parsing\n"));
	if (start_counting(&data))
		return (final_free(&data, "Error due counting start\n"));
	if (start_process(&data))
		return (final_free(&data, "Error due process starting\n"));
	sem_wait(data.dead_smb);
	res = -1;
	while (++res < data.num_philos)
		kill(data.philos[res].pid, SIGKILL);
	final_free(&data, "");
	return (0);
}
