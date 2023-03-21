/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:48:24 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/21 19:48:48 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	checker(t_v *v)
{
	int				i;
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
	if (v->philos[i].n_ate != v->num.n_eat)
		kill_threads(v, i);
}

void	kill_threads(t_v *v, int i)
{
	int	l;

	if (i == 0)
		l = 1;
	else
		l = i;
	printf("%lli %i %s\n", currentms(&v->philos[i]), l, D);
	i = -1;
	while (++i < v->num.n_philo)
		v->philos[i].life = FALSE;
	pthread_mutex_unlock(&v->num.print);
}
