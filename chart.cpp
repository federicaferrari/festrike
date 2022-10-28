#include "chart.h"
#include "header.h"
#include "globalvariables.h"
#include <wiringPi.h>

using namespace std;
int8_t state;
int input = 0;


long time_buttonPressed;
//double chart::previousCurrents[2][9] = {60, 60, 60, 50, 60, 60, 60, 50, 400, 130, 180, 300, 310, 240, 290, 50, 50, 0};
chart::chart()
{

}

void chart::currentsInitialization(vector<double> &vect, vector<double> &vect2, vector<double> &vectf, vector<double> &vectf2)
{
    vect[0] = initialCurrents[0];
    vect[1] = initialCurrents[1];
    vect[2] = initialCurrents[2];
    vect[3] = initialCurrents[3];
    vect2[0] = initialCurrents[4];
    vect2[1] = initialCurrents[5];
    vect2[2] = initialCurrents[6];
    vect2[3] = initialCurrents[7];

    vectf[0] = finalCurrents[0];
    vectf[1] = finalCurrents[1];
    vectf[2] = finalCurrents[2];
    vectf[3] = finalCurrents[3];
    vectf2[0] = finalCurrents[4];
    vectf2[1] = finalCurrents[5];
    vectf2[2] = finalCurrents[6];
    vectf2[3] = finalCurrents[7];
}

void chart::currentsInitialization_switch(vector<double> &vect, vector<double> &vect2)
{
    vect[0] = actualCurrentsL[0];
    vect[1] = actualCurrentsL[1];
    vect[2] = actualCurrentsL[2];
    vect[3] = actualCurrentsL[3];
    vect2[0] = actualCurrentsL[4];
    vect2[1] = actualCurrentsL[5];
    vect2[2] = actualCurrentsL[6];
    vect2[3] = actualCurrentsL[7];
}

void chart::initialization_Function_switch(vector<double> &currentsL, vector<double> &currentsR,vector<double> &currentsfL, vector<double> &currentsfR, vector<double> &startRangeL,
                                    vector<double> &endRangeL, vector<double> &startRangeR, vector<double> &endRangeR, double &pulsewidth, double &PW, bool &PI_flag) {

    currentsInitialization_switch(currentsL, currentsR);
    pulsewidth = PulseWidth;
    for(int i=0; i<4; i++) {
        startRangeL[i] = initialRanges_left[i];
    }
    for(int i=0; i<4; i++) {
        endRangeL[i] = initialRanges_left[i+4];
    }
    for(int i=0; i<4; i++) {
        startRangeR[i] = initialRanges_right[i];
    }
    for(int i=0; i<4; i++) {
        endRangeR[i] = initialRanges_right[i+4];
    }
    PW = 0;
    PI_flag = 1;
}

void chart::stop_Function(vector<double> &currentsL, vector<double> &currentsR, vector<double> &currentsfL, vector<double> &currentsfR,double &PW, bool &PI_flag)
{
    currentsInitialization(currentsL, currentsR, currentsfL, currentsfR);

    PW = 0;
    PI_flag = 1;
}

void chart::initialization_Function(vector<double> &currentsL, vector<double> &currentsR, vector<double> &currentsfL, vector<double> &currentsfR, vector<double> &startRangeL,
                                    vector<double> &endRangeL, vector<double> &startRangeR, vector<double> &endRangeR, double &pulsewidth, double &PW, bool &PI_flag) {

    currentsInitialization(currentsL, currentsR, currentsfL, currentsfR);
    pulsewidth = PulseWidth;
    for(int i=0; i<4; i++) {
        startRangeL[i] = initialRanges_left[i];
    }
    for(int i=0; i<4; i++) {
        endRangeL[i] = initialRanges_left[i+4];
    }
    for(int i=0; i<4; i++) {
        startRangeR[i] = initialRanges_right[i];
    }
    for(int i=0; i<4; i++) {
        endRangeR[i] = initialRanges_right[i+4];
    }
    PW = 0;
    PI_flag = 1;
}

void chart::computeCoefficients(float angle, float delay, vector<double> startRangeL, vector<double> stopRangeL, vector<double> startRangeR, vector<double> stopRangeR, vector<double> &coeffsL, vector<double> &coeffsR)
{
    float angleL = angle + delay;
    //float angleR = angle + delay + 180;
    float angleR = angle + delay;

    if(angleL > 360)
        angleL = angleL - 360;

    if(angleR > 360)
        angleR = angleR - 360;

    int a;
    int b;
    int c;
    int d;

    // Left
    for(int i=0; i<4; i++) {
        if(modulateON[i]) {
            a = 15;
            b = 10;
            c = 0;
            d = -10;
        }
        else {
            a = 15;
            b = 15;
            c = 15;
            d = 0;

        }
        modulate(startRangeL, stopRangeL, angleL, coeffsL, a, b, c, d, i);
        // cout << "\nRanges LEFT" << coeffsL[0] << " " << coeffsL[1] << " " << coeffsL[2] << " " << coeffsL[3] << endl;
    }

    // Right
    for(int i=0; i<4; i++) {
        if(modulateON[i]) {
            a = 10;
            b = 5;
            c = 0;
            d = -5;
        }
        else {
            a = 15;
            b = 15;
            c = 15;
            d = 0;
        }
        modulate(startRangeR, stopRangeR, angleR, coeffsR, a, b, c, d, i);
        // cout << "\nRanges LEFT" << coeffsR[0] << " " << coeffsR[1] << " " << coeffsR[2] << " " << coeffsR[3] << endl;

    }
}


void chart::modulate(vector<double> startRange, vector<double> stopRange, float angle, vector<double> &coeffs, int a, int b, int c, int d, int i) {

    if(startRange[i] < stopRange[i]) { // going from start to stop, 360 is not passed

        if (angle >= startRange[i]-a && angle <= stopRange[i]+a) {
           if(angle >= startRange[i]-b && angle <= stopRange[i]+b) {
               if(angle >= startRange[i]-c && angle <= stopRange[i]+c) {
                   if(angle >= startRange[i]-d && angle <= stopRange[i]+d)
                        coeffs[i] = 1;
                   else
                       coeffs[i] = 0.8;
               }
               else
                   coeffs[i] = 0.6;
           }
           else
               coeffs[i] = 0.4;
        }
        else
            coeffs[i] = 0;
    }

    else { // going from start to stop, 360 is passed -> angle count restarts from 0 so, final angle is smaller then initial (use or instead of and)
        if (angle >= startRange[i]-a || angle <= stopRange[i]+a) {
           if(angle >= startRange[i]-b || angle <= stopRange[i]+b) {
               if(angle >= startRange[i]-c || angle <= stopRange[i]+c) {
                   if(angle >= startRange[i]-d || angle <= stopRange[i]+d)
                       coeffs[i] = 1;
                  else
                      coeffs[i] = 0.8;
              }
              else
                  coeffs[i] = 0.6;
          }
          else
              coeffs[i] = 0.4;
       }
       else
           coeffs[i] = 0;
   }

}
/*
long chart::time_now(void)
{
    // Get start time for timing measurements
    gettimeofday(&start_, NULL);

    u1_ = start_.tv_sec * 1000 + start_.tv_usec / 1000;

    return (long) u1_;
}
*/






void chart::readButton(){
    wiringPiSetup();

    pinMode(UP,INPUT);
    pinMode(DOWN, INPUT);
    pinMode(SS, INPUT);
    pinMode(PD, INPUT);

    buttons[0]= digitalRead(SS);
    buttons[1]= digitalRead(UP);
    buttons[2]= digitalRead(PD);
    buttons[3]= digitalRead(DOWN);

}





