#ifndef STIMULATION_H
#define STIMULATION_H

#include <QDialog>
#include <QApplication>
//#include "program.h"
#include "globalvariables.h"
#include "cadenceblock.h"
#include "chart.h"
//#include "fine.h"
#include "report.h"

namespace Ui {
class Stimulation;
}


class Stimulation : public QDialog
{
    Q_OBJECT

private:
     static void *internal_threadFunction(void * This){((Stimulation *)This)->mainthread(); return nullptr;}
public:
    explicit Stimulation(QWidget *parent = nullptr);
    ~Stimulation();

    bool cadenceChanged = false;
    int mainprogram();
    void mainthread();
    void mainthread_old();
    void mainthread_gui();
    float cadence;
    float streamCurrent;
    float streamPW;
    float streamPI;
    bool correndo=false;
    double Tinter[4]={0,0,0,0};
    int program=0;
    int freqB=0;
    void setfrequencies();
    void printvalues();

    void leggiangoli();
    bool pluto_start = 0;

public slots:
//    void onSomethingChanged(bool val);
//    void onSomethingChanged();
//    void print();


private slots:
    void on_startStopButton_clicked();

//    void on_returnButton_clicked();

////    void on_startStopButton_2_clicked();

//    void on_startStopButton_2_clicked();

//    void on_startStopButton_3_clicked();

    //    void on_startStopButton_4_clicked();



    void on_startStopButton_4_clicked();

    void on_startStopButton_3_clicked();

    void on_startStopButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

public:
    Ui::Stimulation *ui;
};

#endif // STIMULATION_H
