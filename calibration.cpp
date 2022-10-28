#include "calibration.h"
#include "ui_calibration.h"
#include "temp2.h"

calibration::calibration(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::calibration)
{
    ui->setupUi(this);
//    mThread = new mythread(this);
//    connect(mThread, SIGNAL(NumberChanged(int)), this, SLOT(onNumberChanged(int)));
  showFullScreen();

}


#define DEFAULT_LOOP_TIME_NS 1000000L
#define DEFAULT_BUTTON_PRESSED_PAUSE_S 1
#define DEFAULT_BUTTON_PRESSED_PAUSE_NS 0

calibration::~calibration()
{
    delete ui;
}


temp2 temp2_calibration;

void write2temp2_calibration(int param){
    temp2_calibration.temp_flag_calibrate=param;
}

void calibration::on_pushButton_clicked()
{

    QString stimulator=ui->stim->text();
    temp2_calibration.temp_stimulator_calibration=stimulator.toInt();
    QString canale=ui->canale_2->text();
    temp2_calibration.temp_channel_calibration=canale.toInt();
    QString corrente_1=ui->corrente->text();
    temp2_calibration.temp_current_calibration=corrente_1.toInt();
    QString pulsewidth=ui->pulsewidth->text();
    temp2_calibration.temp_pulsewidth_calibration=pulsewidth.toInt();
    QString frequency=ui->frequenza->text();
    temp2_calibration.temp_period_calibration= (1/frequency.toInt())*1000;

    temp2_calibration.temp_flag_calibrate=1;
    temp2_calibration.write2sharedmemory_fromtemp();
    ui->lineEdit->setText("STIMOLAZIONE ACCESA");

}

void calibration::on_pushButton_2_clicked()
{
    temp2_calibration.temp_flag_calibrate=0;
    ui->lineEdit->setText("STIMOLAZIONE SPENTA");
    temp2_calibration.write2sharedmemory_fromtemp();

}

void calibration::on_pushButton_3_clicked()
{
    this->hide();
    static MainWindow *mainW = new MainWindow(this);
    mainW->show();


}

int calibration::loop_angle(){

    pthread_t thread;
    pthread_create(&thread, nullptr, internal_threadFunction, this);
    return 0;


}

void calibration::thread_angle(){


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
        temp2_calibration.write2temp_fromshmem();
        int angolo = temp2_calibration.temp_angle_encoder;
        // print angle
        ui->angle->setText(QString::number((int)angolo));
        sleep(1);

    }
}
