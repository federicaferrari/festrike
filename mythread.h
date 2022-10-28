#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include "smpt_ll_client.h"
#include "smpt_client.h"
#include "smpt_ml_client.h"
#include "smpt_messages.h"
#include "smpt_packet_number_generator.h"
#include "smpt_ll_packet_validity.h"

class mythread:public QThread
{
    Q_OBJECT
public:
    explicit mythread(QObject *parent=0);
    void run();
    void stimulation();
    bool Stop=false;
    bool check_send;
    bool check_data;
    bool check_close;

    bool Close=false;
    int stimolatore;
    int corrente;
    int frequenza;
    int periodo;
    int canale;
    int pulsewidth;

signals:
   void NumberChanged(int);


public slots:
//void onCorrente(int);
};

#endif // MYTHREAD_H
