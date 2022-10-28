#ifndef USER_H
#define USER_H

#include <QDialog>
#include <QFileDialog>
#include <QApplication>
#include "header.h"
#include "mainwindow.h"

using namespace std;

namespace Ui {
class User;
}

class User : public QDialog
{
    Q_OBJECT

public:
    explicit User(QWidget *parent = nullptr);
    ~User();
    string filename;

private slots:
    void on_selectUser_clicked();

    void on_backButton_clicked();

    void on_insertNewUser_clicked();

    void on_saveConfigButton_clicked();

private:
    Ui::User *ui;
};
#endif // USER_H
