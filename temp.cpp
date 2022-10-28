#include "temp.h"
#include "shared_memory.h"
shared_memory shmem;
#include <iostream>
using namespace std;

temp::temp()
{

}

void temp::write2sm(){

    shmem.data->angle_pedals = temp_angolo;

    //CARDIO
    shmem.data->heart_rate=temp_heart_rate;

    //    double RR = 0.0;
    //    double temp_RR = 0.0;


    //PEDALI
    // Time from pedals
    shmem.data->time_pedal_left=temp_time_pedal_left;
    shmem.data->time_pedal_right=temp_time_pedal_right;

    // Angle from pedals
    shmem.data->angle_pedals_left=temp_angle_pedals_left;
    shmem.data->angle_pedals_right=temp_angle_pedals_right;

    // Cadence from pedals
    shmem.data->cadence_pedal_left=temp_cadence_pedal_left;
    shmem.data->cadence_pedal_right=temp_cadence_pedal_right;

    // Istantaneous forces
    shmem.data->tangential_force_left=temp_tangential_force_left;
    shmem.data->tangential_force_right=temp_tangential_force_right;

    shmem.data->radial_force_left=temp_radial_force_left;
    shmem.data->radial_force_right=temp_radial_force_right;

    // Istantaneous power
    shmem.data->power_left=temp_power_left;
    shmem.data->power_right=temp_power_right;

    // Istantaneous pedal efficiency
    shmem.data->pedal_efficiency_left=temp_pedal_efficiency_left;
    shmem.data->pedal_efficiency_right=temp_pedal_efficiency_right;

    // Mean power calculated over 360 deg
    shmem.data->mean_power_left = temp_mean_power_left;
    shmem.data->mean_power_right= temp_mean_power_right;

    // Index over 360 deg
    shmem.data->percentage_left=temp_percentage_left;
    shmem.data->percentage_right=temp_percentage_right;
    shmem.data->pedal_smoothness_left=temp_pedal_smoothness_left;
    shmem.data->pedal_smoothness_right=temp_pedal_smoothness_right;

    //Check Ble
    shmem.data->check_pedal_left=temp_pLeft;
    shmem.data->check_pedal_right=temp_pRight;
    shmem.data->check_cardio=temp_cardio;

   //Mean tf
    shmem.data->tfmedia_left= temp_tfmedia_left;
    shmem.data->tfmedia_right= temp_tfmedia_right;
  
}
