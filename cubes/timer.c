#include "timer.h"
#include <sys/time.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int utime() {
  struct timeval time;
  gettimeofday(&time, NULL);
  unsigned int s1 = (time.tv_sec) * 1000;
  unsigned int s2 = (time.tv_usec / 1000);
  return s1 + s2;
}

int timer(Timer* timer) {

    if(timer == NULL) {
        perror("error: at timer() variable timer is null pointer");
        exit(1);
    }

    if(utime() > timer->time) {
        timer->time = utime() + timer->cycle;
        return 1;
    }
    return 0;
}
