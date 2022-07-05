/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 12:31:37 by ckarol            #+#    #+#             */
/*   Updated: 2022/07/04 12:31:38 by ckarol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include "messages_bonus.h"

# define PHILO_STD_NAME "pSTDphilo"
# define PHILO_STD_EAT "pSTDeat"
# define PHILO_INF_FORK "pINFforr"
# define PHILO_INF_WRITE "pINFwrite"
# define PHILO_INF_DEADS "pINFsmbdead"
# define PHILO_INF_DEADW "pINFwdead"

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	int				pos;
	int				is_eating;
	uint64_t		limit;
	uint64_t		last_eat;
	int				eat_count;

	sem_t			*access;
	sem_t			*emech;

	pid_t			pid;
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

	sem_t			*forks_k;
	sem_t			*write_k;
	sem_t			*dead_smb;
	sem_t			*dead_w;
}					t_data;

//	utils_bonus.c
int			ft_atoi(const char *s);
uint64_t	get_time(void);
int			int_free(void *ptr);
void		print_mess(t_philo *philo, const char *s, int flg);
void		smart_sleep(uint64_t length);

//	parsing_bonus.c
int			parse_n_init(t_data *data, int argc, char *argv[]);

//	clean_up_bonus.c
int			final_free(t_data *data, const char *s);

//	start_process_bonus.c
int			start_process(t_data *data);

//	sems_bonus.c
sem_t		*my_ssopen(const char *s, int st_value);
char		*name_constructor(int pos, char *dst, const char *src);

//	main_bonus.c
void		*counter_tread(void *ptr);
int			start_counting(t_data *data);

#endif
