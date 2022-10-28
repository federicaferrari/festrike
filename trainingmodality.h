#ifndef TRAININGMODALITY_H
#define TRAININGMODALITY_H

#include <QDialog>
#include "input.h"
#include "cadence.h"
#include "header.h"
#include "QCheckBox"

namespace Ui {
class trainingmodality;
}

class trainingmodality : public QDialog
{
    Q_OBJECT

public:
    explicit trainingmodality(QWidget *parent = nullptr);
    ~trainingmodality();

private slots:
    void on_forward_clicked();

    void on_back_clicked();

    void on_HIIT_clicked();

    void on_PID_clicked();

    void on_TESTGARA_clicked();

    void on_RISCALDAMENTO_clicked();

    void on_FATICA_clicked();

private:
    Ui::trainingmodality *ui;
};

#endif // TRAININGMODALITY_H
