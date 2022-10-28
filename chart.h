#ifndef CHART_H
#define CHART_H

#include "header.h"




#define UP 3
#define SS 7
#define DOWN 23
#define PD 0

using namespace std;

class chart
{
public:
    chart();

    void currentsInitialization(vector<double> &vect, vector<double> &vect2, vector<double> &vectf, vector<double> &vectf2);
    void currentsInitialization_switch(vector<double> &vect, vector<double> &vect2);

    void initialization_Function(vector<double> &currentsL, vector<double> &currentsR, vector<double> &currentsfL, vector<double> &currentsfR,vector<double> &startRangeL,
                                        vector<double> &endRangeL, vector<double> &startRangeR, vector<double> &endRangeR, double &pulsewidth, double &PW, bool &PI_flag);
    void initialization_Function_switch(vector<double> &currentsL, vector<double> &currentsR,vector<double> &currentsfL, vector<double> &currentsfR, vector<double> &startRangeL,
                                        vector<double> &endRangeL, vector<double> &startRangeR, vector<double> &endRangeR, double &pulsewidth, double &PW, bool &PI_flag);

    void stop_Function(vector<double> &currentsL, vector<double> &currentsR, vector<double> &currentsfL, vector<double> &currentsfR, double &PW, bool &PI_flag);

    void computeCoefficients(float angle, float delay, vector<double> startRangeL, vector<double> stopRangeL, vector<double> startRangeR, vector<double> stopRangeR, vector<double> &coeffsL, vector<double> &coeffsR);

    long time_now(void);

    void modulate(vector<double> startRange, vector<double> stopRange, float angle, vector<double> &coeffs, int a, int b, int c, int d, int i);

    void readButton();

    enum State
    {
        INIT = 0,
        STOP,
        START
    };

    vector <bool> button_pressed={0,0,0,0};
    vector <bool> old_button_pressed={0,0,0,0};
    vector <bool> old_buttons={0,0,0,0};
    vector <bool> buttons={0,0,0,0};
    bool button_start    = 0;
    bool button_stop     = 1;
    bool button_pause    = 1;
    bool stopwaspressed  = 0;
    bool button_start_old = 0;
    bool pausewaspressed = 0;
    bool startwaspressed = 0;
    int wait = 0;
    bool waiting = 0;
    bool currentup=0;
    bool currentdown=0;
    bool inizio=1;
    bool pid_start=0;
    bool pid_attivo=1;
    bool pid_attivo_button=1;

    bool start_frombuttons = 0;
    bool pause_frombuttons = 0;
    bool pid_frombuttons   = 0;
    bool up_frombuttons    = 0;
    bool down_frombuttons  = 0;
};

#endif // CHART_H
