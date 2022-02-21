# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

void	*func(void *ptr)
{
	(void)(ptr);
	sleep(5);
	if (*(int *)ptr == 1)
		exit(1);
	return (NULL);
}

int		main(void)
{
	pthread_t	*t;
	int			p;
	int			w;
	int			x;

	p = fork();
	x = 0;
	if (p == 0)
	{
		pthread_create(t, NULL, func, &x);
		while (1)
			x = 1;
		pthread_join(*t, NULL);
		exit(0);
	}
	else
		waitpid(p, &w, 0);
	printf("%d\n", w);
	return (0);
}

/*
process philo | thread

				thread
time_to_eat		time_to_die
time_to_sleep	time_start
eat_count		*last_meal

eat_ammount		return (-1);...
last_meal

join...exit

*/
