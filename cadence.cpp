#include "cadence.h"
#include "ui_cadence.h"
#include "input.h"
#include "shared_memory.h"
#include "temp2.h"


#define DEFAULT_LOOP_TIME_NS 1000000L
#define DEFAULT_BUTTON_PRESSED_PAUSE_S 1
#define DEFAULT_BUTTON_PRESSED_PAUSE_NS 0

Cadence::Cadence(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Cadence)
{
    ui->setupUi(this);
//showFullScreen();

}

Cadence::~Cadence()
{
    delete ui;
}


shared_memory SM_cadence;
temp2 temp2_cadence;

void write2temp2_cadence(int param ){
    temp2_cadence.temp_supp_flag = param;
    temp2_cadence.write2sharedmemory_fromtemp();
}


void Cadence::on_start_stimulating_clicked()
{
    int supp = 5;
    write2temp2_cadence(supp);

    this->hide();
    Stimulation *stimulation = new Stimulation();
    stimulation->show();
    stimulation->mainprogram();


    }

void Cadence::onCadenceChanged(float cad)
{
    //ui->current_cad->setText(QString::number(cad));
}



void Cadence::on_pushButton_clicked()
{
//    myCadenceThread->start();
}

void Cadence::on_start_stimulating_2_clicked()
{
    temp2_cadence.write2temp_fromshmem();
    float cadence=temp2_cadence.temp_current_cadence;
    ui->cad->setText(QString::number((int)cadence));

}

int Cadence::mainprogramcad(){


    pthread_t thread;
    pthread_create(&thread, NULL, internal_threadFunction, this);
    return 0;

}

void Cadence::mainthreadcad(){

//    signal(SIGINT, myInterruptHandler);


    struct timespec t_now;
    struct timespec t_next;
    struct timespec t_period;
    struct timespec t_wait;
    struct timespec pause_duration;

    //unsigned long int t_overflow = 0;   // measure the overflowed time for each cycle
    unsigned long int loop_count = 0;

    // t_period defines duration of one "running" cycle (1 ms in this case)
    t_period.tv_sec = 0;
    t_period.tv_nsec = DEFAULT_LOOP_TIME_NS;

    // pause_duration defines duration of pause considered when a buttton is pressed (1 s in this case)
    pause_duration.tv_sec = DEFAULT_BUTTON_PRESSED_PAUSE_S;
    pause_duration.tv_nsec = DEFAULT_BUTTON_PRESSED_PAUSE_NS;

    clock_gettime( CLOCK_MONOTONIC, &t_next);


    while(1){

       // Print values in real time
       temp2_cadence.write2temp_fromshmem();
       float cad=temp2_cadence.temp_current_cadence;
       ui->cad->setText(QString::number((int)cad));


       sleep(1);

    }


}



void Cadence::on_Back_clicked()
{
    this->hide();
     static trainingmodality *trmod= new trainingmodality(this);
     trmod->show();


}
