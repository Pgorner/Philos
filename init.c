/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:46:37 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/05 16:40:25 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_v *v, t_n *num)
{
	int	i;

	v->philos = malloc(sizeof(t_p) * v->num->n_philo + 1);
	i = -1;
	while (++i < num->n_philo)
		set_v(&v->philos[i], num, i);
	i = -1;
	if (v->num->n_eat > 0)
		while (++i < v->num->n_philo)
			pthread_create(&v->philos[i].philo, NULL,
				(void *)existence, (void *)&(v->philos[i]));
	else
		while (++i < v->num->n_philo)
			pthread_create(&v->philos[i].philo, NULL,
				(void *)infinity, (void *)&(v->philos[i]));
}
