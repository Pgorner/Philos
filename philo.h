/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgorner <pgorner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:50:07 by pgorner           #+#    #+#             */
/*   Updated: 2023/04/05 17:08:57 by pgorner          ###   ########.fr       */
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
	int				life;
	long long int	s_t;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	pthread_mutex_t	sleep;
	pthread_mutex_t	eattime;
}	t_n;

typedef struct s_phil
{
	t_n				*num;
	int				me;
	long long int	t_ate;
	int				n_ate;
	int				forklf;
	int				forkrf;
	int				life;
	int				death;
	pthread_t		philo;
}	t_p;

typedef struct s_val
{
	t_n				*num;
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
void			init_philo(t_v *v, t_n *num);
void			init_phork(t_v *v);
//==============================================================================
//----------------------------------INPUT.c-------------------------------------
//==============================================================================
int				check_args(char *str);
void			set_v(t_p *p, t_n *num, int i);
int				values(int argc, char **argv, t_n *num);
//==============================================================================
//----------------------------------MAIN.c--------------------------------------
//==============================================================================
int				main(int argc, char **argv);
void			existence(void *args);
void			infinity(void *args);
void			join_philo(t_v *v);
int				self_aware(t_p *p);
//==============================================================================
//----------------------------------TIME.c--------------------------------------
//==============================================================================
long			ms(void);
long long int	currentms(t_p *p);
//==============================================================================
//---------------------------------UTILS.c--------------------------------------
//==============================================================================
void			*set_calloc(size_t count, size_t size);
void			ft_exit(char *c);
void			pzero(void *s, size_t n);
int				check_args(char *str);
void			sleep_diff(t_p *p, int time);
#endif