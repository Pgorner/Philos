/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:50:07 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/20 17:50:39 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <stdarg.h>

#define SEC_PER_DAY		86400
#define SEC_PER_HOUR	3600
#define SEC_PER_MIN		60
#define TRUE 1
#define FALSE 0
#define RF 0
#define LF 1
#define P "PHILO"
#define E "IS EATING"
#define S "IS SLEEPING"
#define T "IS THINKING"
#define F "HAS TAKEN PHORKS"
#define D "IS DED"

typedef struct num
{
	long long int	s_t;
	int				t_eat;
	int				n_eat;
	int				num;
	int				n_philo;
	int				t_death;
	int				t_sleep;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
} t_n;

typedef struct phil
{
	t_n				num;
	int				me;
	int				t_ate;
	int				n_ate;
	int				fork[2];
	int				life;
	pthread_t		philo;
}	t_p;

typedef struct val
{
	t_n				num;
	t_p				*philos;
	pthread_t		checker;
}	t_v;


//==============================================================================
//----------------------------------MAIN.c--------------------------------------
//==============================================================================


//==============================================================================
//----------------------------------TIME.c--------------------------------------
//==============================================================================
void		calctime(void);
long		ms();
//==============================================================================
//-------------------------------UTILS_MAIN.c-----------------------------------
//==============================================================================
void		values(int argc, char **argv, t_v *v);
int			check_args(char *str);
void		ft_exit(char *c, int exc);
//==============================================================================
//-------------------------------CONVERSION.c-----------------------------------
//==============================================================================
long		atol(const char *str);
void		existence(void *args);

#endif