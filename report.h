#ifndef REPORT_H
#define REPORT_H

#include <QDialog>
#include <QApplication>
#include "header.h"
#include "mainwindow.h"
#include "globalvariables.h"
#include "cadenceblock.h"
#include "chart.h"

namespace Ui {
class Report;
}

class Report : public QDialog
{
    Q_OBJECT

public:
    explicit Report(QWidget *parent = nullptr);
    ~Report();

    void mainprogram();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Report *ui;
};

#endif // REPORT_H
