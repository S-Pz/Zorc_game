#ifndef _CLOCK_
#define _CLOCK_

#include<sys/time.h>
#include<sys/resource.h>

float diffSystemTime(struct rusage *, struct rusage *);
float diffUserTime(struct rusage *, struct rusage *);

float time_diff(struct timeval *, struct timeval *);
long memomyChack();

#endif