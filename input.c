/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:28:00 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/05 15:23:44 by pgorner          ###   ########.fr       */
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

void	set_v(t_p *p, t_v *v, int i)
{
	p->t_ate = currentms(p);
	p->me = i + 1;
	p->num = v->num;
	p->forkrf = i;
	p->life = TRUE;
	p->death = v->num.t_death;
	pthread_mutex_init(&p->eattime, NULL);
	if (i < v->num.n_philo - 1)
		p->forklf = i + 1;
	if (i == v->num.n_philo - 1)
		p->forklf = 0;
}

void	values(int argc, char **argv, t_v *v)
{
	int	i;

	i = 0;
	while (++i < argc)
		if (check_args(argv[i]) == FALSE)
			ft_exit("False input at args", 2);
	v->num.n_philo = atol(argv[1]);
	v->num.t_death = atol(argv[2]);
	v->num.t_eat = atol(argv[3]);
	v->num.t_sleep = atol(argv[4]);
	if (argc == 6)
		v->num.n_eat = atol(argv[5]);
	else
		v->num.n_eat = -1;
	v->num.s_t = ms();
	v->num.life = TRUE;
}
