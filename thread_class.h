#ifndef THREAD_CLASS_H
#define THREAD_CLASS_H
#include "thread_app.h"
#include "globalvariables.h"
#include "header.h"
#define DEFAULT_LOOP_TIME_NS 1000000L

class thread_class
{
public:
    thread_class();
    void getinfo();
    thread_app app;
    void rt_thread();
    bool start_thread();
    void join_thread();

private:
    static void *internal_rt(void* This){((thread_class*)This)->rt_thread(); return nullptr;}
    pthread_t pthread_rt;

};

#endif // THREAD_CLASS_H
