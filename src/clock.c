#include"clock.h"

float diffUserTime(struct rusage *start, struct rusage *end){

    return (end->ru_utime.tv_sec - start->ru_utime.tv_sec) + 
        1e-6*(end->ru_utime.tv_usec - start->ru_utime.tv_usec);
}

float diffSystemTime(struct rusage *start, struct rusage *end){

    return (end->ru_stime.tv_sec - start->ru_stime.tv_sec) +
        1e-6*(end->ru_stime.tv_usec - start->ru_stime.tv_usec);
}


float time_diff(struct timeval *start, struct timeval *end){

  return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);

}

long memomyChack(){

  struct rusage memory;

  getrusage(RUSAGE_SELF,&memory);
  
  return (memory.ru_maxrss)*1024;
}