#include "cadenceblock.h"
#include "header.h"
#include"globalvariables.h"

using namespace std;

cadenceBlock::cadenceBlock()
{

}


//int nSamples = 30;
//struct timespec timeNow;

//vector<timespec> timeWindow(nSamples);
//vector<float> angleWindow(nSamples);
//vector<timespec> timeWindow_old(nSamples);
//vector<float> angleWindow_old(nSamples);

//bool filledWindow = false;
//int nCycles;
//float angleDifference;
//long timeDifference;
//float cad;

//float cadenceBlock::computeCadence(float previous_angle, float now_angle)
//{
//    if(previous_angle == -1) { // exlude first cycle where oldAngle is unknown
//        nCycles = 1;
//        angleWindow_old[nCycles-1] = now_angle;
//        clock_gettime( CLOCK_MONOTONIC, &timeWindow_old[nCycles-1] );

//        return -1;
//    }

//    if(filledWindow == false) { //registering initial samples
//        nCycles = nCycles + 1;
//        angleWindow_old[nCycles-1] = now_angle;
//        clock_gettime( CLOCK_MONOTONIC, &timeWindow_old[nCycles-1] );

//        if(now_angle >= previous_angle) //"normal" case
//            angleDifference = now_angle - previous_angle;
//        else //passing from 360 to 0
//            angleDifference = now_angle + 360 - previous_angle;

//        cad = (angleDifference * mainF * 60)/360; //in first samples, cadence computed angle by angle

//        if(nCycles == nSamples)
//            filledWindow = true;
//    }

//    else { //window filles and moving average can be computed
//        // save values of "new" window
//        for(int k = 1; k < nSamples; k++) {
//            angleWindow[k-1] = angleWindow_old[k];
//            timeWindow[k-1] = timeWindow_old[k];
//        }
//        angleWindow[nSamples-1]=now_angle;
//        clock_gettime( CLOCK_MONOTONIC, &timeWindow[nSamples-1] );

//        // compute angleDifference
//        if(angleWindow[nSamples-1] >= angleWindow[0])
//            angleDifference = angleWindow[nSamples-1] - angleWindow[0];
//        else
//            angleDifference = angleWindow[nSamples-1] + 360 - angleWindow[0];

//        timeDifference = (timeStructToMs(timeWindow[nSamples-1]) - timeStructToMs(timeWindow[0]));

//        // compute cadence
//        cad = ( (angleDifference/timeDifference) * 1000 * 60 )/360.0;

//        // update Values
//        angleWindow_old = angleWindow;
//        timeWindow_old = timeWindow;
//    }

//    return cad;
//}



float angle_difference = -99.0;
float previous_angle_difference = -99.0;
int interval = 30;
struct timespec tau_now;
struct timespec tau_old;
float previous_cadence = 0;


float angle_old;
float cadenceBlock::computeCadence(float previous_angle, float now_angle)
{
    float cadence;

    if(previous_angle == -1) { // FIRST ITERATION
//        cadence = prev_cad; // exlude first cycle where oldAngle is unknown
//        previous_cadence = cadence;
        clock_gettime ( CLOCK_MONOTONIC, &tau_old);
        angle_old = now_angle;
    }

    else {
        //previous_angle_difference = angle_difference;
        if(now_angle > angle_old){  // normal case
            angle_difference = now_angle - angle_old;}

        else if(now_angle==angle_old) {angle_difference=0;}

        else if(now_angle<angle_old){// in case difference is negative, meaning we are passing from 360 to 0
            angle_difference = (now_angle + 360) - angle_old;}
        //        cout << "\n\nAAAAAaAA angle diff = " << angle_difference << endl;
        //        cout << "\n\nAAAAAaAA angle OLD = " << angle_old << endl;
        //        cout << "\n\nAAAAAaAA angle NOW = " << now_angle << endl;

        if(angle_difference >= interval) { // Compute cadence
            clock_gettime ( CLOCK_MONOTONIC, &tau_now);
            cadence = ( ( angle_difference/(timeStructToMs(tau_now) - timeStructToMs(tau_old)) ) * 1000 * 60 )/360.0;
            //cout << "\n\nAAAAAaAA cadence = " << cadence << endl;
            previous_cadence = cadence;
            tau_old = tau_now;
            angle_old = now_angle;
        }

        else if(angle_difference < interval){
            cadence = previous_cadence;}

    }

    return cadence;
}

float cadenceBlock::computeDelay(float cad)
{
    float constant = 0.72;
    float del;

    if (cad < 30)
        del = 25;
    else if (cad >= 30 && cad <= 50)
        del = 40;
    else if (cad > 50 && cad < 100)
        del = 60;
    else
        del = 0;

    return (del * constant);
}


double cadenceBlock::filterCadence(double cad_now, double filtC_old )
{
        double filtC_now = 0.0;
        //float absDiff = abs (cad_now-filtC_old); // to choose different value of lambda
        double lambda=0.1; // default value

        //TO DO: adding different value of lambda

        filtC_now = lambda*cad_now + ( 1 - lambda)*filtC_old;
        return (filtC_now);
}













