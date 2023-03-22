/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:50:07 by pgorner           #+#    #+#             */
/*   Updated: 2023/03/22 12:05:09 by pgorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define SEC_PER_DAY 86400
# define SEC_PER_HOUR 3600
# define SEC_PER_MIN 60
# define TRUE 1
# define FALSE 0
# define RF 0
# define LF 1
# define E "is eating"
# define S "is sleeping"
# define T "is thinking"
# define F "has taken a fork"
# define D "died"

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <stdarg.h>
# include <stdint.h>

typedef struct s_num
{
	int				n_philo;
	int				t_death;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	long long int	s_t;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	pthread_mutex_t	start;
	pthread_mutex_t	sleep;
}	t_n;

typedef struct s_phil
{
	t_n				num;
	int				me;
	long long int	t_ate;
	int				n_ate;
	int				forklf;
	int				forkrf;
	int				life;
	pthread_mutex_t	eattime;
	pthread_t		philo;
}	t_p;

typedef struct s_val
{
	t_n				num;
	t_p				*philos;
	pthread_t		checker;
}	t_v;

//==============================================================================
//---------------------------------ACTION.c-------------------------------------
//==============================================================================
void			eating(t_p *p);
void			sleeping(t_p *p);
void			thinking(t_p *p);
//==============================================================================
//---------------------------------CHECKER.c------------------------------------
//==============================================================================
void			checker(t_v *v);
void			kill_threads(t_v *v, int i);
//==============================================================================
//----------------------------------INIT.c--------------------------------------
//==============================================================================
void			init_philo(t_v *v);
void			init_phork(t_v *v);
//==============================================================================
//----------------------------------INPUT.c-------------------------------------
//==============================================================================
void			ft_exit(char *c, int exc);
int				check_args(char *str);
void			set_v(t_p *p, t_v *v, int i);
void			values(int argc, char **argv, t_v *v);
//==============================================================================
//----------------------------------MAIN.c--------------------------------------
//==============================================================================
int				main(int argc, char **argv);
void			existence(void *args);
void			infinity(void *args);
void			join_philo(t_v *v);
//==============================================================================
//----------------------------------TIME.c--------------------------------------
//==============================================================================
long			ms(void);
long long int	currentms(t_p *p);
//==============================================================================
//---------------------------------UTILS.c--------------------------------------
//==============================================================================
void			*set_calloc(size_t count, size_t size);
void			values(int argc, char **argv, t_v *v);
void			ft_exit(char *c, int exc);
void			pzero(void *s, size_t n);
int				check_args(char *str);
void			sleep_diff(int time);

#endif