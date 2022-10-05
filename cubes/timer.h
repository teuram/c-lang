
#ifndef TIMER_H
#define TIMER_H
 
struct timer {
    unsigned int cycle;
    unsigned int time;
} typedef Timer;

int timer(Timer* timer);

#endif

