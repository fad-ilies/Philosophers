#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_rules
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int nb_meal;                 /* -1 si pas précisé */
	long long start_time;        /* moment où la simulation commence */
	int stop;                    /* flag d'arrêt (0 = run, 1 = stop) */
	pthread_mutex_t print_mutex; /* pour sérialiser l'affichage */
	pthread_mutex_t stop_mutex;  /* protège "stop" */
}					t_rules;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
	t_rules *rules;             /* pointeur vers les règles globales */
	int ate;                    /* nombre de fois mangé */
	long long last_eat;         /* timestamp ms du dernier repas */
	pthread_mutex_t *left_fork; /* pointeurs vers les fourchettes (mutex) */
	pthread_mutex_t	*right_fork;
}					t_philo;

typedef struct s_data
{
	t_philo			*philos;
	t_rules			rules;
	pthread_mutex_t *forks; /* tableau de mutex (nb_philo elements) */
}					t_data;

/* parsing / init */
int					check_args(int ac);
int					pars_pos_int(char *str);
int					init_philosophers(t_data *data);
int					init_mutex(t_data *data);
int					init_rules(t_rules *rules, int ac, char **av);
int					start_simulation(t_data *data);

/* routines */
void				*routine(void *arg);
void				*monitor_routine(void *arg);

/* util */
long long			get_time(void);
void				print_action(t_philo *philo, char *str);
int					get_stop(t_rules *rules);
void				set_stop(t_rules *rules);
int					start_simulation(t_data *data);

#endif /* PHILO_H */
