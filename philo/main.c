/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:46:02 by ckarol            #+#    #+#             */
/*   Updated: 2022/07/02 20:46:04 by ckarol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (start_threads(&data))
		return (final_free(&data, "Error due tread starting\n"));
	pthread_mutex_lock(&data.dead_smb);
	pthread_mutex_unlock(&data.dead_smb);
	final_free(&data, "");
	return (0);
}
