/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:48:24 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/22 14:28:28 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	checker(t_v *v)
{
	int	i;

	i = 0;
	while (TRUE)
	{
		pthread_mutex_lock(&v->philos[i].eattime);
		if (currentms(&v->philos[i]) - v->philos[i].t_ate > v->num.t_death
			|| v->philos[i].n_ate == v->num.n_eat)
			break ;
		pthread_mutex_unlock(&v->philos[i].eattime);
		if (v->num.n_philo != 1)
			i++;
		if (i == v->num.n_philo)
			i = 0;
	}
	pthread_mutex_lock(&v->num.print);
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
	i = -1;
	while (++i < v->num.n_philo)
		v->philos[i].life = FALSE;
	printf("%lli %i %s\n", currentms(&v->philos[i]), l, D);
}
