/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:25:38 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/08 14:53:26 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	calctime(void)
{
	long	hms;
	int		h;
	int		m;
	int		s;
	struct timeval tv;
	struct timezone tz;

	if (gettimeofday(&tv, &tz) < 0)
		ft_exit("Getting time failed", 66);
	hms = tv.tv_sec % SEC_PER_DAY;
	hms += tz.tz_dsttime * SEC_PER_HOUR;
	hms -= tz.tz_minuteswest * SEC_PER_MIN;
	hms = (hms + SEC_PER_DAY) % SEC_PER_DAY;
	h = hms / SEC_PER_HOUR;
	m = (hms % SEC_PER_HOUR) / SEC_PER_MIN;
	s = (hms % SEC_PER_HOUR) % SEC_PER_MIN;
	printf(":%02d:%02d:%02d:%d\n", h, m, s, tv.tv_usec);
}

long	ms()
{
	long	ms;
	struct timeval tv;
	struct timezone tz;

	if (gettimeofday(&tv, &tz) < 0)
		ft_exit("Getting time failed", 66);
	ms = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return(ms);
}