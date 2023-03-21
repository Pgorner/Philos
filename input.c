/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:28:00 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/21 16:37:02 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	p->t_ate = 0;
	p->me = i + 1;
	/* p->philo = NULL; */
	p->num = v->num;
	p->fork[0] = i;
	p->life = TRUE;
	if (i < v->num.n_philo - 1)
		p->fork[1] = i + 1;
	if (i == v->num.n_philo - 1)
		p->fork[1] = 0;
}

void	values(int argc, char **argv, t_v *v)
{
	int	i;

	i = 0;
	while (++i < argc)
		if (check_args(argv[i]) == FALSE)
			ft_exit("False Input at Arg\n", 2);
	v->num.n_philo = atol(argv[1]);
	v->num.t_death = atol(argv[2]);
	v->num.t_eat = atol(argv[3]);
	v->num.t_sleep = atol(argv[4]);
	if (argc == 6)
		v->num.n_eat = atol(argv[5]);
	else
		v->num.n_eat = -1;
	v->num.s_t = ms();
}
