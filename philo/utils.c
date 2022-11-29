#include "philosophers.h"

long long	ft_time(void)
{
	struct timeval	tv;
	long long		ret;

	gettimeofday(&tv, NULL);
	ret = 1000 * tv.tv_sec + tv.tv_usec / 1000;
	return (ret);
}

int	ft_atoi(const char *str)
{
	int	neg;
	int	result;
	int	i;

	neg = 1;
	result = 0;
	i = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
		|| (str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		result = 10 * result + (int)(str[i++] - '0');
	return (neg * result);
}

int	is_digit(char *str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

void	ft_usleep(int ms)
{
	long long		time;

	time = ft_time();
	usleep(ms * 920);
	while (ft_time() < time + ms)
		usleep(3 * ms);
}

int	ft_error(char *s)
{
	printf("%s\n", s);
	return (1);
}
