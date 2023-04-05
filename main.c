/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:47:27 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/05 15:23:49 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	self_aware(t_p *p)
{
	pthread_mutex_lock(&p->eattime);
	if ((currentms(p) - p->t_ate) > p->death || p->num.life == FALSE)
	{
		p->num.life = FALSE;
		pthread_mutex_unlock(&p->eattime);
		return (FALSE);
	}
	else
		pthread_mutex_unlock(&p->eattime);
	return (TRUE);
}

void	existence(void *args)
{
	t_p	*p;

	p = (t_p *)args;
	if (p->me % 2)
		usleep(1500);
	while (p->n_ate < p->num.n_eat)
	{
		if (self_aware(p))
			eating(p);
		if (self_aware(p))
			sleeping(p);
		if (self_aware(p))
			thinking(p);
	}
	usleep(300);
	pthread_mutex_destroy(&p->num.forks[p->me]);
}

void	infinity(void *args)
{
	t_p	*p;

	p = (t_p *)args;
	if (p->me % 2)
		usleep(1500);
	while (self_aware(p))
	{
		if (self_aware(p))
			eating(p);
		if (self_aware(p))
			sleeping(p);
		if (self_aware(p))
			thinking(p);
	}
}

void	end(t_v *v)
{
	int	i;

	pthread_mutex_destroy(&v->num.start);
	pthread_mutex_destroy(&v->num.sleep);
	pthread_mutex_destroy(&v->num.print);
	i = 0;
	while (i < v->num.n_philo)
		pthread_detach(v->philos[i++].philo);
	free(v->philos);
	free(v->num.forks);
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
	end(&v);
	return (0);
}
