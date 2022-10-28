#include "globalvariables.h"
#include "header.h"
#include "thread_app.h"
thread_app app2;


// variables TO SET
int error_angle = 0;
double targetCadence = 35.0;
double target_cadence_new= 35.0;
int target_cadence_old = 0;
float CadenceOld = 0;

bool thread_running = 1;

const std::string nomino2;
char nome_char_fes;

int mainF = 200; // Hz ?? encoder frequency?
int stimF = 40; // Hz
int mainT = 1000/mainF; // period in ms

int stimT = 1000/stimF;

int stimF_D=20;
int stimF_ID = 80;
int stimT_D = 50;
int stimT_ID = 13;

vector<int> waveCoeff = {1, 0, -1};

vector<double> initialCurrents = { 5, 5, 5, 5, 5, 5, 5, 5 };
vector<double> finalCurrents = { 5, 5, 5, 5, 5, 5, 5, 5 };
vector<double> initialRanges_left = { 130, 180, 300, 310, 240, 290, 50, 50 };
vector<double> initialRanges_right = { 310, 360, 120, 130, 60, 110, 230, 230 };
vector<double> marginiL = { 0, 0, 0, 0};
vector<double> marginiR = { 0, 0, 0, 0};
vector<double> maxCurrR = {5,5,5,5};
vector<double> maxCurrL = {5,5,5,5};

double currentIncrement = 5; // mA

uint8_t number_of_points = 3; // 1-16

double PulseWidth = 400; // us

double maxCurrentL = 125; // mA
double maxCurrentR = 125; // mA

bool guibutton_start    = 0;
bool guibutton_start_old    = 0;
bool guibutton_stop     = 0;
bool guibutton_pid      = 0;
bool guibutton_pause    = 0;
bool guibutton_up       = 0;
bool guibutton_down     = 0;
bool up_fromgui_old     = 0;
bool down_fromgui_old   = 0;
int old_pid_from_gui = 0;

bool uppi = 0;
bool downi = 0;


int selected_frontGear = 2;
int selected_backGear = 7;

bool ginosu=0;
bool ginogiu=0;

bool ginosu_old=0;
bool ginogiu_old=0;

vector<int> frontGears = {50, 39, 30};
vector<int> backGears =
{36, 32, 28, 25, 22, 19, 17, 15, 13, 11};

float circumference = 2.136; // meters

float angle = -1.0;
float angleOld = -1.0;
float cadence;
float old_cadence = 0;
float del;

bool flag_c = 0;

vector<double> theoreticalCurrentsL(4);
vector<double> theoreticalCurrentsR(4);

vector<double> actualCurrentsL(4);
vector<double> actualCurrentsR(4);

vector<bool> modulateON = {1, 1, 1, 1};

double pidCoefficient = 0.0;

// PID parameters
double kp = 0.0025;
double kd = 0.0;
double ki = 0.005;

ofstream CSVfile;
ofstream CSVfile2;
ofstream BLEfileR ("/home/pi/TrikeStimulation/por");
ofstream BLEfileL ("/home/pi/TrikeStimulation/pol");
struct timespec timeStartThread;
struct timespec timeLoop;

double HR;
double POL;
double POR;
double mean_POR;
double mean_POL;
double TgL;
double TgR;
double RadL;
double RadR;
double percPOR;
double percPOL;
double smoothR;
double smoothL;
double effL;
double effR;

double angle_ped_left;
double angle_ped_right;
float time_ped_left;
float time_ped_right;
double cad_ped_right;
double cad_ped_left;
double max_current_value;

double fsx_med;
double fdx_med;

int mod;
int sup;
int sup2;
bool input_running;
bool supp_flag = 0;
int Init_saturation_current = 0;
int Init_pulse_width = 0;
int Init_target_cadence = 0;
int flag_save = 0;
int flag_save_old =0 ;


int stim_calib = 0;
int curr_calib= 0;
int pw_calib= 0;
int channel_calib= 0;

int nome = 0;

bool flag_cicle_ble_right = 0;
double mean_force_left = 0.0;
double mean_force_right = 0.0;
double simsx = 0.0;
double simdx = 0.0;
double coeff_symm = 0.0;


long timeStructToMs(timespec t) // transforms time as struct to a long integer (time in ms)
{
    long result;

    result = t.tv_sec*1000 + t.tv_nsec/1000000;

    return result;
}

long long timeStructTons(timespec t) // transforms time as struct to a long integer (time in ms)
{
    long long result;

    result = t.tv_sec*1000000000 + t.tv_nsec;

    return result;
}

timespec addition(timespec a, timespec b) {
    timespec r;

    if(a.tv_nsec + b.tv_nsec <= 999999999) {
        r.tv_nsec = a.tv_nsec + b.tv_nsec;
        r.tv_sec = a.tv_sec + b.tv_sec;
    }
    else {
        int c = (a.tv_nsec + b.tv_nsec)/1000000000;
        r.tv_nsec = a.tv_nsec + b.tv_nsec - 1000000000*c;
        r.tv_sec = a.tv_sec + b.tv_sec + c;
    }

    return r;
}




void interface(vector<double> &initC,  vector<double> &initR_left, vector<double> &initR_right){

    int stato = 0;
    double currentTempL[4] = {0.0, 0.0, 0.0, 0.0};
    double currentTempR[4] = {0.0, 0.0, 0.0, 0.0};
    double rangeTempL_init[4] = {0.0, 0.0, 0.0, 0.0};
    double rangeTempL_end[4] = {0.0, 0.0, 0.0, 0.0};
    string muscoli[4] = {"quadricipite", "gluteo", "hamstring", "gastrocnemio"};

    while(stato<5){
        switch (stato){

        case 0:
            // Parameter setting from terminal via keayboard
            cout << "Inserire i parametri dell'allenamento: " << endl;
            cout << "FASE 1: Inserire i valori di corrente desiderata per ciascun gruppo muscolare" << endl;
            cout << "*****************************************************************************" << endl;
            cout << "GAMBA SINISTRA"<< endl;

            for (int i = 0; i<4; i++) {
                do {
                    cout << muscoli[i];
                    cin >> currentTempL[i];
                    if(currentTempL[i] > 120) cout << "Errore: reinserire\n";
                }
                while(currentTempL[i] > 120);
            }

            cout << "\nGAMBA DESTRA"<< endl;

            for (int i = 0; i<4; i++) {
                do {
                    cout << muscoli[i];
                    cin >> currentTempR[i];
                    if(currentTempR[i] > 120) cout << "Errore: reinserire\n";
                }
                while(currentTempR[i] > 120);
            }

            cout << "*****************************************************************************" << endl;
            cout << "Il vettore delle correnti è il seguente:";

            for(int i=0; i<4; i++){
                cout << currentTempL[i];
                cout << " ; " ;
            }
            for(int i=0; i<4; i++){
                cout << currentTempR[i];
                cout << " ; " ;
            }

            cout << endl;
            stato=1;

            break;


        case 1:

            char confirm;
            cout << "Confermare? s/n  ";
            cin >> confirm;

            if(confirm== 's'){
                for(int i=0; i<4; i++){
                   initC[i] = currentTempL[i];
                }
                for(int i=4; i<8; i++){
                   initC[i] = currentTempR[i-4];
                }

                stato=2;
            }
            else if(confirm == 'n'){
                stato=0;
            }

            break;

         case 2:
            cout << "*****************************************************************************" << endl;
            cout << "FASE 2: Inserire i valori di range angolari desiderati per ciascun gruppo muscolare" << endl;
            cout << "GAMBA SINISTRA"<< endl;
            for (int i = 0; i<4; i++) {
                do {
                    cout << muscoli[i];
                    cin >> rangeTempL_init[i];
                    if(rangeTempL_init[i] > 360) cout << "Errore: reinserire\n";
                }
                while(rangeTempL_init[i] > 360);
            }

            cout << "\nGAMBA DESTRA"<< endl;

            for (int i = 0; i<4; i++) {
                do {
                    cout << muscoli[i];
                    cin >> rangeTempL_end[i];
                    if(rangeTempL_end[i] > 360) cout << "Errore: reinserire\n";
                }
                while(rangeTempL_end[i] > 360);
            }

            cout << "*****************************************************************************" << endl;
            cout << "Il vettore dei range è il seguente:";
            for(int i=0; i<4; i++){
                cout << rangeTempL_init[i];
                cout << " ; " ;
            }
            for(int i=0; i<4; i++){
                cout << rangeTempL_end[i];
                cout << " ; " ;
            }


            cout << endl;
            stato=3;

            break;

        case 3:

            char confirm2;
            cout << "Confermare? s/n  ";
            cin >> confirm2;

            if(confirm2== 's'){
                for(int i=0; i<4; i++){
                   initR_left[i] = rangeTempL_init[i];
                }
                for(int i=4; i<8; i++){
                   initR_left[i] = rangeTempL_end[i-4];
                }

                for(int i=0; i<8; i++){
                   initR_right[i] = initR_left[i] + 180;
                   if(initR_right[i] > 360) initR_right[i] = initR_right[i] - 360;
                }

                stato=4;
            }
            else if(confirm2 == 'n'){
                stato=2;
            }

            break;

        case 4:
            cout << "*****************************************************************************" << endl;
            do {
                cout << "FASE 3: Inserire il valore di FREQUENZA desiderata" << endl;
                cin >> stimF;
                if(stimF > 120) cout << "Errore: reinserire\n";
            } while(stimF > 120);
            cout << "*****************************************************************************" << endl;
            do {
                cout << "FASE 4: Inserire il valore di PULSEWIDTH desiderata" << endl;
                cin >> PulseWidth;
                if(PulseWidth > 500) cout << "Errore: reinserire\n";
            } while(PulseWidth > 500);
            stato=5;
            break;

        }
    }
}


void configure(vector<double> &initC,  vector<double> &initR_left, vector<double> &initR_right) {
    libconfig::Config initialConfig;

    //std::string name = to_string(nome);
    std::string configFilename = "/home/pi/Desktop/TrikeStimulation/configFilePaolo.cfg";

    // Use this with name passed from shared memory
    //std::string filename = "/home/pi/users/configFile"+name+".cfg";

    cout << "\nString file name: " << configFilename;
    initialConfig.readFile(configFilename.c_str());
    const auto& root = initialConfig.getRoot();
    root.TypeFloat;
    initC[0] = root[CURRENTS_NODE_NAME][L0_NODE_NAME];
    initC[1] = root[CURRENTS_NODE_NAME][L1_NODE_NAME];
    initC[2] = root[CURRENTS_NODE_NAME][L2_NODE_NAME];
    initC[3] = root[CURRENTS_NODE_NAME][L3_NODE_NAME];
    initC[4] = root[CURRENTS_NODE_NAME][R0_NODE_NAME];
    initC[5] = root[CURRENTS_NODE_NAME][R1_NODE_NAME];
    initC[6] = root[CURRENTS_NODE_NAME][R2_NODE_NAME];
    initC[7] = root[CURRENTS_NODE_NAME][R3_NODE_NAME];

    initR_left[0] = root[LEFT_INIT_RANGES_NODE_NAME][L0_NODE_NAME];
    initR_left[1] = root[LEFT_INIT_RANGES_NODE_NAME][L1_NODE_NAME];
    initR_left[2] = root[LEFT_INIT_RANGES_NODE_NAME][L2_NODE_NAME];
    initR_left[3] = root[LEFT_INIT_RANGES_NODE_NAME][L3_NODE_NAME];
    // from 4 to 7 is final ranges
    initR_left[4] = root[LEFT_FINAL_RANGES_NODE_NAME][L0_NODE_NAME];
    initR_left[5] = root[LEFT_FINAL_RANGES_NODE_NAME][L1_NODE_NAME];
    initR_left[6] = root[LEFT_FINAL_RANGES_NODE_NAME][L2_NODE_NAME];
    initR_left[7] = root[LEFT_FINAL_RANGES_NODE_NAME][L3_NODE_NAME];

    // right da ricavare
    for(int i=0; i<8; i++){
       initR_right[i] = initR_left[i] + 180;
       if(initR_right[i] > 360) initR_right[i] = initR_right[i] - 360;
    }

    cout << "\nInitial currents are: " << initC[0] << " " << initC[1] << " " << initC[2] << " " << initC[3] << " " << initC[4] << " " << initC[5] << " " << initC[6] << " " << initC[7] << endl;
    cout << "\nInitial ranges left are: " << initR_left[0] << " " << initR_left[1] << " " << initR_left[2] << " " << initR_left[3] << " " << initR_left[4] << " " << initR_left[5] << " " << initR_left[6] << " " << initR_left[7] << endl;
    cout << "\nInitial ranges right are: " << initR_right[0] << " " << initR_right[1] << " " << initR_right[2] << " " << initR_right[3] << " " << initR_right[4] << " " << initR_right[5] << " " << initR_right[6] << " " << initR_right[7] << endl;
}


void OpenFile(){
    // Get system  time
    time_t t = time(nullptr);
    struct tm * now = localtime( & t );
    char buffer [80];

    // Log directory
    strftime (buffer,80,"/home/pi/Desktop/Data_FESbike_Medea/AcquiredData-%Y-%m-%d-%H-%M-%S.csv",now);
    CSVfile.open (buffer);

//    std::string ciao = app2.pilot_name;
//    CSVfile.open ("/home/pi/Desktop/Pilot_Acquired_Data/AcquiredData-" + ciao);
    if(CSVfile.is_open()){

    CSVfile << endl

            << "time" << ","
            << "time ns" << ","
            << "angle" << ","
            << "cadence" << ","
            << "pid" << ","
            << "corrente effettiva Quad Sx" << ","
            << "corrente effettiva Glut Sx" << ","
            << "corrente effettiva Hams Sx" << ","
            << "corrente effettiva Gastro Sx" << ","
            << "corrente effettiva Quad Dx" << ","
            << "corrente effettiva Glut Dx" << ","
            << "corrente effettiva Hams Dx" << ","
            << "corrente effettiva Gastro Dx" << ","
            << "power_output_left" << ","
            << "power_output_right" << ","
            << "tangential_force_left" << ","
            << "tangential_force_right" << ","
            << "radial_force_left" << ","
            << "radial_force_right" << ","
            << "heart rate" << ","
            << "pedal_cadence_left" << ","
            << "pedal_cadence_right" << ","
            << "pedal_angle_left" << ","
            << "pedal_angle_right" << ","
            << "pedal_time_left" << ","
            << "pedal_time_right" << endl;

    }
}
void writeFile(){
    clock_gettime ( CLOCK_MONOTONIC, &timeLoop);

    CSVfile << endl
            << ( timeStructToMs(timeLoop)-timeStructToMs(timeStartThread) ) << ","
            << ( timeStructTons(timeLoop)-timeStructTons(timeStartThread) ) << ","
            << angle << ","
            << cadence << ","
            << pidCoefficient << ","
            << actualCurrentsL[0] << ","
            << actualCurrentsL[1] << ","
            << actualCurrentsL[2] << ","
            << actualCurrentsL[3] << ","
            << actualCurrentsR[0] << ","
            << actualCurrentsR[1] << ","
            << actualCurrentsR[2] << ","
            << actualCurrentsR[3] << ","
            << POL << ","
            << POR << ","
            << TgL << ","
            << TgR << ","
            << RadL << ","
            << RadR << ","
            << HR << ","
            << cad_ped_left << ","
            << cad_ped_right << ","
            << angle_ped_left << ","
            << angle_ped_right << ","
            << time_ped_left << ","
            << time_ped_right ;



    }



void open_fesbike_file(){
    // Get system  time
    time_t t = time(nullptr);
    struct tm * now = localtime( & t );
    char buffer [80];

    // Log directory
    strftime (buffer,80,"/home/pi/Desktop/btle_fede/files/NEWAcquiredData-%Y-%m-%d-%H-%M-%S.csv",now);
//    CSVfile2.open ("/home/pi/Desktop/btle_fede/files/AcquiredData-" + app2.pilot_name );

    CSVfile2.open (buffer);
    if(CSVfile2.is_open()){

        CSVfile2 << endl

                << "time" << ","
                << "time ns" << ","
                << "angle" << ","
                << "cadence" << ","
                << "pid" << ","
                << "pid_button" << ","
                << "corrente effettiva Quad Sx" << ","
                << "corrente effettiva Glut Sx" << ","
                << "corrente effettiva Hams Sx" << ","
                << "corrente effettiva Gastro Sx" << ","
                << "corrente effettiva Quad Dx" << ","
                << "corrente effettiva Glut Dx" << ","
                << "corrente effettiva Hams Dx" << ","
                << "corrente effettiva Gastro Dx" << ","
                << "power_output_left" << ","
                << "power_output_right" << ","
                << "tangential_force_left" << ","
                << "tangential_force_right" << ","
                << "radial_force_left" << ","
                << "radial_force_right" << ","
                << "heart rate" << ","
                << "pedal_cadence_left" << ","
                << "pedal_cadence_right" << ","
                << "pedal_angle_left" << ","
                << "pedal_cadence_right" << ","
                << "pedal_time_left" << ","
                << "pedal_time_right" << endl;

    }
}

void write_fesbike_file(){
    clock_gettime ( CLOCK_MONOTONIC, &timeLoop);

    CSVfile2 << endl
               //            << ( timeStructToMs(timeLoop)-timeStructToMs(timeStartThread) ) << ","
               //            << ( timeStructTons(timeLoop)-timeStructTons(timeStartThread) ) << ","
            << app2.count << ","
            << app2.count/1000 << ","
            << angle << ","
            << cadence << ","
            << pidCoefficient << ","
            << old_pid_from_gui << ","
            << actualCurrentsL[0] << ","
            << actualCurrentsL[1] << ","
            << actualCurrentsL[2] << ","
            << actualCurrentsL[3] << ","
            << actualCurrentsR[0] << ","
            << actualCurrentsR[1] << ","
            << actualCurrentsR[2] << ","
            << actualCurrentsR[3] << ","
            << POL << ","
            << POR << ","
            << TgL << ","
            << TgR << ","
            << RadL << ","
            << RadR << ","
            << HR << ","
            << cad_ped_left << ","
            << cad_ped_right << ","
            << angle_ped_left << ","
            << angle_ped_right << ","
            << time_ped_left << ","
            << time_ped_right ;

}

void writeBLE(){

    BLEfileL << "\nAcquisition " << endl;
    BLEfileR << "\nAcquisition " << endl;
    BLEfileL.close();
    BLEfileR.close();

}

void stopBLE(){

    std::ofstream BLEfileL ("/home/pi/TrikeStimulation/pol", std::ios_base::app | std::ios_base::out);
    BLEfileL <<"\nStop";
    std::ofstream BLEfileR ("/home/pi/TrikeStimulation/por", std::ios_base::app | std::ios_base::out);
    BLEfileR <<"\nStop";

}
