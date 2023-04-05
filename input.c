/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:28:00 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/05 17:02:20 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit(char *c, int exc)
{
	printf("%s\n", c);
	exit(exc);
}

int	check_args(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	while (str[j] >= '0' && str[j] <= '9')
		j++;
	if (i != j)
		return (FALSE);
	if (atol(str) <= 0)
		return (FALSE);
	return (TRUE);
}

void	set_v(t_p *p, t_n *num, int i)
{
	p->me = i + 1;
	p->forkrf = i;
	p->life = TRUE;
	p->num = num;
	p->death = num->t_death;
	if (i < num->n_philo - 1)
		p->forklf = i + 1;
	if (i == num->n_philo - 1)
		p->forklf = 0;
	p->t_ate = currentms(p);
}

void	values(int argc, char **argv, t_n *num)
{
	int	i;

	i = 0;
	while (++i < argc)
		if (check_args(argv[i]) == FALSE)
			ft_exit("False input at args", 2);
	num->n_philo = atol(argv[1]);
	num->forks = set_calloc(sizeof(pthread_mutex_t), num->n_philo);
	num->t_death = atol(argv[2]);
	num->t_eat = atol(argv[3]);
	num->t_sleep = atol(argv[4]);
	if (argc == 6)
		num->n_eat = atol(argv[5]);
	else
		num->n_eat = -1;
	i = 0;
	while (i < num->n_philo)
		pthread_mutex_init(&num->forks[i++], NULL);
	pthread_mutex_init(&num->print, NULL);
	pthread_mutex_init(&num->sleep, NULL);
	pthread_mutex_init(&num->eattime, NULL);
	num->s_t = ms();
	num->life = TRUE;
}
