/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:48:24 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/05 15:23:33 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	checker(t_v *v)
{
	int	i;

	i = 0;
	while (TRUE)
	{
		if (self_aware(&v->philos[i]) == 0)
			break ;
		if (v->num.n_philo != 1)
			i++;
		if (i == v->num.n_philo)
			i = 0;
	}
	pthread_mutex_lock(&v->num.print);
	pthread_mutex_lock(&v->philos[i].eattime);
	usleep(3000);
	if (v->philos[i].n_ate != v->num.n_eat)
	{
		pthread_mutex_unlock(&v->philos[i].eattime);
		kill_threads(v, i);
	}
	else
		pthread_mutex_unlock(&v->philos[i].eattime);
	pthread_mutex_unlock(&v->num.print);
}

void	kill_threads(t_v *v, int i)
{
	int	l;

	if (i == 0)
		l = 1;
	else
		l = i;
	printf("%lli %i %s\n", currentms(&v->philos[i]), l, D);
}
/* 
		pthread_mutex_lock(&v->philos[i].eattime);
		if (currentms(&v->philos[i]) - v->philos[i].t_ate > v->num.t_death)
			break ;
		pthread_mutex_unlock(&v->philos[i].eattime); */