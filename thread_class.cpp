#include "thread_class.h"
#include <stdio.h>
#include <iostream>
using namespace std;
#include <chrono>
#include <sys/ioctl.h>
#include <stdint.h>
#include <time.h>

thread_class::thread_class()
{

    if(app.c.init()){

        cout << "User Interface shared memory initialized with key: " << hex << app.c.get_shared_memory_key();
    }

    else{

        cout << "User Interfce shared memory initialization has been failed ";
        app.c.detach_shared_memory();
    }
}


void thread_class::getinfo(){

    struct sched_param param;
    int policy ;
    sched_getparam(0, &param);

    printf("Priority if the thread: %d, current policy is: %d\n\r", param.sched_priority);
    pthread_getschedparam(pthread_self(), &policy, &param);
    printf("Priotiry of the thread: %d, current policy is: %d\n\r", param.sched_priority, policy);

}

void thread_class::rt_thread(){

    struct timespec t_start, t_now, t_next, t_period, t_result;
    cout << "RT Thread";
    getinfo();

    clock_gettime(CLOCK_MONOTONIC, &t_start);
    clock_gettime(CLOCK_MONOTONIC, &t_now);
    t_next=t_now;

    while(app.c.data->stop_thread_running==false){

        t_period.tv_sec=0;
        t_period.tv_nsec=DEFAULT_LOOP_TIME_NS;

        t_next = addition(t_next, t_period);

        //Debug cycle at 1kHz
        if(app.count%1==0){

            app.loop();

        }
        app.count++;
        clock_nanosleep ( CLOCK_MONOTONIC, TIMER_ABSTIME, &t_next, nullptr ); // waits until time t_next is reached
        // print t_now (just to check "running" cycle repeats with desired frequency)
        clock_gettime ( CLOCK_MONOTONIC, &t_now);
    }


    cout << "sono fuori dal loop";


}

bool thread_class::start_thread(){

    int policy;
    struct sched_param prio;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);


    policy = SCHED_RR;
    pthread_attr_setschedpolicy(&attr, policy);
    prio.sched_priority = 1;
    pthread_attr_setschedparam(&attr,&prio);

    if(pthread_create(&pthread_rt, &attr, internal_rt, this)){
        cout << "Error rt thread";
        return 1;
    }

    return 0;
}

void thread_class::join_thread(){

    (void)pthread_join(pthread_rt,NULL);
}







