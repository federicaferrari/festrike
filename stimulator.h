#ifndef STIMULATOR_H
#define STIMULATOR_H

// HEADERS
#include "header.h"
#include <bits/stdc++.h>

using namespace std;

class stimulator
{
public:
    stimulator();

    Smpt_device device;
    Smpt_ll_channel_config channels[4];

    void channelsInitialization(stimulator &stim, uint8_t nPoints);
    void channelsDeactivation(stimulator &stim, uint8_t nPoints);



//    void init_stimulation(Smpt_device *const device);
    bool init_stimulation(Smpt_device *const device);


    void stimulation_initialization(int channel);
    void setfrequency(int strategy, int pulsewidth);
    double Tinter[4]={0,0,0,0};
    int freqB = 0;
    void stimulation_calibration(stimulator &stim, int channel,   int current, int pulsewidth);
    void stimulate(stimulator &stim, double pidCoef, vector<double> current_Leg, vector<double> current_coeff, vector<double> &current_theoretical, vector<double> &current_actual, double  max, vector<double> pulsewidthVector);

    void stimulatebiss(stimulator &stim, double pidCoef, vector<double> current_Leg, vector<double> current_coeff, vector<double> &current_theoretical, vector<double> &current_actual, vector<double>  margini, vector<double> pulsewidthVector, vector<double> maxCurrents);
//   void stimulate(stimulator &stim, double pidCoef, vector<double> current_Leg, vector<double> current_coeff, vector<double> &current_theoretical, vector<double> &current_actual, double max, vector<double> pulsewidthVector, double simmetry_coeff);
       // aggiunta simmetry coefficient
    void stimulatemitch(stimulator &stim, double pidCoef, vector<double> current_Leg, vector<double> current_coeff, vector<double> &current_theoretical, vector<double> &current_actual, vector<double> margini, vector<double> pulsewidthVector, vector<double> maxCurrents, double coeff_symm, double k_symm);


};

#endif // STIMULATOR_H
