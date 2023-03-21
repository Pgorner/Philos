/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:46:37 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/21 15:04:27 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo(t_v *v)
{
	int	i;

	v->philos = set_calloc(sizeof(t_p), v->num.n_philo + 1);
	i = -1;
	while (++i < v->num.n_philo)
		set_v(&v->philos[i], v, i);
	i = -1;
	if (v->num.n_eat > 0)
		while (++i < v->num.n_philo)
			pthread_create(&v->philos[i].philo, NULL,
				(void *)existence, (void *)&(v->philos[i]));
	else
		while (++i < v->num.n_philo)
			pthread_create(&v->philos[i].philo, NULL,
				(void *)infinity, (void *)&(v->philos[i]));
}

void	init_phork(t_v *v)
{
	int	i;

	i = 0;
	v->num.forks = malloc(sizeof(pthread_mutex_t) * v->num.n_philo + 1);
	while (i < v->num.n_philo)
		pthread_mutex_init(&v->num.forks[i++], NULL);
	pthread_mutex_init(&v->num.print, NULL);
	pthread_mutex_init(&v->num.eattime, NULL);
}
