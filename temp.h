#ifndef TEMP_H
#define TEMP_H


class temp
{
public:
    temp();
    bool temp_angolo = 0;
    //Check BLE
    bool temp_pLeft=0;
    bool temp_pRight=0;
    bool temp_cardio=0;

    void write2sm();

    double temp_time_pedal_left = 0.0;
    double temp_time_pedal_right = 0.0;
    double temp_cadence_pedal_left = 0.0;
    double temp_cadence_pedal_right = 0.0;

    // Istantaneous forces
    double temp_tangential_force_right = 0.0;
    double temp_tangential_force_left = 0.0;
    double temp_radial_force_right = 0.0;
    double temp_radial_force_left = 0.0;

    // Istantaneous power
    double temp_power_left = 0.0;
    double temp_power_right = 0.0;

    // Pedals angle
    double temp_angle_pedals_left = 0.0; //***
    double temp_angle_pedals_right = 0.0; //***

    // Mean power calculated over 360 deg
    double temp_mean_power_left = 0.0;
    double temp_mean_power_right = 0.0;
    double temp_percentage_left = 0.0;
    double temp_percentage_right = 0.0;
    double temp_pedal_smoothness_left = 0.0;
    double temp_pedal_smoothness_right = 0.0;

    //Mean tf
    double temp_tfmedia_left= 0.0;
    double temp_tfmedia_right=0.0;

    // Istantaneous pedal efficiency
    double temp_pedal_efficiency_left = 0.0;
    double temp_pedal_efficiency_right = 0.0;

    // Heart rate monitor
    double temp_heart_rate = 0.0;
    double temp_RR = 0.0;

    int temp_cicli_ble_right = 0;
    bool temp_flag_ciclo_right = 0;
    int temp_cicli_ble_left = 0;
    bool temp_flag_ciclo_left = 0;

};

#endif // TEMP_H
