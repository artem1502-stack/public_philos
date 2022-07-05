/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckarol <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 12:31:55 by ckarol            #+#    #+#             */
/*   Updated: 2022/07/04 12:31:56 by ckarol           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(const char *s)
{
	int	ans;
	int	neg;

	neg = 1;
	ans = 0;
	while (*s && (*s == ' ' || *s == '\n' || *s == '\t'
			|| *s == '\v' || *s == '\f' || *s == '\r'))
		++s;
	if (*s == '-')
		neg = -1;
	if (*s == '-' || *s == '+')
		++s;
	while (*s && *s >= '0' && *s <= '9')
	{
		ans = ans * 10 + (*s - 48);
		++s;
	}
	return (ans * neg);
}

uint64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

int	int_free(void *ptr)
{
	if (ptr)
		free(ptr);
	return (1);
}

void	print_mess(t_philo *philo, const char *s, int flg)
{
	sem_wait(philo->data->write_k);
	sem_wait(philo->data->dead_w);
	printf("%lld\t", get_time() - philo->data->start);
	if (flg < 2)
		printf("%d", philo->pos + 1);
	printf("\t%s\n", s);
	if (!flg)
		sem_post(philo->data->dead_w);
	sem_post(philo->data->write_k);
}

void	smart_sleep(uint64_t time)
{
	uint64_t	cur;
	uint64_t	end;

	cur = get_time();
	end = cur + time / 1000;
	while (cur < end)
	{
		usleep(100);
		cur = get_time();
	}
}
