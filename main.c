/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:47:27 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/20 17:58:49 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleep_diff(int time)
{
	long long int i;
	
	i = ms();
	while (ms() - i < time)
		usleep(50);
}

void	eating(t_p *p)
{
	pthread_mutex_lock(&p->num.forks[p->fork[LF]]);
	pthread_mutex_lock(&p->num.forks[p->fork[RF]]);
	if (p->life == TRUE)
	{
		pthread_mutex_lock(&p->num.print);
		printf("%lli %s %i %s\n", ms() - p->num.s_t, P, p->me, F);
		printf("%lli %s %i %s for %i\n", ms() - p->num.s_t, P, p->me, E, p->num.t_eat);
		pthread_mutex_unlock(&p->num.print);
	}
	p->t_ate = ms() - p->num.s_t;
	sleep_diff(p->num.t_eat);
	pthread_mutex_unlock(&p->num.forks[p->fork[LF]]);
	pthread_mutex_unlock(&p->num.forks[p->fork[RF]]);
	p->n_ate++;
}

void	sleeping(t_p *p)
{
	if (p->life == TRUE)
	{
		pthread_mutex_lock(&p->num.print);
		printf("%lli %s %i %s\n", ms() - p->num.s_t, P, p->me, S);
		pthread_mutex_unlock(&p->num.print);
	}
	sleep_diff(p->num.t_sleep);
}

void	thinking(t_p *p)
{
	if (p->life == TRUE)
	{
		pthread_mutex_lock(&p->num.print);
		printf("%lli %s %i %s\n", ms() - p->num.s_t, P, p->me, T);
		pthread_mutex_unlock(&p->num.print);
	}
}

void	existence(void *args)
{
	t_p *p;

	printf("existence\n");
	p = (t_p *)args;
	//printf("Im living ~ Philo %i\n", v->num);
	if (p->me % 2)
		usleep(1500);
	while (p->n_ate <= p->num.n_eat && p->life == TRUE)
	{
		eating(p);
		sleeping(p);
		thinking(p);
	}
}

void	infinity(void *args)
{
	t_p *p;
	p = (t_p *)args;
	if (p->me % 2)
		usleep(1500);
	while (TRUE && p->life == TRUE)
	{
		eating(p);
		sleeping(p);
		thinking(p);
	}
}

void	set_v(t_p *p, t_v *v, int i)
{
	p->t_ate = 0;
	p->me = i + 1;
	p->philo = NULL;
	p->num = v->num;
	p->fork[0] = i;
	p->life = TRUE;
	if (i < v->num.n_philo - 1)
		p->fork[1] = i + 1;
	if (i == v->num.n_philo - 1)
		p->fork[1] = 0;
	printf("%s %i alive\n", P, p->me);
}

void	init_philo(t_v *v)
{
	int	i;

	v->philos = malloc(sizeof(t_p) * v->num.n_philo);
	i = -1;
	while (++i < v->num.n_philo)
		set_v(&v->philos[i], v, i);
	i = 0;
	if (v->num.n_eat > 0)
		while (i < v->num.n_philo)
		{
			//printf("EXISTENCE\n");
			pthread_create(&v->philos[i].philo, NULL, (void *)existence, (void *)&(v->philos[i]));
			usleep(10);
			i++;
		}
	else
		while (i < v->num.n_philo)
		{
			//printf("INFINITY\n");
			pthread_create(&v->philos[i].philo, NULL, (void *)infinity, (void *)&(v->philos[i]));
			usleep(10);
			i++;
		}
}

void	init_phork(t_v *v)
{
	int i;
	v->num.forks = malloc(sizeof(pthread_mutex_t) * v->num.n_philo + 1);
	
	i = 0;
	while (i < v->num.n_philo)
		pthread_mutex_init(&v->num.forks[i++], NULL);
	pthread_mutex_init(&v->num.print, NULL);
}

void	join_philo(t_v *v)
{
	int i; 
	
	i = -1;
	while (++i < v->num.n_philo)
	{
		pthread_join(v->philos[i].philo, NULL);
	}
	pthread_join(v->checker, NULL);
}

void	checker(t_v *v)
{
	int i;
	
	i = 0;
	while (TRUE)
	{
		i++;
		if (((ms() - v->num.s_t) - v->philos[i].t_ate) > v->num.t_death)
			break;
		if (i == v->num.n_philo)
			i = 0;
	}
	printf("---------------------PHILO%i has died\n", i);
	i = -1;
	while (++i < v->num.n_philo)
		v->philos[i].life = FALSE;
	i = -1;
	while (++i < v->num.n_philo)
	{
		pthread_mutex_unlock(&v->num.forks[i]);
		printf("FORKKILL:%i:%i:\n", i + 1, pthread_mutex_destroy(&v->num.forks[i]));
	}
	i = -1;
	while (++i < v->num.n_philo)
		printf("PHILOKILL:%i:%i:\n", i + 1, pthread_detach(v->philos[i].philo));
	pthread_detach(v->checker);
/* 	exit(1); */
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
	join_philo(&v);
	//printf("%i Philosophers have been created at\n%lld\nat time\n%ld\n", v.n_philo, v.s_t, ms());
	return(0);
}


// if onbe thread exits or returns over main everything is terminated