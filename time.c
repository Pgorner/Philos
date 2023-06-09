/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:25:38 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/05 16:55:26 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ms(void)
{
	long			ms;
	struct timeval	tv;
	struct timezone	tz;

	gettimeofday(&tv, &tz);
	ms = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return (ms);
}

long long int	currentms(t_p *p)
{
	long long int	ret;

	if (p->num->s_t == 0)
		p->num->s_t = ms();
	ret = ms() - p->num->s_t;
	return (ret);
}
