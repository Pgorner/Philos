/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:48:24 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/21 16:56:39 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	checker(t_v *v)
{
	int			i;
	long long int	eattime;

	i = 0;
	while (TRUE)
	{
		eattime = (currentms(&v->philos[i]) - v->philos[i].t_ate);
		if (eattime > v->num.t_death)
			break ;
		if (v->num.n_philo != 1)
			i++;
		if (i == v->num.n_philo)
			i = 0;
	}
	pthread_mutex_lock(&v->num.print);
	usleep(3000);
	if (i == 0)
		i = 1;
	kill_threads(v, i);
}

void	kill_threads(t_v *v, int i)
{
	long long int ct = currentms(&v->philos[i]);
	printf("%lli %i %s\n", ct, i, D);
	i = -1;
	while (++i < v->num.n_philo)
		v->philos[i].life = FALSE;
	i = -1;
	while (++i < v->num.n_philo)
		pthread_mutex_destroy(&v->num.forks[i]);
	i = -1;
	while (++i < v->num.n_philo)
		pthread_detach(v->philos[i].philo);
	pthread_mutex_destroy(&v->num.print);
	pthread_mutex_destroy(&v->num.eattime);
	pthread_mutex_destroy(&v->num.start);
}
