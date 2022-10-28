#ifndef CALIBRATION_H
#define CALIBRATION_H

#include <QDialog>
//#include "mythread.h"
#include "mainwindow.h"


namespace Ui {
class calibration;
}

class calibration : public QDialog
{
    Q_OBJECT

public:
    explicit calibration(QWidget *parent = nullptr);
    ~calibration();
//    mythread *mThread;
        int loop_angle();
        void thread_angle();
private:
    Ui::calibration *ui;
         static void *internal_threadFunction(void * This){((calibration *)This)->thread_angle(); return nullptr;}

public slots:
//    void onNumberChanged(int);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
//    void on_lineEdit_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_3_clicked();

};

#endif // CALIBRATION_H










