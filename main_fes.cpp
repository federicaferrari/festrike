


// HEADERS
#include "pid.h"
#include "chart.h"
#include "cadenceblock.h"
#include "globalvariables.h"
#include "stimulator.h"
#include "header.h"
#include "temp2.h"
#include "shared_memory.h"




#define DEFAULT_LOOP_TIME_NS 1000000L
#define DEFAULT_BUTTON_PRESSED_PAUSE_S 1
#define DEFAULT_BUTTON_PRESSED_PAUSE_NS 0

// VARIABLES
bool check_open1;
bool check_open2;

vector<double> L_Leg(4);
vector<double> R_Leg(4);
vector<double> L_Leg_f(4);
vector<double> R_Leg_f(4);
vector<double> L_Leg_old = {0.0, 0.0, 0.0, 0.0};
vector<double> R_Leg_old = {0.0, 0.0, 0.0, 0.0};

vector<double> iniRangesL(4);
vector<double> finRangesL(4);
vector<double> iniRangesR(4);
vector<double> finRangesR(4);

double PW = 0;
bool PI_start = 1;
bool running = 0;

vector<double> currentCoefficientsL(4);
vector<double> currentCoefficientsR(4);


vector<double> stim_pulseWL(4);
vector<double> stim_pulseWR (4);

vector<double> stim_pulseWL_new = {400.0, 400.0, 400.0, 400.0};
vector<double> stim_pulseWR_new = {400.0, 400.0, 400.0, 400.0};

vector<double> stim_pulseWL_burst = {200.0, 200.0, 200.0, 200.0};
vector<double> stim_pulseWR_burst = {200.0, 200.0, 200.0, 200.0};


// ENCODER
static const char *device = "/dev/spidev0.0";// /dev/spidev0.0 or /dev/spidev0.1
static uint8_t mode = 1;			// SPI_MODE_1
static uint8_t bits = 8;			// 8 or 9
static uint32_t speed = 1000000;	// Clock frequency [Hz]
static uint16_t delayEncoder = 0;			// Time between end of data and CS de-assert

// understand how to handle buttons
// BUTTONS
bool switch_on = 1;
bool switch_pid = 0;
bool switch_currentUp = 0;
bool switch_currentDown = 0;
bool switch_emergency=0;

// BOOLEANS related to buttons state
bool stop_pressed;
// *** perchè non è inizializzato pure lui *** //
bool start_pressed=1;



float anglevect[300]={0,2.06360561917019,3.39151377249985,4.58571090707987,5.69567003150714,6.98065399484383,8.03637028922807,9.23649058158414,10.4555120815266,11.7700269115044,12.8680789494183,14.0962810114979,15.2054050890472,16.4702017014575,17.6399338849295,18.9092404582546,20.1135216992433,21.2349372409196,22.5833060370282,23.7733657984786,24.9653222773762,26.1218124395353,27.2337240514322,28.4393271216795,29.787905764166,30.9201484458773,32.0946248338983,33.3166401064138,34.4686280218053,35.674405328162,36.9416031840077,38.1136697659502,39.3969025748728,40.4031872551242,41.7665663180171,42.9787567310143,44.1255180519889,45.3603763194914,46.5020624723968,47.7321013173218,48.8096739070445,50.0159335920327,51.3894646004638,52.4524283808966,53.7461761147203,54.9154328769982,56.090425819757,57.2114526031446,58.5164511791367,59.603389506706,60.9397090102576,62.0597802488198,63.2667322296831,64.4921747069914,65.6603788959639,66.8666944173195,68.1643735091199,69.374397120056,70.4001839210477,71.7657757867287,72.9934798358939,74.0877600414581,75.2236266999096,76.4661649390931,77.761913346564,78.9262166907872,80.1078548125479,81.2036724098058,82.5687190095547,83.6288954388308,84.871047092626,86.1247455579442,87.3618152609527,88.5143494014041,89.7035955877936,90.9758776773406,92.082098503061,93.3547624640495,94.5230761751261,95.6834027234505,96.9496387755055,98.1419118671446,99.2765818231213,100.546943818038,101.635124746662,102.803467320056,104.053950241546,105.331224599177,106.483186133344,107.778446196951,108.81873836987,110.024069255104,111.236447888126,112.547854400189,113.681128749867,114.995497481452,116.114948135957,117.337456222636,118.567703051138,119.76424676265,120.91542286218,122.181154132222,123.280295266249,124.505815148728,125.66081013734,126.860022430014,128.072293848346,129.393279232787,130.586238780176,131.736080052964,132.893827143861,134.069110858449,135.318476160592,136.436003755444,137.656328211359,138.806270133954,140.093733218687,141.334970863636,142.578874159334,143.677808268251,144.844239551635,146.115309416207,147.381835342843,148.546705701844,149.769268656482,150.943798939493,152.1119829722,153.294571451648,154.508515126862,155.624925680279,156.896389578328,158.01127547509,159.272458180386,160.408461212032,161.751858592904,162.864775539227,164.142187085665,165.265638366917,166.46097190009,167.786401446306,168.949041968681,170.155191993835,171.266433454597,172.431121568695,173.73110751774,174.843896069454,176.064933586851,177.398656937136,178.479565902484,179.722645761096,180.816801751174,182.199769788574,183.307510168152,184.515130192037,185.707816726794,186.845968054278,188.135505638563,189.243052141048,190.505728569258,191.792847453346,192.964825116863,194.055648393322,195.305302801407,196.569455759912,197.73177507859,198.878522157246,200.161650948908,201.252314632005,202.551430080336,203.61651513159,204.946187682663,206.046899996676,207.362267604642,208.542500365387,209.781777307263,210.884758123867,212.063327351341,213.290681377082,214.514854231626,215.671111443714,216.870476473965,218.064196649181,219.272842657897,220.410965177378,221.758213015515,222.858143659458,224.152753884601,225.376120750441,226.478539211863,227.709972460607,228.90825490127,230.067611049619,231.245942897039,232.529956397312,233.667598080328,234.916768282006,236.031614169462,237.233416636185,238.548711801554,239.677307852637,240.883550167095,242.091852132575,243.226011793528,244.547044194705,245.736385184904,246.976157091789,248.012034105931,249.270889625006,250.50410735501,251.672136607792,252.891056777895,254.070537703941,255.2912228132,256.455790675884,257.695500938845,258.801259075176,260.15626467352,261.37884034535,262.578060507095,263.787281725805,264.919084000828,266.110325417587,267.326836764632,268.44729907183,269.674420724077,270.845603922889,272.013429285944,273.205451829199,274.561594330114,275.772225159434,276.860746732583,278.181235994645,279.294919119228,280.493931156321,281.627772037721,282.90302933329,284.121308727757,285.265713772065,286.451748411309,287.695989506522,288.930457465744,290.170000549234,291.282781586554,292.547570936454,293.791109181544,294.849013346554,296.151442928436,297.3115195374,298.462440782976,299.72815435792,300.85273198514,302.121058504944,303.263316826606,304.459190513933,305.711538917323,306.996084475289,308.133828423957,309.315138100633,310.545945915314,311.760589240381,312.835655763008,314.114015718123,315.222445809149,316.521763400908,317.646177122522,318.920641696597,320.038297180822,321.248984580199,322.524520891033,323.756796216808,324.841918556407,326.01013921763,327.334486913185,328.46574712591,329.712271003483,330.833299880882,332.046229149514,333.366549290901,334.42760390426,335.602025569274,336.897115308699,338.023143795375,339.282394788938,340.569049530269,341.760027435429,342.918609032572,344.050258856357,345.234883236843,346.442007394011,347.73629515092,348.893187174526,350.182009864246,351.377658851161,352.572741490212,353.66426953904,354.900964596182,356.162057918796,357.300998835002,358.570478355605,359.789005170619};
int ii;
int jj;

chart chartclass;
temp2 temp2_thread;

stimulator stimulator1;
stimulator stimulator2;

float linearVelocity; // Km/h
double distanceTravelled = 0.0; // Km

//double deltaTkiller = (double) mainT/1000;8
//double deltaT=0.005;
double deltaT= 1/((double)mainF);


PID pid = PID(deltaT, 1, -1, kp, kd, ki);


std::unique_ptr<PID> pidPointer;
std::unique_ptr<chart> chartPointer;
//std::unique_ptr<Encoder> encoderPointer;
std::unique_ptr<cadenceBlock> cadencePointer;
std::unique_ptr<stimulator> stimPointer;


int secondi_d=0;
int secondi_u=0;
int minuti_d=0;
int minuti_u=0;

int sat_sec_d=0;
int sat_sec_u=0;
int sat_min_d=0;
int sat_min_u=0;
vector <double> pidvalue(5);
vector <double> cadvalue(5);

double sum_old=0.0;


float filt_cadence = 0.0;
float filtcadence_old = 0.0;


#include "thread_app.h"
#include "thread_class.h"


static void exit_on_error (const char *s)	// Exit and print error code
{ 	perror(s);
    abort();
}
float readError () {
    int fd;
    uint32_t Buffer_size;

    uint8_t tx[] = {0x01, 0x02, 0x03, 0x04, 0x05, };	// Data to send
    Buffer_size = sizeof(tx);		// Size of TX (and RX) buffer
    uint8_t rx[sizeof(tx)] = {0, };    	// RX buffer

    struct spi_ioc_transfer tr =
    {
        .tx_buf = (unsigned long)tx,
        .rx_buf = (unsigned long)rx,
        .len = Buffer_size,
        .speed_hz = speed,
        .delay_usecs = delayEncoder,
        .bits_per_word = bits,
        .cs_change = 0,
    };

    // Open SPI device
    if ((fd = open(device, O_RDWR)) < 0) exit_on_error ("Can't open SPI device");

    // Set SPI mode
    if (ioctl(fd, SPI_IOC_WR_MODE, &mode) == -1) exit_on_error ("Can't set SPI mode");

    // Read and write data (full duplex)
    if (ioctl(fd, SPI_IOC_MESSAGE(1), &tr) < 1) exit_on_error ("Can't send SPI message");

//    printf ("Data from SPI Rx buffer: ");
//    for (int i = 0; i < Buffer_size; i++) printf("%.2X ", rx[i]);
//    printf ("\n");
    int angleb = (rx[0]<<8 | rx[1]);
//        printf("%X", angleb);
//        printf("\n");
    int anglei = uint(angleb);
//        printf("%d",anglei);
//        printf("\n");
    float angleEncoder = (anglei/65536.0)*360.0;
    // printf("%f", angle);
//    printf ("\n");

    error_angle= uint(rx[3]) & 0x08;

    close(fd);

    return error_angle;

}
float readAngle () {
    int fd;
    uint32_t Buffer_size;

    uint8_t tx[] = {0x01, 0x02, 0x03, 0x04, 0x05, };	// Data to send
    Buffer_size = sizeof(tx);		// Size of TX (and RX) buffer
    uint8_t rx[sizeof(tx)] = {0, };    	// RX buffer

    struct spi_ioc_transfer tr =
    {
        .tx_buf = (unsigned long)tx,
        .rx_buf = (unsigned long)rx,
        .len = Buffer_size,
        .speed_hz = speed,
        .delay_usecs = delayEncoder,
        .bits_per_word = bits,
        .cs_change = 0,
    };

    // Open SPI device
    if ((fd = open(device, O_RDWR)) < 0) exit_on_error ("Can't open SPI device");

    // Set SPI mode
    if (ioctl(fd, SPI_IOC_WR_MODE, &mode) == -1) exit_on_error ("Can't set SPI mode");

    // Read and write data (full duplex)
    if (ioctl(fd, SPI_IOC_MESSAGE(1), &tr) < 1) exit_on_error ("Can't send SPI message");

//    printf ("Data from SPI Rx buffer: ");
//    for (int i = 0; i < Buffer_size; i++) printf("%.2X ", rx[i]);
//    printf ("\n");
    int angleb = (rx[0]<<8 | rx[1]);
//        printf("%X", angleb);
//        printf("\n");
    int anglei = uint(angleb);
//        printf("%d",anglei);
//        printf("\n");
    float angleEncoder = (anglei/65536.0)*360.0;
    // printf("%f", angle);
//    printf ("\n");

    error_angle= uint(rx[3]) & 0x08;

    close(fd);

    return angleEncoder;

}
shared_memory shmem;
global glob;
thread_app app;

void myInterruptHandler (int signum) {

    printf ("ctrl-c has been pressed. Programs will be terminated in sequence.\n");
    thread_running = 0;
    running = 0;
    CSVfile.close();
    shmem.detach_shared_memory();
    stopBLE();

}


thread_class tclass;


void configure_from_sharedmemory(vector<double> &initC,  vector<double> &finC, vector<double> &initR_left, vector<double> &initR_right) {
    for (int i=0; i<8; i++){

        initC[i]=shmem.data->correnti_iniziali[i];
        finC[i]=shmem.data->correnti_finali[i];
        initR_left[i]=shmem.data->range_iniziali_sx[i];
        initR_right[i]=shmem.data->range_iniziali_dx[i];
    }

    cout << "\nInitial currents are: " << initC[0] << " " << initC[1] << " " << initC[2] << " " << initC[3] << " " << initC[4] << " " << initC[5] << " " << initC[6] << " " << initC[7] << endl;
    cout << "\nFinal currents are: " << finC[0] << " " << finC[1] << " " << finC[2] << " " << finC[3] << " " << finC[4] << " " << finC[5] << " " << finC[6] << " " << finC[7] << endl;



    cout << "\nInitial ranges left are: " << initR_left[0] << " " << initR_left[1] << " " << initR_left[2] << " " << initR_left[3] << " " << initR_left[4] << " " << initR_left[5] << " " << initR_left[6] << " " << initR_left[7] << endl;
    cout << "\nInitial ranges right are: " << initR_right[0] << " " << initR_right[1] << " " << initR_right[2] << " " << initR_right[3] << " " << initR_right[4] << " " << initR_right[5] << " " << initR_right[6] << " " << initR_right[7] << endl;

}

void readfromSM(){

   input_running = shmem.data->input_running;
   thread_running = shmem.data->thread_running;

}

int wait_count = 0;
int wait_count_pid = 0;
int wait_count_2 = 0;
int wait_count_2pid = 0;
int wait_count_3 = 0;



// Configure initial currents and initial ranges
vector<double> initcurr(8);
vector<double> fincurr(8);
vector<double> initrangR(8);
vector<double> initrangL(8);


void thread_app::loop(){

    // Everything here runs at 1kHz

    if(change_mode==0 && flag_save==3){
//        OpenFile();
        change_mode = 1;
    }


    // Read from shared memory
//    pilot_name = shmem.data->file_name;
    int stimulator_calib = shmem.data->stimulator_calibration;
    stim_calib = static_cast<int>(stimulator_calib);
    int canale = shmem.data->channel_calibration;
    channel_calib=static_cast<int>(canale);
    int pw = shmem.data->pulsewidth_calibration;
    pw_calib=static_cast<int>(pw);
    int current_calib = shmem.data->current_calibration;
    curr_calib=static_cast<int>(current_calib);
    bool flag_cal = shmem.data->flag_calibrate;
    flag_c = flag_cal;

    bool uppiuppi = shmem.data->up;
    uppi = uppiuppi;
    bool downidowni = shmem.data->down;
    downi = downidowni;

    // Force values
    bool flag_cicle_ble_right_supp = shmem.data->flag_ciclo_right;
    flag_cicle_ble_right = flag_cicle_ble_right_supp;
    bool mean_force_right_supp = shmem.data->tfmedia_right;
    mean_force_right=mean_force_right_supp;
    bool mean_force_left_supp = shmem.data->tfmedia_left;
    mean_force_left=mean_force_left_supp;


    // **************************************************************************************************
    // *********** CALIBRATION **************************************************************************
    // **************************************************************************************************


    // If in the calibration phase stimulate the desired channel at a given intensity
    if(flag_c==1){
        if (count%1000==0){
            cout << "Calibration running" << endl;
        }

        if(stim_calib==1){

            // Calibrazione con frequenza costante
            if(count%stimT == 0) {
                stimPointer->stimulation_calibration(stimulator1, channel_calib,  curr_calib, pw_calib);
                cout << "sto stimolando sul 1" << endl;
            }


            // Prova calibrazione con doublets
//            if(count%stimT_D==0 || count%stimT_D == stimT_ID) {
//                stimPointer->stimulation_calibration(stimulator1, channel_calib,  curr_calib, pw_calib);
//                cout << "sto stimolando sul 1" << endl;

            // Prova calibrazione con bursts
//             if(count%stimT_D == 0 || count%stimT == 3 || count%stimT == 6 || count%stimT == 9 || count%stimT == 12) {
//              stimPointer->stimulation_calibration(stimulator1, channel_calib,  curr_calib, 200);
//             }
//            }
        }

        else if(stim_calib==2){
            if(count%stimT == 0) {
                stimPointer->stimulation_calibration(stimulator2, channel_calib,  curr_calib, pw_calib);
                cout << "sto stimolando sul 2" << endl;
            }
        }
    }



     int supp2 = shmem.data->supp_flag_sh;
     sup2 = supp2;
     int flag = shmem.data->flag_save;
     flag_save = flag;
     flag_save_old=flag_save;


     // Keep the values set in the GUI to run the program
     if(flag_save==3){

         for (int i=0; i<8; i++){

             initcurr[i]=shmem.data->correnti_iniziali[i];
             fincurr[i]=shmem.data->correnti_finali[i];
             initrangL[i]=shmem.data->range_iniziali_sx[i];
             initrangR[i]=shmem.data->range_iniziali_dx[i];
         }



         for (int i=0; i<8; i++){

             initialCurrents[i]=initcurr[i];
             finalCurrents[i]=fincurr[i];
             initialRanges_left[i]=initrangL[i];
             initialRanges_right[i]=initrangR[i];
         }

         for (int i=0; i<4; i++){

             marginiL[i]=finalCurrents[i]-initialCurrents[i];
             marginiR[i]=finalCurrents[i+4]-initialCurrents[i+4];
             maxCurrL[i]=finalCurrents[i];
             maxCurrR[i]=finalCurrents[i+4];
         }

         cout << "\nBBBBBBBBBB"<<endl;
         cout << "\nInitial currents are: " << initialCurrents[0] << " " << initialCurrents[1] << " " << initialCurrents[2] << " " << initialCurrents[3] << " " << initialCurrents[4] << " " << initialCurrents[5] << " " << initialCurrents[6] << " " << initialCurrents[7] << endl;
         cout << "\nInitial currents are: " << finalCurrents[0] << " " << finalCurrents[1] << " " << initialCurrents[2] << " " << finalCurrents[3] << " " << finalCurrents[4] << " " << finalCurrents[5] << " " << finalCurrents[6] << " " << finalCurrents[7] << endl;

         cout << "\nInitial ranges left are: " << initialRanges_left[0] << " " << initialRanges_left[1] << " " << initialRanges_left[2] << " " << initialRanges_left[3] << " " << initialRanges_left[4] << " " << initialRanges_left[5] << " " << initialRanges_left[6] << " " << initialRanges_left[7] << endl;
         cout << "\nInitial ranges right are: " << initialRanges_right[0] << " " << initialRanges_right[1] << " " << initialRanges_right[2] << " " << initialRanges_right[3] << " " << initialRanges_right[4] << " " << initialRanges_right[5] << " " << initialRanges_right[6] << " " << initialRanges_right[7] << endl;

         cout << "\nMargins left are: " << marginiL[0] << " " << marginiL[1] << " " << marginiL[2] << " " << marginiL[3] << endl;
         cout << "\nMargins right are: " << marginiR[0] << " " << marginiR[1] << " " << marginiR[2] << " " << marginiR[3] << endl;


        chartPointer->initialization_Function(L_Leg, R_Leg,  L_Leg_f, R_Leg_f, iniRangesL, finRangesL, iniRangesR, finRangesR, PulseWidth, PW, PI_start);


         // Configure values in input from gui
         int modality = shmem.data->modality_from_gui;
         mod = modality;
         int Init_sat_current = shmem.data->saturation_current_from_gui;
         Init_saturation_current = static_cast<int>(Init_sat_current);
         int Init_pw=shmem.data->pulse_width_from_gui;
         Init_pulse_width = static_cast<int>(Init_pw);
         int Init_trg_cadence = shmem.data->target_cadence_from_gui;
         Init_target_cadence = static_cast<int>(Init_trg_cadence);
         target_cadence_new=Init_target_cadence;

         for (int i =0;i<4;i++) {
             stim_pulseWL[i]=Init_pulse_width;
             stim_pulseWR[i]=Init_pulse_width;
         }

         open_fesbike_file();
         flag_save=0;
         shmem.data->flag_save=flag_save;


         cout << "initialized variables locali" << endl;
         cout << "modality  " << mod;
         cout << "sat current  " << dec << static_cast<int>(Init_saturation_current) << hex ;
         cout << "PW  " << dec << static_cast<int>(Init_pulse_width) << hex;
         cout << "Init trg cadence" << dec << static_cast<int>(Init_target_cadence) << hex;

     }


//     error_angle=readError();
//     int angle_dummy = readAngle();

//     if(error_angle==0){
//         angle = angle_dummy ;
//     }
//     else angle=angleOld;

     angle = readAngle();

     angleOld = angle;
     shmem.data->angle_encoder=angle;

     // FILTERED CADENCE
     old_cadence = cadencePointer->computeCadence(angleOld, angle);
     filt_cadence = cadencePointer->filterCadence(static_cast<double>(old_cadence),static_cast<double>(filtcadence_old));
     if(filt_cadence<100){
         cadence=filt_cadence; filtcadence_old=cadence;
     }
    // else cadence=filtcadence_old;
     else cadence=0;

     //NORMAL CADENCE
    //     cadence = cadencePointer->computeCadence(angleOld, angle, CadenceOld);
    //     CadenceOld=cadence;
     shmem.data->current_cadence = cadence;


     // Read GUI Buttons from shared memory
     bool start_fromgui = shmem.data->start_training;
     bool stop_fromgui = shmem.data->stop_training;
     bool pause_fromgui = shmem.data->pause_training;
     bool pid_fromgui = shmem.data->pid;
     bool up_fromgui = shmem.data->up;
     bool down_fromgui = shmem.data->down;

     // Assign value from sm to a local variable
     guibutton_start = start_fromgui;
     guibutton_stop  = stop_fromgui;
     guibutton_pause = pause_fromgui;
     guibutton_pid = pid_fromgui;
     guibutton_up = up_fromgui;
     guibutton_down = down_fromgui;


     // ***************** START STIMULATION LOOP ******************************************************************

     // When the AVVIA button is pressed in the GUI the program starts to run and stimulation is ON

     if(stop_fromgui==1){

         // TODO: do not stimulate!!!

     }

     // **********************************************************************************************
     // *********** BUTTONS **************************************************************************
     // **********************************************************************************************

     // Check if the button is pressed and update the booleans

    chartclass.readButton();


    // Handle buttons
    // START BUTTON

    // Press the button for at least 2 seconds
//    if(chartclass.buttons[3]==1){
//        // Start button has been pressed once
//            if(guibutton_start==0){
//                // Activate Stimulation LOOP
//                guibutton_start=1;
//            }
//            else if(guibutton_start==1){
//                // Dectivate Stimulation LOOP
//                guibutton_start=0;
//            }
//    }

    // Write to shared memory
      shmem.data->start_training=guibutton_start;



    // PID BUTTON
//    if(chartclass.buttons[1]==1 && chartclass.old_buttons[1]==0){
//        // PID button has been pressed once

//        if(chartclass.pid_frombuttons==0){
//            // Activate PID
//            chartclass.pid_frombuttons=1;
//        }
//        else if(chartclass.pid_frombuttons==1){
//            // Dectivate PID
//            chartclass.pid_frombuttons=0;
//        }

//        if(pid_fromgui==0){
//            // Activate PID
//            pid_fromgui=1;

//        }
//        else if(pid_fromgui==1){
//            // Dectivate PID
//            pid_fromgui=0;

//        }
//      }

// Punto d partenza 13/06
//    if(chartclass.buttons[0]==0 && chartclass.old_buttons[0]==1){
//        // UP button has been pressed
//        guibutton_up=1;
//        wait_count ++;

//    }
//    if(wait_count==1){ ginosu=1;
//    }
//    else {
//        ginosu=0;
//    }
//    if(wait_count>1000){wait_count=0; }

    // Prove buttons
//        if(chartclass.buttons[0]==0 && chartclass.old_buttons[0]==1){

//            // Up button has been pressed
//                if(uppi==0){
//                    // Decrease quantity
//                    uppi=1;
//                }


//        }


// Prove buttons

      // BIANCO ALZO CORRENTE/CADENCE
      // BLU DIMINUISCO CORRENTE/CADENCE

    if(chartclass.buttons[3]==1 && chartclass.old_buttons[3]==0){
        // Down button has been pressed
            if(downi==0){
                // Decrease quantity
                downi=1;
            }
    }

    if(chartclass.buttons[2]==1 && chartclass.old_buttons[2]==0){

            if(uppi==0){

                uppi=1;
            }

    }



    ginogiu_old = ginogiu;
    ginosu_old = ginosu;




       if(guibutton_start==1 ){

         if(count%mainT == 0) { // repeats every 5ms -> 200 Hz

             // Everything here runs at 200Hz
             linearVelocity = (frontGears[selected_frontGear]/backGears[selected_backGear]) * cadence * circumference; // velocity as m/min
             linearVelocity = linearVelocity * (60.0/1000.0); // velocity as km/h


             // linearVelocity is = (Front/Back) * cadence * circumference * (60/1000)
             // distanceTravelled is = (Front/Back) * deltaAngle * circumference * 1/(360*1000)
             // as deltaAngle = (cadence * 360)/(freq * 60) -> distanceTravelled = (Front/Back) * cadence/(freq * 60) circumference/1000
             // we derive distanceTravelled = linearVelocity/(freq * 60 * 60) = linearVelocity/(freq * 3600)
             distanceTravelled =  distanceTravelled + linearVelocity/( ((double)mainF) * 3600);
             del = cadencePointer->computeDelay(cadence);


             if(cadence > -5)
             {
                 chartPointer->computeCoefficients(angle, del, iniRangesL, finRangesL, iniRangesR, finRangesR, currentCoefficientsL, currentCoefficientsR);
                 PW = PulseWidth;
             }
             else
             {
                 currentCoefficientsL = {0.0, 0.0, 0.0, 0.0};
                 currentCoefficientsR = {0.0, 0.0, 0.0, 0.0};
                 PW = 0;
             }

             // TODO: add button within if



             if(pid_fromgui==1) {

                 if(pid_fromgui!=old_pid_from_gui ){
                     pidCoefficient=0.0;
                     pid._integral = 0;
                     pid._pre_error = 0;

                     //  Keep in memory the current value of current and pw
                     for (int i=0; i<4; i++){
                         L_Leg[i]=theoreticalCurrentsL[i];
                         R_Leg[i]=theoreticalCurrentsR[i];
                     }

//                     chartPointer->initialization_Function_switch(L_Leg, R_Leg, iniRangesL, finRangesL, iniRangesR, finRangesR, PulseWidth, PW, PI_start);

                 }

//                 pidCoefficient = pid.calculate(target_cadence_new, cadence);
                 pidCoefficient = pid.calcolopid(target_cadence_new, cadence);


//                 if(guibutton_up!=up_fromgui_old || ginosu==1){
//                     if(target_cadence_new+5<70){
//                         target_cadence_new=target_cadence_new+5;
//                      }
//                 }
//                 if(guibutton_up==1){
//                     if(target_cadence_new+5<70){
//                         target_cadence_new=target_cadence_new+5;
//                         cout<<" AAAAAAAAA premuto su"<<endl;
//                      }
//                      guibutton_up=0;
//                 }

//                 else if(guibutton_down==1){

//                     if(target_cadence_new-5>5){
//                         target_cadence_new=target_cadence_new-5;
//                         cout<<" AAAAAAAAA premuto giu"<<endl;


//                     }
//                     guibutton_down=0;
//                 }

                 if(uppi == 1){

                     cout << "ho premuto uppi " << endl;
                     if(target_cadence_new+5<90){
                         target_cadence_new=target_cadence_new+5;
                      }
                     uppi = 0;
                 }

                 if(downi == 1){

                     cout << "ho premuto downi " << endl;
                     if(target_cadence_new-5>5){
                         target_cadence_new=target_cadence_new-5;
                     }
                     downi = 0;
                 }

                 for (int i=0; i<4; i++){
                     L_Leg_old[i]=actualCurrentsL[i];
                     R_Leg_old[i]=actualCurrentsR[i];
                 }

             }

//             shmem.data->down=guibutton_down;
//             shmem.data->up=guibutton_up;

             // If PID is inactive use buttons up/down to increase/decrease current
             // TODO: add button within if
             if(pid_fromgui==0) {
                 if(pid_fromgui!=old_pid_from_gui){
                     pidCoefficient=0;
                     //  TODO: keep in memory the current value of current and pw
                     for (int i=0; i<4; i++){
                         L_Leg[i]=theoreticalCurrentsL[i];
                         R_Leg[i]=theoreticalCurrentsL[i];
                     }

//                     chartPointer->initialization_Function_switch(L_Leg, R_Leg, iniRangesL, finRangesL, iniRangesR, finRangesR, PulseWidth, PW, PI_start);

                 }

                 pidCoefficient = 0.0;
                 // attivare pulsanti up e down per aumentare/diminuire corrente
                 if(uppi==1){




//                     for(int i=0; i<4; i++) {
//                         if (theoreticalCurrentsR[i] + 5 <= Init_saturation_current)
//                             R_Leg[i] = R_Leg[i] + 5;
//                         if (theoreticalCurrentsR[i] + currentIncrement <= Init_saturation_current)
//                             L_Leg[i] = L_Leg[i] + 5;
//                     }



                     // Prova limite per ciascun muscolo
                     for(int i=0; i<4; i++) {
                         if (theoreticalCurrentsR[i] + 5 <= fincurr[i+4])
                             R_Leg[i] = R_Leg[i] + 5;
                         if (theoreticalCurrentsL[i] + 5 <= fincurr[i])
                             L_Leg[i] = L_Leg[i] + 5;
                     }

                     uppi=0;

                 }

                 // TODO: add button within if
                 if(downi==1){
                     for(int i=0; i<4; i++) {
                      if (theoreticalCurrentsR[i] - 5 >= initcurr[i+4] ){
                         R_Leg[i] = R_Leg[i] - 5;}
                      if (theoreticalCurrentsL[i] - 5 >= initcurr[i]  ){
                         L_Leg[i] = L_Leg[i] - 5;}
                     }
                     downi=0;
                 }


                 for (int i=0; i<4; i++){
                     L_Leg_old[i]=actualCurrentsL[i];
                     R_Leg_old[i]=actualCurrentsR[i];
                 }
             }

             // Keep in memory variables from the previous cycle
             old_pid_from_gui = pid_fromgui;
             up_fromgui_old = guibutton_up;
             down_fromgui_old = guibutton_down;

             chartclass.old_buttons[0]=chartclass.buttons[0];
             chartclass.old_buttons[1]=chartclass.buttons[1];
             chartclass.old_buttons[2]=chartclass.buttons[2];
             chartclass.old_buttons[3]=chartclass.buttons[3];

//             for (int i=0; i<4; i++){
//                L_Leg_old[i]=actualCurrentsL[i];
//                R_Leg_old[i]=actualCurrentsR[i];
//             }

             // PRINT
             writeFile();
             write_fesbike_file();

         // ******************************** PROGRAMS *******************************************************************


         // FIXED FREQUENCY PULSES
         if(mod==1){
             if(count%1000==0){
                 cout << "Fixed Frequency mode" << endl;
                 cout << pidCoefficient << "," << L_Leg[1] << "," << currentCoefficientsL[1] << "," << theoreticalCurrentsL[1] << "," << actualCurrentsL[1] << "," << Init_saturation_current << "," << stim_pulseWL[1] << endl;
                 cout << "\nMargins left are: " << marginiL[0] << " " << marginiL[1] << " " << marginiL[2] << " " << marginiL[3] << endl;
                 cout << "\nMargins right are: " << marginiR[0] << " " << marginiR[1] << " " << marginiR[2] << " " << marginiR[3] << endl;


             }

//         coeff_simmetry1 =compute_simmetry_coefficients(fsx_med, fdx_med);
//         coeff_simmetry2=1-coeff_simmetry1;

//         cout<<"coeff1"<<coeff_simmetry1<<endl;
//         cout<<"coeff2"<<coeff_simmetry2<<endl;


             if(count%stimT == 0) { // repeats every stimT (25ms for 40Hz)
//                 stimPointer->stimulate(stimulator1, pidCoefficient, L_Leg, currentCoefficientsL, theoreticalCurrentsL, actualCurrentsL, Init_saturation_current, stim_pulseWL );
//                 stimPointer->stimulate(stimulator2, pidCoefficient, R_Leg, currentCoefficientsR, theoreticalCurrentsR, actualCurrentsR, Init_saturation_current, stim_pulseWR );
                 stimPointer->stimulatebiss(stimulator1, pidCoefficient, L_Leg, currentCoefficientsL, theoreticalCurrentsL, actualCurrentsL, marginiL, stim_pulseWL, maxCurrL );
                 stimPointer->stimulatebiss(stimulator2, pidCoefficient, R_Leg, currentCoefficientsR, theoreticalCurrentsR, actualCurrentsR, marginiR, stim_pulseWR, maxCurrR );
            }
         }

         if(mod==2){
             if(count%1000==0){
                 cout << "Burst mode" << endl;
             }

                         if(count%stimT_D == 0 || count%stimT == 3 || count%stimT == 6 || count%stimT == 9 || count%stimT == 12) { // repeats every stimT (25ms for 40Hz)
                             stimPointer->stimulate(stimulator1, pidCoefficient, L_Leg, currentCoefficientsL, theoreticalCurrentsL, actualCurrentsL, maxCurrentL, stim_pulseWL_burst);
                             stimPointer->stimulate(stimulator2, pidCoefficient, R_Leg, currentCoefficientsR, theoreticalCurrentsR, actualCurrentsR, maxCurrentR, stim_pulseWR_burst);

                         }

         }

         if(mod==3){
             if(count%1000==0){
                 cout << "Doublets mode" << endl;
             }
             //            // DOUBLETS FREQUENCY PULSES (check fatto)
                         if(count%stimT_D==0 || count%stimT_D == stimT_ID){
                             stimPointer->stimulate(stimulator1, pidCoefficient, L_Leg, currentCoefficientsL, theoreticalCurrentsL, actualCurrentsL, maxCurrentL, stim_pulseWL);
                             stimPointer->stimulate(stimulator2, pidCoefficient, R_Leg, currentCoefficientsR, theoreticalCurrentsR, actualCurrentsR, maxCurrentR, stim_pulseWR);
                         }
         }

         if(mod==4){
             // 200Hz
             // calcolo coefficiente di simmetria
             if(flag_cicle_ble_right==1){
                 // Solo qando il flag è = 1 significa che ha fatto 5 cicli e calcolato la media sui 5 cicli
                 // quindi aggiorno il coefficiente di simmetria solo ogni 5 cicli
                 coeff_symm = compute_simmetry_coefficients(mean_force_left, mean_force_right);
                 if(coeff_symm>0){
                     simsx=-coeff_symm/2;
                     simdx=coeff_symm/2;
                 }

                 if(coeff_symm<0){
                     simsx=coeff_symm/2;
                     simdx=-coeff_symm/2;
                 }
             }
             // stimolare con funzione che tiene in considerazione il coefficiente di simmetria
             if(count%stimT == 0) { // repeats every stimT (25ms for 40Hz)
                 void stimulatemitch(stimulator &stim, double pidCoef, vector<double> current_Leg, vector<double> current_coeff, vector<double> &current_theoretical, vector<double> &current_actual, vector<double> margini, vector<double> pulsewidthVector, vector<double> maxCurrents, double coeff_symm);


                 stimPointer->stimulatemitch(stimulator1, pidCoefficient, L_Leg, currentCoefficientsL, theoreticalCurrentsL, actualCurrentsL, marginiL, stim_pulseWL, maxCurrL, simsx, 0.8);
                 stimPointer->stimulatemitch(stimulator2, pidCoefficient, R_Leg, currentCoefficientsR, theoreticalCurrentsR, actualCurrentsR, marginiR, stim_pulseWR, maxCurrR, simdx, 0.8);

             }




         }

         // Read from shared memory
         bool angolo_pedali = shmem.data->angle_pedals;
         double angolo_pedali_sinistro = shmem.data->angle_pedals_left;
         double angolo_pedali_destro = shmem.data->angle_pedals_right;
         double hr=shmem.data->heart_rate;
         HR=hr;
         double po_left=shmem.data->power_left;
         POL=po_left;
         double po_right=shmem.data->power_right;
         POR=po_left;
         double mean_po_right=shmem.data->mean_power_right;
         mean_POR=mean_po_right;
         double mean_po_left=shmem.data->mean_power_left;
         mean_POL=mean_po_left;
         double tg_left=shmem.data->tangential_force_left;
         TgL=tg_left;
         double tg_right=shmem.data->tangential_force_right;
         TgR=tg_right;
         double rad_left=shmem.data->radial_force_left;
         RadL=rad_left;
         double rad_right=shmem.data->radial_force_right;
         RadR=rad_right;
         double perc_right=shmem.data->percentage_right;
         percPOR=perc_right;
         double perc_left=shmem.data->percentage_left;
         percPOL=perc_left;
         double smooth_left=shmem.data->pedal_smoothness_left;
         smoothL=smooth_left;
         double smooth_right=shmem.data->pedal_smoothness_right;
         smoothR=smooth_right;
         double eff_right=shmem.data->pedal_efficiency_right;
         effR=eff_right;
         double eff_left=shmem.data->pedal_efficiency_left;
         effL=eff_left;
         double pedal_cadence_left = shmem.data->cadence_pedal_left;
         cad_ped_left = pedal_cadence_left;
         double pedal_cadence_right = shmem.data->cadence_pedal_right;
         cad_ped_right = pedal_cadence_right;
         float time_pedal_left = shmem.data->time_pedal_left;
         time_ped_left = time_pedal_left;
         float time_pedal_right = shmem.data->time_pedal_right;
         time_ped_right = time_pedal_right;
         float angle_pedal_right = shmem.data->angle_pedals_right;
         angle_ped_right = angle_pedal_right;
         float angle_pedal_left = shmem.data->angle_pedals_left;
         angle_ped_left = angle_pedal_left;
//         double forza_sx_media = shmem.data->tfmedia_left;
//         fsx_med= forza_sx_media;
//         double forza_dx_media = shmem.data->tfmedia_right;
//         fdx_med= forza_dx_media;


         // Write to shared memory
         shmem.data->current_quadriceps_left=actualCurrentsL[0];
         shmem.data->current_quadriceps_right=actualCurrentsR[0];
         shmem.data->current_gluteus_left=actualCurrentsL[1];
         shmem.data->current_gluteus_right=actualCurrentsR[1];
         shmem.data->current_hamstring_left=actualCurrentsL[2];
         shmem.data->current_hamstring_right=actualCurrentsR[2];
         shmem.data->current_gastro_left=actualCurrentsL[3];
         shmem.data->current_gastro_right=actualCurrentsR[3];

//         shmem.data->current_quadriceps_left=theoreticalCurrentsL[0];
//         shmem.data->current_quadriceps_right=theoreticalCurrentsR[0];
//         shmem.data->current_gluteus_left=theoreticalCurrentsL[1];
//         shmem.data->current_gluteus_right=theoreticalCurrentsR[1];
//         shmem.data->current_hamstring_left=theoreticalCurrentsL[2];
//         shmem.data->current_hamstring_right=theoreticalCurrentsR[2];
//         shmem.data->current_gastro_left=theoreticalCurrentsL[3];
//         shmem.data->current_gastro_right=theoreticalCurrentsR[3];


         shmem.data->trg_cad=target_cadence_new;
         shmem.data->pid=pid_fromgui;

         shmem.data->up = uppi;

         shmem.data->down = downi;


        // *********************************************
        // Print on terminal & on GUI
        // *********************************************
         if(count%1000==0){
             // Everything here runs at 1Hz

             cout << "angle " << angle << endl;
//             cout << "angle dummy " << angle_dummy << endl;
             cout << "error angle" << error_angle << endl;
             cout << "angle old" << angleOld << endl;

//             cout << "********************************************************************************" << endl;
//             cout << "********************************************************************************" << endl;
             std::cout << "CURRENT             LEFT RIGHT " << endl;
             std::cout << "QUADRICEPS           "  <<actualCurrentsL[0] << "     " << actualCurrentsR[0] << endl;
             std::cout << "GLUTEUS              "   <<actualCurrentsL[1] << "     " << actualCurrentsR[1] << endl;
             std::cout << "HAMSTRINGS           "  <<actualCurrentsL[2] << "     " << actualCurrentsR[2] << endl;
             std::cout << "GASTRCNEMIOUS        "  <<actualCurrentsL[3] << "     " << actualCurrentsR[3] << endl;

             std::cout << "CURRENT             LEFT RIGHT " << endl;
             std::cout << "QUADRICEPS           "  <<theoreticalCurrentsL[0] << "     " << theoreticalCurrentsR[0] << endl;
             std::cout << "GLUTEUS              "   <<theoreticalCurrentsL[1] << "     " << theoreticalCurrentsR[1] << endl;
             std::cout << "HAMSTRINGS           "  <<theoreticalCurrentsL[2] << "     " << theoreticalCurrentsR[2] << endl;
             std::cout << "GASTRCNEMIOUS        "  <<theoreticalCurrentsL[3] << "     " << theoreticalCurrentsR[3] << endl;

             cout << "pid_coeff" << pidCoefficient << endl;

             cout << "initialized variables locali" << endl;
             cout << "modality  " << mod;
             cout << "sat current  " << dec << static_cast<int>(Init_saturation_current) << hex ;
             cout << "PW  " << dec << static_cast<int>(Init_pulse_width) << hex;
             cout << "Init trg cadence" << dec << static_cast<int>(Init_target_cadence) << hex;

//             cout << "MAIN CADENCE: " << cadence << endl;
//             cout << "CRANK ANGLE:" << angle << endl;
//             cout << "TARGET CADENCE: " << target_cadence_new << endl;
//             cout << "down: " << down_fromgui << endl;
//             cout << "up: " << up_fromgui << endl;
//             cout << "pid from gui" << pid_fromgui << endl;
//             cout << "start from gui/buttons" << guibutton_start << endl;
//             cout << "stop from gui" <<stop_fromgui << endl;
//             cout << "pause from gui" <<pause_fromgui << endl;
//             cout << "down from butt: " << chartclass.down_frombuttons << endl;
//             cout << "up from butt: " << chartclass.up_frombuttons  << endl;
//             cout << "pid from butt" << chartclass.pid_frombuttons  << endl;
//             cout << "flag save" << flag_save << endl;
//             cout<<wait_count<<"waitcount"<<endl;
             cout << "guibutton_up" << guibutton_up << endl;
             cout << "guibutton_down" << guibutton_down << endl;


                 cout << "GIALLO:   " << chartclass.buttons[0] << endl;
                 cout << "BIANCO:   " << chartclass.buttons[2] << endl;
                 cout << "VERDE:   "<< chartclass.buttons[1] << endl;
                 cout << "BLU:  " << chartclass.buttons[3] << endl;
                 cout << "++++++++++++++++++++++++++++" << endl;






//             cout << "" << endl;

             // Compute time to display
             secondi_u ++;
             if(secondi_u==10){
                 secondi_d ++;
                 secondi_u =0;
             }

             if(secondi_d==6){
                 minuti_u ++;
                 secondi_d =0;
             }

             if(minuti_u==10){
                 minuti_d ++;
                 minuti_u=0;
             }

//             cout << "ELAPSED TIME:" << minuti_d << minuti_u << ":" << secondi_d << secondi_u << endl;
//             cout << "********************************************************************************" << endl;

             shmem.data->sec_u=secondi_u;
             shmem.data->sec_d=secondi_d;
             shmem.data->min_u=minuti_u;
             shmem.data->min_d=minuti_d;

             double sum=0.0;

                 for (int q=0; q<pidvalue.size()-1; q++){
                     pidvalue.at(q)=pidvalue.at(q+1);
                       }
                 pidvalue.at(pidvalue.size()-1)=pidCoefficient;


             sum=accumulate(pidvalue.begin(),pidvalue.end(), 0.0);
             cout << "somma:" << sum << endl;
             if (sum==5.0){
                 sat_sec_u=secondi_u;
                 sat_sec_d=secondi_d;
                 sat_min_u=minuti_u;
                 sat_min_d=minuti_d;

            }

             if (sum_old<5 && sum==5.0){
                 shmem.data->saturation_sec_u=sat_sec_u;
                 shmem.data->saturation_sec_d=sat_sec_d;
                 shmem.data->saturation_min_u=sat_min_u;
                 shmem.data->saturation_min_d=sat_min_d;
            }

             sum_old=sum;

//             std::cout << " OLD CURRENT             LEFT RIGHT " << endl;
//             std::cout << "OLD QUADRICEPS           "  << L_Leg_old[0] << "     " << R_Leg_old[0] << endl;
//             std::cout << "OLD GLUTEUS              "   <<L_Leg_old[1] << "     " << R_Leg_old[1] << endl;
//             std::cout << "OLD HAMSTRINGS           "  <<L_Leg_old[2] << "     " << R_Leg_old[2] << endl;
//             std::cout << "OLD GASTRCNEMIOUS        "  <<L_Leg_old[3] << "     " << R_Leg_old[3] << endl;

             for (int t=0; t<cadvalue.size()-1; t++){
                 cadvalue.at(t)=cadvalue.at(t+1);
            }
             double sum_cadence=0.0;
             double mean_cadence =0.0;
             cadvalue.at(cadvalue.size()-1)=cadence;
             sum_cadence=accumulate(cadvalue.begin(),cadvalue.end(), 0.0);
             mean_cadence=sum_cadence/5.0;

             shmem.data->m_cadence=mean_cadence;

//                cout << "modality from gui: " << mod << endl;
//                cout << "support flag from gui: "<< sup << endl;
//                cout << "Init max current from gui:" << dec << static_cast<int>(Init_saturation_current) << hex << endl;
//                cout << "Init target cadence from gui:" << dec << static_cast<int>(Init_target_cadence) << hex << endl;
//                cout << "Init pulse width from gui:" << dec << static_cast<int>(Init_pulse_width) << hex << endl;

//                cout << "angolo pedali" << angolo_pedali << endl;
//                cout << "angolo pedali_sinistro" << angolo_pedali_sinistro << endl;
//                cout << "angolo pedali_destro" << angolo_pedali_destro << endl;
//                cout << "heart rate" << hr << endl;
//                cout << "Power Output Left" << po_left << endl;
//                cout << "Power Output Right" << po_right << endl;
//                cout << "Max current from gui" << max_current_value << endl;

//                cout << "Max amplitude selected from GUI: " << shmem.data->max_current_value;
//                cout << "Mean Power Output Right" << mean_po_right << endl;

//                cout << "Mean Power Output Left" << mean_po_left << endl;

//                cout << "Tangential Force Left" << tg_left << endl;

//                cout << "Tangential Force Right" << tg_right << endl;

//                cout << "Radial Force Left" << rad_left << endl;

//                cout << "Radial Force Right" << rad_right<< endl;

//                cout << "Percentage Force Right" << perc_right << endl;

//                cout << "Percentage Force Left" << perc_left << endl;

//                cout << "Smoothness Left" << smooth_left << endl;

//                cout << "Smoothness Right" << smooth_right << endl;

//                cout << "Efficiency Right" << eff_right << endl;

//                cout << "Efficiency Left" << eff_left << endl;


//                cout << "********************************************************************************" << endl;
             cout << endl;
             cout << endl;
             cout << endl;
             cout << endl;
             cout << endl;
             cout << endl;
             cout << endl;
             cout << endl;
             cout << endl;
             cout << endl;
             cout << endl;
             cout << endl;
             cout << endl;

         }



         }
     }

}

void init_shared_memory(){

    if(shmem.init())
    {
        cout << "User interface shared memory initialized with key " << hex << shmem.get_shared_memory_key() <<  endl;
    }

    else{

        cout << "User Interface shared memory initialization has been failed";
        shmem.detach_shared_memory();
    }

}





int main()
{
    init_shared_memory();
    OpenFile();
    char selection;

    cout << "ciao sono il thread della FES" << endl;

//    cout << "\nPress y to start the training session" << endl;
//    //cout << "\nPress i to insert, press c for standard configuration" << endl;
//    cin >> selection;
//    if(selection == 'i')
//        interface(initialCurrents, initialRanges_left, initialRanges_right);
//    else if(selection == 'y')

//      configure(initialCurrents, initialRanges_left, initialRanges_right);
//    configure_from_sharedmemory(initialCurrents, initialRanges_left, initialRanges_right);
      target_cadence_new =35.0;
      CadenceOld = 0;
      cadence=CadenceOld;

    //interface(initialCurrents, initialRanges_left, initialRanges_right);

      // ******
//      pthread_t thread;

    // Port name for both stimulators
    const char *port_name1 = "/dev/RehamoveStim-left";
    const char *port_name2 = "/dev/RehamoveStim-right";
//      const char *port_name1 = "/dev/ttyUSB1";
//      const char *port_name2 = "/dev/ttyUSB1";

    // Open serial port
    stimulator1.device = {0};
    stimulator2.device = {0};

    //check_open = smpt_open_serial_port(&device, port_name);.
    check_open1 = smpt_open_serial_port(&stimulator1.device, port_name1);
    check_open2 = smpt_open_serial_port(&stimulator2.device, port_name2);
    //cout << "\nCHECK open 1 = " << check_open1 << endl;

//    stimulator1.init_stimulation(&stimulator1.device);
//    stimulator2.init_stimulation(&stimulator2.device);

    bool ok_stim1 = stimulator1.init_stimulation(&stimulator1.device);
    bool ok_stim2 = stimulator2.init_stimulation(&stimulator2.device);
    cout << ok_stim1 << endl;
    cout << ok_stim2 << endl;
    shmem.data->check_stim1=ok_stim1;
    shmem.data->check_stim2=ok_stim2;


    for(int i=0; i<4; i++) {
        stimulator1.channels[i] = {0};
        stimulator2.channels[i] = {0};
    }

    stimPointer->channelsInitialization(stimulator1, number_of_points);
    stimPointer->channelsInitialization(stimulator2, number_of_points);

    // Initialization of currents, angular ranges, pulsewidth and booleans
//    chartPointer->initialization_Function(L_Leg, R_Leg, iniRangesL, finRangesL, iniRangesR, finRangesR, PulseWidth, PW, PI_start);
    chartPointer->stop_Function(L_Leg, R_Leg, L_Leg_f, R_Leg_f, PW, PI_start);

    for (int i=0; i<4; i++){
        L_Leg_old[i]=L_Leg[i];
        R_Leg_old[i]=R_Leg[i];
    }

    // PID initialization
    //pid = PID(mainT, 1, -1, kp, kd, ki); // done outside
    running = 1;
    supp_flag=1;

    writeBLE();

    clock_gettime ( CLOCK_MONOTONIC, &timeStartThread);

    tclass.start_thread();
    tclass.join_thread();




    // ***
//    pthread_create(&thread, NULL, threadFunction, nullptr);
//    pthread_join(thread, NULL);
//    pthread_detach(thread);
//    pthread_kill(thread, NULL);

    return 0;
}

