/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:47:13 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/21 16:40:40 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating(t_p *p)
{
	pthread_mutex_lock(&p->num.forks[p->fork[LF]]);
	pthread_mutex_lock(&p->num.forks[p->fork[RF]]);
	if (p->life == TRUE)
	{
		pthread_mutex_lock(&p->num.print);
		printf("%lli %i %s\n", ms() - p->num.s_t, p->me, F);
		printf("%lli %i %s\n", ms() - p->num.s_t, p->me, F);
		printf("%lli %i %s\n", ms() - p->num.s_t, p->me, E);
		pthread_mutex_unlock(&p->num.print);
	}
	p->t_ate = ms() - p->num.s_t;
	p->n_ate++;
	sleep_diff(p->num.t_eat);
	pthread_mutex_unlock(&p->num.forks[p->fork[LF]]);
	pthread_mutex_unlock(&p->num.forks[p->fork[RF]]);
}

void	sleeping(t_p *p)
{
	if (p->life == TRUE)
	{
		pthread_mutex_lock(&p->num.print);
		printf("%lli %i %s\n", currentms(p), p->me, S);
		pthread_mutex_unlock(&p->num.print);
	}
	sleep_diff(p->num.t_sleep);
}

void	thinking(t_p *p)
{
	if (p->life == TRUE)
	{
		pthread_mutex_lock(&p->num.print);
		printf("%lli %i %s\n", currentms(p), p->me, T);
		pthread_mutex_unlock(&p->num.print);
	}
}
