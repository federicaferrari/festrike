#ifndef CADENCE_H
#define CADENCE_H

//#include "cadencethread.h"
#include <QDialog>
#include "stimulation.h"
#include "input.h"
//#include "stimthread.h"
//#include "program.h"


namespace Ui {
class Cadence;
}

class Cadence : public QDialog
{
    Q_OBJECT
private:
      static void *internal_threadFunction(void * This){((Cadence *)This)->mainthreadcad(); return nullptr;}

public:
    explicit Cadence(QWidget *parent = nullptr);
    ~Cadence();
    bool startFlag = false;
//    cadenceThread *myCadenceThread;
    int mainprogramcad();
    void mainthreadcad();

private slots:
    void on_start_stimulating_clicked();
    void on_pushButton_clicked();



    void on_start_stimulating_2_clicked();

    void on_Back_clicked();

private:
    Ui::Cadence *ui;

public slots:
    void onCadenceChanged(float);
};
#endif // CADENCE_H
