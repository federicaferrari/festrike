#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QFile>
#include <QTextStream>
#include "temp2.h"
#include "shared_memory.h"
#include "iostream"
#include <string>
#include <sstream>
#include "globalvariables.h"


#define CURRENTS_NODE_NAME  "initialCurrents"
#define LEFT_INIT_RANGES_NODE_NAME  "initialLeftRanges"
#define LEFT_FINAL_RANGES_NODE_NAME  "finalLeftRanges"
#define L0_NODE_NAME  "L0"
#define L1_NODE_NAME  "L1"
#define L2_NODE_NAME  "L2"
#define L3_NODE_NAME  "L3"
#define R0_NODE_NAME  "R0"
#define R1_NODE_NAME  "R1"
#define R2_NODE_NAME  "R2"
#define R3_NODE_NAME  "R3"

temp2 temp2mw;

void write2tempfrommw(std::string param){
    temp2mw.temp_file_name = param;
    temp2mw.writenametosm();
}

void write2tempfrommw2(char param){
    temp2mw.temp_file_name_char = param;
    temp2mw.writenametosm2();
}


void writeflagthread2temp2(bool param1, bool param2){
    temp2mw.temp_thread_running = param1;
    temp2mw.temp_stop_thread_running = param2;
    temp2mw.write2sharedmemory_fromtemp();
}

 std::string name;
 vector <double> initC(8) ;
 vector <double> finC(8) ;
 vector <double> initR_left(8);
 vector <double> initR_right(8);

 void read_init_file(string gatto){
  fstream fin;
  fin.open(gatto,ios::in);
  int rollnum =1, roll2, count=0;
  vector<string> row;
  string line;
  string word;
  string temp;

  row.clear();

  getline(fin,line);

  stringstream s(line);

  while(getline(s,word,','))
  {
      row.push_back(word);
  }
    roll2=stoi(row[0]);
    if(roll2==rollnum){
        count=1;
        initC[0] = stod(row[1]);
        initC[1] = stod(row[2]);
        initC[2] = stod(row[3]);
        initC[3] = stod(row[4]);
        initC[4] = stod(row[5]);
        initC[5] = stod(row[6]);
        initC[6] = stod(row[7]);
        initC[7] = stod(row[8]);

        finC[0] = stod(row[9]);
        finC[1] = stod(row[10]);
        finC[2] = stod(row[11]);
        finC[3] = stod(row[12]);
        finC[4] = stod(row[13]);
        finC[5] = stod(row[14]);
        finC[6] = stod(row[15]);
        finC[7] = stod(row[16]);

        initR_left[0] = stod(row[17]);
        initR_left[1] = stod(row[18]);
        initR_left[2] = stod(row[19]);
        initR_left[3] = stod(row[20]);
        // from 4 to 7 is final ranges
        initR_left[4] = stod(row[21]);
        initR_left[5] = stod(row[22]);
        initR_left[6] = stod(row[23]);
        initR_left[7] = stod(row[24]);

        // right da ricavare
        for(int i=0; i<8; i++){
           initR_right[i] = initR_left[i] + 180;
           if(initR_right[i] > 360) initR_right[i] = initR_right[i] - 360;
        }

        cout << "\nInitial currents are: " << initC[0] << " " << initC[1] << " " << initC[2] << " " << initC[3] << " " << initC[4] << " " << initC[5] << " " << initC[6] << " " << initC[7] << endl;
        cout << "\nFinal currents are: " << finC[0] << " " << finC[1] << " " << finC[2] << " " << finC[3] << " " << finC[4] << " " << finC[5] << " " << finC[6] << " " << finC[7] << endl;

        cout << "\nInitial ranges left are: " << initR_left[0] << " " << initR_left[1] << " " << initR_left[2] << " " << initR_left[3] << " " << initR_left[4] << " " << initR_left[5] << " " << initR_left[6] << " " << initR_left[7] << endl;
        cout << "\nInitial ranges right are: " << initR_right[0] << " " << initR_right[1] << " " << initR_right[2] << " " << initR_right[3] << " " << initR_right[4] << " " << initR_right[5] << " " << initR_right[6] << " " << initR_right[7] << endl;

        // Passa alla SM
        for (int i=0; i<8; i++){
            temp2mw.temp_correnti_iniziali[i] = initC[i];
            temp2mw.temp_correnti_finali[i] = finC[i];

            temp2mw.temp_range_iniziali_dx[i] = initR_right[i];
            temp2mw.temp_range_iniziali_sx[i] = initR_left[i];

        }


    }
    if (count==0){
        cout<< "\nFile not found"<<endl;
    }


 }




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("/home/pi/Desktop/trikino.png");
    //    ui -> labelpic ->setPixmap(pix.scaled(250,250));
//    showFullScreen();


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Start_clicked()
{
//    write2tempfrommw(name);
    this->hide();
    static Input *input=new Input(this);
    input->show();
}

void MainWindow::on_closeButton_clicked()
{
    this->~MainWindow();
    bool report_running = 0;
    bool stop_running =1;
    writeflagthread2temp2(report_running, stop_running);
}

void MainWindow::on_User_clicked()
{
    this->hide();
    static User *user = new User(this);
    user->show();
}

void MainWindow::on_Calibration_clicked()
{
    this->hide();
    static calibration *mcalibration = new calibration(this);
    mcalibration->show();
    mcalibration->loop_angle();
}







void MainWindow::on_User_2_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Config File"), "/home/pi/users", tr("Config file(*.txt)"));
    User userclass;


    // Plot on GUI
    QString nameDisplay = filename;
    nameDisplay.remove("/home/pi/users/configFile");
    QString filename2;
    filename2 = nameDisplay.remove("/home/pi/users/configFile");
    QString filename3;
    filename3= filename2.remove(".txt");
    ui->namefile->setText(filename3);


    // Read Configure File
    libconfig::Config initialConfig;
    std::string namefile=filename.toStdString();

    cout << "\nString file name: " << namefile;
    read_init_file(namefile);
    temp2mw.write2sharedmemory_initial();
//    initialConfig.readFile(namefile.c_str());
//    const auto& root = initialConfig.getRoot();
//    root.TypeFloat;
//    vector <double> initC(8) ;
//    vector <double> initR_left(8);
//    vector <double> initR_right(8);

//    initC[0] = 2.0;
//    initC[1] = 2.0;
//    initC[2] = 2.0;
//    initC[3] = 2.0;
//    initC[4] = 2.0;
//    initC[5] = 2.0;
//    initC[6] = 2.0;
//    initC[7] = 2.0;


//    cout << "\nInitial currents are: " << initC[0] << " " << initC[1] << " " << initC[2] << " " << initC[3] << " " << initC[4] << " " << initC[5] << " " << initC[6] << " " << initC[7] << endl;
//    cout << "\nAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" << endl;

//    // right da ricavare
//    for(int i=0; i<8; i++){
//       initR_right[i] = initR_left[i] + 180;
//       if(initR_right[i] > 360) initR_right[i] = initR_right[i] - 360;
//    }



//    // Passa alla SM
//    for (int i=0; i<8; i++){
//        temp2mw.temp_correnti_iniziali_dx[i] = initC[i];
//        temp2mw.temp_correnti_iniziali_sx[i] = initC[i];
//        temp2mw.temp_range_iniziali_dx[i] = initR_right[i];
//        temp2mw.temp_range_iniziali_sx[i] = initR_left[i];
//        temp2mw.write2sharedmemory_fromtemp();
//    }
}





void MainWindow::on_pushButton_clicked()
{

    temp2mw.write2temp_fromshmem();
    bool ok1 = temp2mw.temp_ok_stim1;
    bool ok2 = temp2mw.temp_ok_stim2;
    bool ok_pedalL =temp2mw.temp_ok_pedal_left;
    bool ok_pedalR =temp2mw.temp_ok_pedal_right;
    bool ok_heart =temp2mw.temp_ok_cardio;

        if(ok1==1 && ok2==1){
            ui->label_okstim->setText("OK");}
        else {
        ui->label_okstim->setText("NON OK");}

    if(ok_heart==1){
        ui->label_okcardio->setText("OK");}
    else {
    ui->label_okcardio->setText("NON OK");}

    if(ok_pedalL==1 && ok_pedalR==1){
        ui->label_okpedal->setText("OK");}
    else {
    ui->label_okpedal->setText("NON OK");}

}
