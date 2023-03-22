/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:47:27 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/22 14:26:51 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	existence(void *args)
{
	int	ate;
	int	eat;
	int	life;
	t_p	*p;

	p = (t_p *)args;
	eat = p->num.n_eat;
	ate = 0;
	life = TRUE;
	if (p->me % 2)
		usleep(1500);
	while (ate < eat && life == TRUE)
	{
		if (p->life == TRUE)
			eating(p);
		if (p->life == TRUE)
			sleeping(p);
		if (p->life == TRUE)
			thinking(p);
		pthread_mutex_lock(&p->eattime);
		if (currentms(p) - p->t_ate > p->num.t_death)
		life = FALSE;
		pthread_mutex_unlock(&p->eattime);
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

void	end(t_v *v)
{
	int	i;

	i = 0;
	while (i < v->num.n_philo)
	{
		pthread_mutex_destroy(&v->num.forks[i]);
		pthread_detach(v->philos[i++].philo);
	}
	pthread_mutex_destroy(&v->num.start);
	pthread_mutex_destroy(&v->num.sleep);
	pthread_mutex_destroy(&v->num.print);
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
