/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:47:13 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/22 14:21:22 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_p *p)
{
	pthread_mutex_lock(&p->num.forks[p->forklf]);
	pthread_mutex_lock(&p->num.forks[p->forkrf]);
	if (p->life == TRUE)
	{
		pthread_mutex_lock(&p->num.print);
		printf("%lli %i %s\n", currentms(p), p->me, F);
		printf("%lli %i %s\n", currentms(p), p->me, F);
		printf("%lli %i %s\n", currentms(p), p->me, E);
		pthread_mutex_unlock(&p->num.print);
	}
	pthread_mutex_lock(&p->eattime);
	p->t_ate = currentms(p);
	sleep_diff(p->num.t_eat);
	p->n_ate++;
	pthread_mutex_unlock(&p->eattime);
	pthread_mutex_unlock(&p->num.forks[p->forkrf]);
	pthread_mutex_unlock(&p->num.forks[p->forklf]);
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
