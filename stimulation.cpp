#include "stimulation.h"
#include "ui_stimulation.h"
#include "stimulator.h"
#include "pid.h"
//#include "fine.h"
#include "temp2.h"
//#include "shared_memory.h"


#define DEFAULT_LOOP_TIME_NS 1000000L
#define DEFAULT_BUTTON_PRESSED_PAUSE_S 1
#define DEFAULT_BUTTON_PRESSED_PAUSE_NS 0

//shared_memory stim_shmem;
temp2 temp2_stim;

int pid_training = 0;
int pid_training_old = 0;
bool flag_up = 0;
bool flag_up_old = 0;
bool flag_down = 0;
bool flag_down_old = 0;

Stimulation::Stimulation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Stimulation)
{
    ui->setupUi(this);
showFullScreen();



}


Stimulation::~Stimulation()
{
    delete ui;
}


void writebuttons2temp(bool param1, bool param2, bool param3){

    temp2_stim.temp_start_training=param1;
    temp2_stim.temp_stop_training=param2;
    temp2_stim.temp_pause_training=param3;
//    temp2_stim.temp_pippo_start = pluto_start;
    temp2_stim.write2sharedmemory_fromtemp();

}


void writeflagup2temp(bool param){

    temp2_stim.temp_up = param;
    temp2_stim.write_uppi_2sharedmemory_fromtemp();
}

void writeflagdown2temp(bool param){
    temp2_stim.temp_down = param;
    temp2_stim.write_downi_2sharedmemory_fromtemp();
}


void writeflagpid2temp(bool param){
    temp2_stim.temp_pid = param;
    temp2_stim.write2sharedmemory_fromtemp();
}


int Stimulation::mainprogram(){


    pthread_t thread;
    pthread_create(&thread, nullptr, internal_threadFunction, this);
    return 0;

}

void Stimulation::mainthread(){

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
       temp2_stim.write2temp_fromshmem();

       float qsx=temp2_stim.temp_current_quadriceps_left;
       float qdx=temp2_stim.temp_current_quadriceps_right;
       float glsx=temp2_stim.temp_current_gluteus_left;
       float gldx=temp2_stim.temp_current_gluteus_right;
       float gasx=temp2_stim.temp_current_gastro_left;
       float gadx=temp2_stim.temp_current_gastro_right;
       float hsx=temp2_stim.temp_current_hamstring_left;
       float hdx=temp2_stim.temp_current_hamstring_right;

       float cad=temp2_stim.temp_current_cadence;

       int minutes_d = temp2_stim.temp_min_d;
       int minutes_u = temp2_stim.temp_min_u;
       int seconds_d = temp2_stim.temp_sec_d;
       int seconds_u = temp2_stim.temp_sec_u;

       int trg_cad = temp2_stim.temp_trg_cad;

       int freqcuore = temp2_stim.temp_HR;

       double POL =temp2_stim.temp_m_POL;
       double POR =temp2_stim.temp_m_POR;

//       double percL =temp2_stim.temp_sim_left;
//       double percR =temp2_stim.temp_sim_right;


       ui->qsx->setText(QString::number((int)qsx));
       ui->glsx->setText(QString::number((int)glsx));
       ui->hsx->setText(QString::number((int)hsx));
       ui->gasx->setText(QString::number((int)gasx));
       ui->qdx->setText(QString::number((int)qdx));
       ui->gldx->setText(QString::number((int)gldx));
       ui->hdx->setText(QString::number((int)hdx));
       ui->gadx->setText(QString::number((int)gadx));

       ui->label_7->setText(QString::number((int)cad));

       ui->min_u->setText(QString::number((int)minutes_u));
       ui->min_d->setText(QString::number((int)minutes_d));
       ui->sec_u->setText(QString::number((int)seconds_u));
       ui->sec_d->setText(QString::number((int)seconds_d));

       ui->trg_cad->setText(QString::number((int)trg_cad));

       ui->label_HR->setText(QString::number((int)freqcuore));

       ui->label_3->setText(QString::number(static_cast<double>(POL)));
       ui->label_5->setText(QString::number(static_cast<double>(POR)));
       //ui->label_start->setText(QString::number((int)temp2_stim.temp_start_training));

//       ui->label_14->setText(QString::number(static_cast<double>(percL)));
//       ui->label_10->setText(QString::number(static_cast<double>(percR)));

       bool pid_label = temp2_stim.temp_pid;
       if(pid_label==1){
       ui->label_pid->setText("ON");}
       else if(pid_label==0){
       ui->label_pid->setText("OFF");}


       // se viene premuto ed era diverso da prima manda un flag e rimetti flag a 0


       sleep(1);

    }


}









void Stimulation::on_startStopButton_2_clicked()
{
    // START
    bool start_tr = 1;
    bool stop_tr  = 0;
    bool pause_tr = 0;

    // read name from SM
//    if(pluto_start==0) pluto_start=1;
//    else if(pluto_start==1) pluto_start=0;
    writebuttons2temp(start_tr, stop_tr, pause_tr);
//    temp2_stim.write_start_2sharedmemory_fromtemp();

}



void Stimulation::on_startStopButton_4_clicked()
{
    // PAUSE
    bool start_tr = 0;
    bool stop_tr = 0;
    bool pause_tr = 1;
    writebuttons2temp(start_tr, stop_tr, pause_tr);
}


void Stimulation::on_startStopButton_clicked()
{
    // stop
    bool start_tr = 0;
    bool stop_tr = 1;
    bool pause_tr = 0;
    writebuttons2temp(start_tr, stop_tr, pause_tr);
    if(correndo)
        correndo = false;
    // GOTO new window that says TRAINING FINISHED !!
    this->hide();
    static Report *report = new Report(this);
    report->show();

}


void Stimulation::on_startStopButton_3_clicked()
{

    if (pid_training_old==0){
    pid_training = 1;
//    ui->label_pid->setText("ON");

    }

    else if(pid_training_old==1){
        pid_training = 0;
//        ui->label_pid->setText("OFF");
    }

    pid_training_old=pid_training;
    writeflagpid2temp(pid_training);

}







void Stimulation::on_pushButton_3_clicked()
{
    bool flaggi_uppi = 1;
    writeflagup2temp(flaggi_uppi);
}


void Stimulation::on_pushButton_4_clicked()
{
    bool flaggi_downi = 1;
    writeflagdown2temp(flaggi_downi);
}
