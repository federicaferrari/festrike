#ifndef INPUT_H
#define INPUT_H

#include <QDialog>
//#include "cadence.h"
#include "trainingmodality.h"
//#include "thread_stim.h"
#include "header.h"
#include "stimulation.h"
//#include "mainwindow.h"
namespace Ui {
class Input;
}

class Input : public QDialog
{
    Q_OBJECT

public:
    explicit Input(QWidget *parent = nullptr);
    ~Input();


    struct stimulationInputs
    {
        int strategy;
        int stimFrequency;
        int stimPeriod;
        int max_amplitude;
        int pulsewidth;
        int cadence;

    };

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

//    void on_selectedStrategy_valueChanged(const QString &arg1);

private:
    Ui::Input *ui;
};

extern Input::stimulationInputs newInput;

#endif // INPUT_H
