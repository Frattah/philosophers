#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

long long       get_time(struct timeval init)
{
        struct timeval  timeval;

        gettimeofday(&timeval, NULL);
        return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000) - init.tv_sec * 1000 - init.tv_usec / 1000);
}

int main() 
{
	struct timeval timeval;

	gettimeofday(&timeval, NULL);
	usleep(4000);
	printf("%lld\n", get_time(timeval));
}
