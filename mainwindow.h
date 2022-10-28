#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "input.h"
#include "user.h"
#include "calibration.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Start_clicked();

    void on_closeButton_clicked();

    void on_User_clicked();



    void on_Calibration_clicked();

//    void on_User_2_clicked();

    void on_User_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
