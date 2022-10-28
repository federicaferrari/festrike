#include "trainingmodality.h"
#include "ui_trainingmodality.h"
#include "shared_memory.h"
#include "temp2.h"



trainingmodality::trainingmodality(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::trainingmodality)
{
    ui->setupUi(this);
  showFullScreen();
}

trainingmodality::~trainingmodality()
{
    delete ui;
}

shared_memory SM_training;
temp2 temp2_training;


void write2temp2(int param1){

     temp2_training.temp_type_training_from_gui=param1;
     temp2_training.write2sharedmemory_fromtemp();

}



void trainingmodality::on_forward_clicked()
{
    this->hide();
    static Cadence *cadence=new Cadence(this);

    cadence->show();
    cadence->mainprogramcad();
}

void trainingmodality::on_back_clicked()
{
    this->hide();
    static Input *inp = new Input(this);
    inp->show();
}




void trainingmodality::on_HIIT_clicked()
{
    if (ui->HIIT->isChecked()==true){
        int type_selected=1;
        write2temp2(type_selected);}

    if (ui->HIIT->isChecked()==false){
        int type_selected=0;
        write2temp2(type_selected);}

}

void trainingmodality::on_PID_clicked()
{
    if (ui->PID->isChecked()==true){
        int type_selected=2;
        write2temp2(type_selected);}

    if (ui->PID->isChecked()==false){
        int type_selected=0;
        write2temp2(type_selected);}
}

void trainingmodality::on_TESTGARA_clicked()
{
    if (ui->TESTGARA->isChecked()==true){
        int type_selected=3;
        write2temp2(type_selected);}

    if (ui->TESTGARA->isChecked()==false){
        int type_selected=0;
        write2temp2(type_selected);}
}

void trainingmodality::on_RISCALDAMENTO_clicked()
{
    if (ui->RISCALDAMENTO->isChecked()==true){
        int type_selected=4;
        write2temp2(type_selected);}

    if (ui->RISCALDAMENTO->isChecked()==false){
        int type_selected=0;
        write2temp2(type_selected);}
}

void trainingmodality::on_FATICA_clicked()
{
    if (ui->FATICA->isChecked()==true){
        int type_selected=5;
        write2temp2(type_selected);}

    if (ui->FATICA->isChecked()==false){
        int type_selected=0;
        write2temp2(type_selected);}
}
