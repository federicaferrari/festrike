#include "user.h"
#include "ui_user.h"
#include <QFile>
#include <QTextStream>

#include "temp2.h"
temp2 temp2user;

User::User(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::User)
{
    ui->setupUi(this);
    showFullScreen();

}

User::~User()
{
    delete ui;
}

void write2tempfromuser(string param){


}




void User::on_selectUser_clicked()
{
//    ui->selectedFileValue->setText("");
//    QString filename = QFileDialog::getOpenFileName(this, tr("Open Config File"), "/home/pi/users", tr("Config file(*.cfg)"));
//    User userclass;
//    userclass.filename = filename.toStdString();

//// TODO: extract the name of the subject from the configfile with strcompare
////    int nome = stoi(userclass.filename);
////    string nome = userclass.filename;
//    int nome=8;


//    QString nameDisplay = filename;
//    nameDisplay.remove("/home/pi/users");
//    string nameDisplay2=nameDisplay.toStdString();
//    ui->selectedFileValue->setText(nameDisplay);

////    write2tempfromuser(nameDisplay2);

}


void User::on_backButton_clicked()
{
//    ui->selectedFileValue->setText("");
    this->hide();
    static MainWindow *mainW = new MainWindow(this);
    mainW->show();
}

void User::on_insertNewUser_clicked()
{
    ui->label1->setEnabled(true);
    ui->label2->setEnabled(true);

    ui->startingCurrentL0->setEnabled(true);
    ui->startingCurrentL1->setEnabled(true);
    ui->startingCurrentL2->setEnabled(true);
    ui->startingCurrentL3->setEnabled(true);

    ui->maxCurrentL0->setEnabled(true);
    ui->maxCurrentL1->setEnabled(true);
    ui->maxCurrentL2->setEnabled(true);
    ui->maxCurrentL3->setEnabled(true);

    ui->startCurrentValueL0->setEnabled(true);
    ui->startCurrentValueL1->setEnabled(true);
    ui->startCurrentValueL2->setEnabled(true);
    ui->startCurrentValueL3->setEnabled(true);
    ui->startCurrentValueR0->setEnabled(true);
    ui->startCurrentValueR1->setEnabled(true);
    ui->startCurrentValueR2->setEnabled(true);
    ui->startCurrentValueR3->setEnabled(true);

    ui->maxCurrentValueL0->setEnabled(true);
    ui->maxCurrentValueL1->setEnabled(true);
    ui->maxCurrentValueL2->setEnabled(true);
    ui->maxCurrentValueL3->setEnabled(true);
    ui->maxCurrentValueR0->setEnabled(true);
    ui->maxCurrentValueR1->setEnabled(true);
    ui->maxCurrentValueR2->setEnabled(true);
    ui->maxCurrentValueR3->setEnabled(true);

    ui->muscle1->setEnabled(true);
    ui->muscle2->setEnabled(true);
    ui->muscle3->setEnabled(true);
    ui->muscle4->setEnabled(true);
    ui->label3->setEnabled(true);
    ui->label3_2->setEnabled(true);
    ui->label3_3->setEnabled(true);
    ui->label3_4->setEnabled(true);

    ui->initialRange1->setEnabled(true);
    ui->initialRange2->setEnabled(true);
    ui->initialRange3->setEnabled(true);
    ui->initialRange4->setEnabled(true);
    ui->finalRange1->setEnabled(true);
    ui->finalRange2->setEnabled(true);
    ui->finalRange3->setEnabled(true);
    ui->finalRange4->setEnabled(true);

    ui->nameLabel->setEnabled(true);
    ui->nameValue->setEnabled(true);
}

void User::on_saveConfigButton_clicked()
{
    ui->ErrorMessage->setText("");
    QString name = ui->nameValue->toPlainText();

    if(name == "") {
        ui->ErrorMessage->setText("ERROR: no name inserted");
    }
    else {
//        QString filename = "/home/pi/users/configFile"+name+".cfg";
        QString filename = "/home/pi/users/configFile"+name+".txt";
        string filename_string = filename.toStdString();
        QFile file( filename );
        if ( file.open(QIODevice::ReadWrite | QIODevice::Append) )
        {
            QTextStream stream( &file ); //startCurrentValueL0 ->text().toInt();
//            stream << "initialCurrents = {" << endl;
//            stream << "    L0 = " << ui->startCurrentValueL0->text().toInt() << ";\n    L1 = " << ui->startCurrentValueL1->text().toInt() << ";\n    L2 = " << ui->startCurrentValueL2->text().toInt() << ";\n    L3 = " << ui->startCurrentValueL3->text().toInt() << ";" << endl;
//            stream << "    R0 = " << ui->startCurrentValueR0->text().toInt() << ";\n    R1 = " << ui->startCurrentValueR1->text().toInt() << ";\n    R2 = " << ui->startCurrentValueR2->text().toInt() << ";\n    R3 = " << ui->startCurrentValueR3->text().toInt() << ";\n}" << endl;

//            stream << "\ninitialLeftRanges = {" << endl;
//            stream << "    L0 = " << ui->initialRange1->text().toInt() << ";\n    L1 = " << ui->initialRange2->text().toInt() << ";\n    L2 = " << ui->initialRange3->text().toInt() << ";\n    L3 = " << ui->initialRange4->text().toInt() << ";\n}" << endl;

//            stream << "\nfinalLeftRanges = {" << endl;
//            stream << "    L0 = " << ui->finalRange1->text().toInt() << ";\n    L1 = " << ui->finalRange2->text().toInt() << ";\n    L2 = " << ui->finalRange3->text().toInt() << ";\n    L3 = " << ui->finalRange4->text().toInt() << ";\n}" << endl;

            stream << 1 << ",";
            stream << ui->startCurrentValueL0->text().toInt() << "," << ui->startCurrentValueL1->text().toInt() << "," << ui->startCurrentValueL2->text().toInt() << "," << ui->startCurrentValueL3->text().toInt() << ","
                   << ui->startCurrentValueR0->text().toInt() << "," << ui->startCurrentValueR1->text().toInt() << "," << ui->startCurrentValueR2->text().toInt() << "," << ui->startCurrentValueR3->text().toInt() << ","

                   << ui->maxCurrentValueL0->text().toInt() << "," << ui->maxCurrentValueL1->text().toInt() << "," << ui->maxCurrentValueL2->text().toInt() << "," << ui->maxCurrentValueL3->text().toInt() << ","
                   << ui->maxCurrentValueR0->text().toInt() << "," << ui->maxCurrentValueR1->text().toInt() << "," << ui->maxCurrentValueR2->text().toInt() << "," << ui->maxCurrentValueR3->text().toInt() << ","

                   << ui->initialRange1->text().toInt() << "," << ui->initialRange2->text().toInt() << ", " << ui->initialRange3->text().toInt() << ", " << ui->initialRange4->text().toInt() << ","
                   << ui->finalRange1->text().toInt() << "," << ui->finalRange2->text().toInt() << "," << ui->finalRange3->text().toInt() << "," << ui->finalRange4->text().toInt() << endl;

            ui->ErrorMessage->setText("Config file SAVED");
        }
    }
}
