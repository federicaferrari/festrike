#include "input.h"
#include "ui_input.h"
#include "shared_memory.h"
#include "temp2.h"
#include "mainwindow.h"




Input::Input(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Input)
{
    ui->setupUi(this);
    showFullScreen();

}

Input::~Input()
{
    delete ui;
}

Input::stimulationInputs newInput;

shared_memory SM_input;
temp2 temp2_input;


void write2temp2(int param1, int param2, int param3, int param4 ){

     temp2_input.temp_saturation_current_from_gui=param1;
     temp2_input.temp_pulse_width_from_gui=param2;
     temp2_input.temp_target_cadence_from_gui=param3;
     temp2_input.temp_modality_from_gui=param4;
     temp2_input.write2sharedmemory_fromtemp();

}

void writeflagtotemp(int param){
    temp2_input.temp_flag_save=param;
    temp2_input.write2sharedmemory_fromtemp();
}


void Input::on_pushButton_clicked()
{

    int max_amplitude = ui->selectedAmplitude->text().toInt();
    int pulsewidth = ui->selectedPulsewidth->text().toInt();
    int cadenza = ui->selectedCadence->text().toInt();
    int strategy = ui->selectedStrategy->text().toInt();
    write2temp2(max_amplitude, pulsewidth, cadenza, strategy);
    int param1 = 3;
    writeflagtotemp(param1);
    this->hide();
    static trainingmodality *trmod=new trainingmodality(this);

    trmod->show();



}

void Input::on_pushButton_2_clicked()
{
    this->hide();
    static MainWindow *mainW = new MainWindow(this);
    mainW->show();

}
