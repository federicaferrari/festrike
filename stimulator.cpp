#include "stimulator.h"
#include "header.h"
#include "globalvariables.h"

vector<bool> checkSent(4);

stimulator::stimulator()
{

}

void stimulator::channelsInitialization(stimulator &stim, uint8_t nPoints)
{
    stim.channels[0].enable_stimulation = true;
    stim.channels[0].channel = Smpt_Channel_Red;
    stim.channels[0].number_of_points = nPoints;

    stim.channels[1].enable_stimulation = true;
    stim.channels[1].channel = Smpt_Channel_Blue;
    stim.channels[1].number_of_points = nPoints;

    stim.channels[2].enable_stimulation = true;
    stim.channels[2].channel = Smpt_Channel_Black;
    stim.channels[2].number_of_points = nPoints;

    stim.channels[3].enable_stimulation = true;
    stim.channels[3].channel = Smpt_Channel_White;
    stim.channels[3].number_of_points = nPoints;
}


void stimulator::channelsDeactivation(stimulator &stim, uint8_t nPoints)
{
    stim.channels[0].enable_stimulation = false;
    stim.channels[0].channel = Smpt_Channel_Red;
    stim.channels[0].number_of_points = nPoints;

    stim.channels[1].enable_stimulation = false;
    stim.channels[1].channel = Smpt_Channel_Blue;
    stim.channels[1].number_of_points = nPoints;

    stim.channels[2].enable_stimulation = false;
    stim.channels[2].channel = Smpt_Channel_Black;
    stim.channels[2].number_of_points = nPoints;

    stim.channels[3].enable_stimulation = false;
    stim.channels[3].channel = Smpt_Channel_White;
    stim.channels[3].number_of_points = nPoints;
}



//void stimulator::init_stimulation(Smpt_device *const device)
//{
//    Smpt_ll_init ll_init = {0};  /* Struct for ll_init command */
//    Smpt_ll_init_ack ll_init_ack = {0};  /* Struct for ll_init_ack response */
//    Smpt_ack ack = {0};  /* Struct for general response */
//    timespec time_now;

//    smpt_clear_ll_init(&ll_init);
//    ll_init.packet_number = smpt_packet_number_generator_next(device);

//    printf("SMPT init_stimulaton(): send Ll_init command ...\n");
//    clock_gettime( CLOCK_MONOTONIC, &time_now);
//    long t_start_sent = timeStructToMs(time_now);
//    smpt_send_ll_init(device, &ll_init);   /* Send the ll_init command to the stimulation unit */

//    while (!smpt_new_packet_received(device)) { /* busy waits for Ll_init_ack response */}
//    clock_gettime( CLOCK_MONOTONIC, &time_now);
//    printf("SMPT init_stimulaton(): Ll_init_ack received, took %ld ms...\n", timeStructToMs(time_now) - t_start_sent);

//    smpt_clear_ack(&ack);
//    smpt_last_ack(device, &ack);

//    if (ack.command_number == Smpt_Cmd_Ll_Init_Ack)
//    {
//        smpt_get_ll_init_ack(device, &ll_init_ack);  /* Writes the received data into ll_init_ack */
//        if ( ll_init_ack.result == Smpt_Result_Successful )
//            printf("SMPT init_stimulation(): Ll_init command was successful\n");
//        else
//            printf("SMPT init_stimulation(): Ll_init command failed! Return code: %d\n", (int)ll_init_ack.result);
//    }

//    else
//    {
//        printf("SMPT init_stimulation(): Unexpected ack received! Command ID: %d\n", (int)ack.command_number);
//    }
//    printf("\n\n");
//}


bool stimulator::init_stimulation(Smpt_device *const device)
{
    Smpt_ll_init ll_init = {0};  /* Struct for ll_init command */
    Smpt_ll_init_ack ll_init_ack = {0};  /* Struct for ll_init_ack response */
    Smpt_ack ack = {0};  /* Struct for general response */
    timespec time_now;
    bool bool_init = 0;

    smpt_clear_ll_init(&ll_init);
    ll_init.packet_number = smpt_packet_number_generator_next(device);

    printf("SMPT init_stimulaton(): send Ll_init command ...\n");
    clock_gettime( CLOCK_MONOTONIC, &time_now);
    long t_start_sent = timeStructToMs(time_now);
    smpt_send_ll_init(device, &ll_init);   /* Send the ll_init command to the stimulation unit */

    while (!smpt_new_packet_received(device)) { /* busy waits for Ll_init_ack response */}
    clock_gettime( CLOCK_MONOTONIC, &time_now);
    printf("SMPT init_stimulaton(): Ll_init_ack received, took %ld ms...\n", timeStructToMs(time_now) - t_start_sent);

    smpt_clear_ack(&ack);
    smpt_last_ack(device, &ack);

    if (ack.command_number == Smpt_Cmd_Ll_Init_Ack)
    {
        smpt_get_ll_init_ack(device, &ll_init_ack);  /* Writes the received data into ll_init_ack */
        if ( ll_init_ack.result == Smpt_Result_Successful ){
            printf("SMPT init_stimulation(): Ll_init command was successful\n");
            bool_init=1;}
        else
            printf("SMPT init_stimulation(): Ll_init command failed! Return code: %d\n", (int)ll_init_ack.result);
    }

    else
    {
        printf("SMPT init_stimulation(): Unexpected ack received! Command ID: %d\n", (int)ack.command_number);
    }
    printf("\n\n");

    return bool_init;
}


void stimulator::stimulate(stimulator &stim, double pidCoef, vector<double> current_Leg, vector<double> current_coeff, vector<double> &current_theoretical, vector<double> &current_actual, double max, vector<double> pulsewidthVector)
{

    double maxCurrent;
    double margin;
    vector<double> margine[8];
    float current_toSum;

    // Old correct version of the code
    maxCurrent = *max_element(current_Leg.begin(), current_Leg.end());
    margin = max - maxCurrent;
    current_toSum = margin * pidCoef;


    for(int i=0; i<4; i++) {
        current_theoretical[i] = current_Leg[i] + current_toSum;
        // check whether obtained current is negative -> in case set to zero
        if(current_theoretical[i] < 0)
            current_theoretical[i] = 0;
    }


    for(int i=0; i<4; i++) {
        current_actual[i] = current_theoretical[i] * current_coeff[i];
    }

    // STIMULATION
    for(int i=0; i<4; i++) {
        stim.channels[i].packet_number = smpt_packet_number_generator_next(&stim.device);
    }

    // we use biphasic wave with 3 points (positive current, zero and negative current)
    for(int i=0; i<4; i++){
        for(int j=0; j<number_of_points; j++){
            stim.channels[i].points[j].current =  current_actual[i] * waveCoeff[j];
            stim.channels[i].points[j].time = pulsewidthVector[i];
        }
    }

    for(int i=0; i<4; i++){
        checkSent[i] = smpt_send_ll_channel_config(&stim.device, &stim.channels[i]);
    }
}


void stimulator::stimulatebiss(stimulator &stim, double pidCoef, vector<double> current_Leg, vector<double> current_coeff, vector<double> &current_theoretical, vector<double> &current_actual, vector<double> margini, vector<double> pulsewidthVector, vector<double> maxCurrents)
{


//    vector<double> current_toSum = {0,0,0,0};
    double maxCurrent;
    vector<double> current_toSum = {0.0,0.0,0.0,0.0};


    // Old correct version of the code
    maxCurrent = *max_element(current_Leg.begin(), current_Leg.end());


    for (int i=0; i<4; i++) {
        current_toSum[i] = margini[i] * pidCoef;
    }



    for(int i=0; i<4; i++) {
        if((current_Leg[i]+current_toSum[i])<=maxCurrents[i]){
        current_theoretical[i] = current_Leg[i] + current_toSum[i];}
        // check whether obtained current is negative -> in case set to zero
        if(current_theoretical[i] < 0)
            current_theoretical[i] = 0;
    }


    for(int i=0; i<4; i++) {
        current_actual[i] = current_theoretical[i] * current_coeff[i];
    }

    // STIMULATION
    for(int i=0; i<4; i++) {
        stim.channels[i].packet_number = smpt_packet_number_generator_next(&stim.device);
    }

    // we use biphasic wave with 3 points (positive current, zero and negative current)
    for(int i=0; i<4; i++){
        for(int j=0; j<number_of_points; j++){
            stim.channels[i].points[j].current =  current_actual[i] * waveCoeff[j];
            stim.channels[i].points[j].time = pulsewidthVector[i];
        }
    }

    for(int i=0; i<4; i++){
        checkSent[i] = smpt_send_ll_channel_config(&stim.device, &stim.channels[i]);
    }
}

void stimulator::stimulatemitch(stimulator &stim, double pidCoef, vector<double> current_Leg, vector<double> current_coeff, vector<double> &current_theoretical, vector<double> &current_actual, vector<double> margini, vector<double> pulsewidthVector, vector<double> maxCurrents, double coeff_symm, double k_symm)
{


//    vector<double> current_toSum = {0,0,0,0};
    double maxCurrent;
    vector<double> current_toSum = {0.0,0.0,0.0,0.0};


    // Old correct version of the code
    maxCurrent = *max_element(current_Leg.begin(), current_Leg.end());


    for (int i=0; i<4; i++) {
        current_toSum[i] = margini[i] * (pidCoef+k_symm*coeff_symm);
    }



    for(int i=0; i<4; i++) {
        if((current_Leg[i]+current_toSum[i])<=maxCurrents[i]){
        current_theoretical[i] = current_Leg[i] + current_toSum[i];}
        // check whether obtained current is negative -> in case set to zero
        if(current_theoretical[i] < 0)
            current_theoretical[i] = 0;
    }


    for(int i=0; i<4; i++) {
        current_actual[i] = current_theoretical[i] * current_coeff[i];
    }

    // STIMULATION
    for(int i=0; i<4; i++) {
        stim.channels[i].packet_number = smpt_packet_number_generator_next(&stim.device);
    }

    // we use biphasic wave with 3 points (positive current, zero and negative current)
    for(int i=0; i<4; i++){
        for(int j=0; j<number_of_points; j++){
            stim.channels[i].points[j].current =  current_actual[i] * waveCoeff[j];
            stim.channels[i].points[j].time = pulsewidthVector[i];
        }
    }

    for(int i=0; i<4; i++){
        checkSent[i] = smpt_send_ll_channel_config(&stim.device, &stim.channels[i]);
    }
}




void stimulator::stimulation_calibration(stimulator &stim, int channel,  int current, int pulsewidth){

    stim.channels[channel].packet_number = smpt_packet_number_generator_next(&stim.device);

    for(int j=0; j<number_of_points; j++){
        stim.channels[channel].points[j].current =  current* waveCoeff[j];
        stim.channels[channel].points[j].time = pulsewidth;
    }

    checkSent[channel] = smpt_send_ll_channel_config(&stim.device, &stim.channels[channel]);
    cout << "check  " <<checkSent[channel] << ' ' << endl;
 }



void stimulator::setfrequency(int strategy, int pulsewidth){

    if(strategy==1){
        Tinter[0]=Tinter[1]=Tinter[2]=Tinter[3]={0.0};
    }

    if(strategy==2){
        Tinter[0]=1000/(stimF*2);
        Tinter[1]=Tinter[2]=Tinter[3]={0.0};
    }

    if(strategy==3){
        freqB=pulsewidth/5;
        Tinter[0]=1000/freqB;
        Tinter[1]=Tinter[0]*2;
        Tinter[2]=Tinter[0]*3;
        Tinter[3]=Tinter[0]*4;
    }

}












