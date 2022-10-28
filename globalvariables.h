#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

#include "header.h"

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

using namespace std;
extern int error_angle ;
extern char nome_char_fes;
extern const std::string nomino2;
extern double targetCadence;
extern double target_cadence_new;
extern float CadenceOld;

extern bool flag_c;

extern int mainF;
extern int stimF;
extern int mainT;
extern double pidT;
extern int stimT;
extern vector<int> waveCoeff;
extern int stimF_D;
extern int stimF_ID;
extern int stimT_D;
extern int stimT_ID;

extern vector<double> initialCurrents;
extern vector<double> finalCurrents;
extern vector<double> initialRanges_left;
extern vector<double> initialRanges_right;
extern vector<double> marginiL;
extern vector<double> marginiR;
extern vector<double> maxCurrL;
extern vector<double> maxCurrR;

extern double currentIncrement;

extern uint8_t number_of_points; // 1-16

extern double PulseWidth;

extern double maxCurrentL;
extern double maxCurrentR;

extern int selected_frontGear;
extern int selected_backGear;

extern vector<int> frontGears;
extern vector<int> backGears;

extern float circumference;

extern float angle;
extern double HR;
extern float angleOld;
extern float cadence;
extern float old_cadence;
extern float del;

extern bool ginosu;
extern bool ginogiu;
extern bool ginosu_old;
extern bool ginogiu_old;

extern bool guibutton_start;
extern bool guibutton_start_old;
extern bool guibutton_stop;
extern bool guibutton_pause;
extern bool guibutton_pid;
extern bool guibutton_up ;
extern bool guibutton_down ;
extern bool up_fromgui_old;
extern bool down_fromgui_old;
extern int target_cadence_old;
extern int old_pid_from_gui;

extern bool uppi ;
extern bool downi ;

// Pedals extern values
extern double POL;
extern double POR;
extern double mean_POR;
extern double mean_POL;
extern double TgL;
extern double TgR;
extern double RadL;
extern double RadR;
extern double percPOR;
extern double percPOL;
extern double smoothR;
extern double smoothL;
extern double effL;
extern double effR;


extern double fsx_med;
extern double fdx_med;

extern double angle_ped_left;
extern double angle_ped_right;
extern float time_ped_left;
extern float time_ped_right;
extern double cad_ped_right;
extern double cad_ped_left;
extern double max_current_value;


// GUI external variables
extern int mod;
extern int sup2;
extern int sup;
extern bool input_running;
extern bool supp_flag;
extern int Init_saturation_current;
extern int Init_pulse_width;
extern int Init_target_cadence;
extern int flag_save;
extern int flag_save_old;


extern int stim_calib;
extern int curr_calib;
extern int pw_calib;
extern int channel_calib;
extern int nome;


extern vector<double> theoreticalCurrentsL;
extern vector<double> theoreticalCurrentsR;



extern vector<double> actualCurrentsL;
extern vector<double> actualCurrentsR;
extern vector<bool> modulateON;
extern double pidCoefficient;

// PID parameters
extern double kp;
extern double kd;
extern double ki;

extern ofstream CSVfile;
extern ofstream CSVfile2;
extern struct timespec timeStartThread;
extern struct timespec timeLoop;

extern bool thread_running;

extern bool flag_cicle_ble_right;
extern double mean_force_left ;
extern double mean_force_right;
extern double simsx ;
extern double simdx ;
extern double coeff_symm;

long timeStructToMs(timespec t);

timespec addition(timespec a, timespec b);

void interface(vector<double> &initC,  vector<double> &initR_left, vector<double> &initR_right);

// void configure(vector<double> &initC,  vector<double> &initR_left, vector<double> &initR_right);
void configure(vector<double> &initC,  vector<double> &initR_left, vector<double> &initR_right);
void OpenFile();

void writeFile();
void write_fesbike_file();
void open_fesbike_file();
void writeBLE();
void stopBLE();

class global{

public:
    void ReadFromSharedMemory();


};


#endif // GLOBALVARIABLES_H
