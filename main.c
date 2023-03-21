/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:47:27 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/21 15:10:26 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	existence(void *args)
{
	t_p	*p;

	p = (t_p *)args;
	if (p->me % 2)
		usleep(1500);
	while (p->n_ate <= p->num.n_eat)
	{
		if (p->life == TRUE)
			eating(p);
		if (p->life == TRUE)
			sleeping(p);
		if (p->life == TRUE)
			thinking(p);
	}
}

void	infinity(void *args)
{
	t_p	*p;

	p = (t_p *)args;
	if (p->me % 2)
		usleep(1500);
	while (TRUE && p->life == TRUE)
	{
		if (p->life == TRUE)
			eating(p);
		if (p->life == TRUE)
			sleeping(p);
		if (p->life == TRUE)
			thinking(p);
	}
}

int	main(int argc, char **argv)
{
	t_v	v;

	if (argc == 5 || argc == 6)
		values(argc, argv, &v);
	else
		ft_exit("Too few/many input", 127);
	init_phork(&v);
	init_philo(&v);
	pthread_create(&v.checker, NULL, (void *)checker, (void *)&v);
	pthread_join(v.checker, NULL);
	return (0);
}
