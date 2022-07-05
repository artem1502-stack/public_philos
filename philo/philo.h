/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 20:46:24 by ckarol            #+#    #+#             */
/*   Updated: 2022/07/02 20:46:26 by ckarol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include "messages.h"

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	int				pos;
	int				is_eating;
	uint64_t		limit;
	uint64_t		last_eat;
	int				lfork;
	int				rfork;
	int				eat_count;

	pthread_mutex_t	access;
	pthread_mutex_t	emech;
}					t_philo;

typedef struct s_data
{
	int				num_philos;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				max_eat_count;

	uint64_t		start;

	t_philo			*philos;
	pthread_mutex_t	*forks_k;
	pthread_mutex_t	write_k;
	pthread_mutex_t	dead_smb;
}					t_data;

//	utils.c
int			ft_atoi(const char *s);
uint64_t	get_time(void);
int			int_free(void *ptr);
void		print_mess(t_philo *philo, const char *s, int flg);
void		smart_sleep(uint64_t length);

//	parsing.c
int			parse_n_init(t_data *data, int argc, char *argv[]);

//	clean_up.c
int			final_free(t_data *data, const char *s);

//	start_treads.c
int			start_threads(t_data *data);

#endif
