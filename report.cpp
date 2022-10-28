#include "report.h"
#include "ui_report.h"
#include "stimulator.h"
#include "pid.h"
#include "shared_memory.h"
#include "temp2.h"
temp2 temp2_report;

Report::Report(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Report)
{
    ui->setupUi(this);
    mainprogram();
  showFullScreen();

}

Report::~Report()
{
    delete ui;
}

void writeflagthread2temp(bool param1, bool param2){
    temp2_report.temp_thread_running = param1;
    temp2_report.temp_stop_thread_running = param2;
    temp2_report.write2sharedmemory_fromtemp();
}


void Report::mainprogram(){

    // Print values in real time
    temp2_report.write2temp_fromshmem();
//    float qsx=temp2_stim.temp_current_quadriceps_left;
//    float qdx=temp2_stim.temp_current_quadriceps_right;
//    float glsx=temp2_stim.temp_current_gluteus_left;
//    float gldx=temp2_stim.temp_current_gluteus_right;
//    float gasx=temp2_stim.temp_current_gastro_left;
//    float gadx=temp2_stim.temp_current_gastro_right;
//    float hsx=temp2_stim.temp_current_hamstring_left;
//    float hdx=temp2_stim.temp_current_hamstring_right;
    double cad=temp2_report.temp_mean_cadence;
    int minutes_d = temp2_report.temp_min_d;
    int minutes_u = temp2_report.temp_min_u;
    int seconds_d = temp2_report.temp_sec_d;
    int seconds_u = temp2_report.temp_sec_u;
    int minutes_d_sat = temp2_report.temp_min_d_sat;
    int minutes_u_sat = temp2_report.temp_min_u_sat;
    int seconds_d_sat = temp2_report.temp_sec_d_sat;
    int seconds_u_sat = temp2_report.temp_sec_u_sat;
    double HR = temp2_report.temp_HR;
//    ui->qsx->setText(QString::number((int)qsx));
//    ui->glsx->setText(QString::number((int)glsx));
//    ui->hsx->setText(QString::number((int)hsx));
//    ui->gasx->setText(QString::number((int)gasx));
//    ui->qdx->setText(QString::number((int)qdx));
//    ui->gldx->setText(QString::number((int)gldx));
//    ui->hdx->setText(QString::number((int)hdx));
//    ui->gadx->setText(QString::number((int)gadx));
    ui->cadencefinal->setText(QString::number(static_cast<double>(cad)));
    ui->durationmin_u->setText(QString::number((int)minutes_u));
    ui->durationmin_d->setText(QString::number((int)minutes_d));
    ui->durationsec_u->setText(QString::number((int)seconds_u));
    ui->durationsec_d->setText(QString::number((int)seconds_d));
    ui->durationmin_u_sat->setText(QString::number((int)minutes_u_sat));
    ui->durationmin_d_sat->setText(QString::number((int)minutes_d_sat));
    ui->durationsec_u_sat->setText(QString::number((int)seconds_u_sat));
    ui->durationsec_d_sat->setText(QString::number((int)seconds_d_sat));
    ui->HRfinal->setText(QString::number((int)HR));

}

void Report::on_pushButton_clicked()
{
    // TODO: terminate programs and close all
    this->close();
    bool report_running = 0;
    bool stop_running =1;
    writeflagthread2temp(report_running, stop_running);

}

void Report::on_pushButton_2_clicked()
{
    this->hide();
    static MainWindow *mainW = new MainWindow(this);
    mainW->show();
}
