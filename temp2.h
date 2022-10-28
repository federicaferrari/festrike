#ifndef TEMP2_H
#define TEMP2_H

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <iostream>
class temp2
{
public:
    temp2();
    void initsm();
    void write2sharedmemory_fromtemp();
    void write2temp_fromshmem();
    void writenametosm();
    void writenametosm2();
    void write2sharedmemory_initial();
    void write_start_2sharedmemory_fromtemp();
    void write_downi_2sharedmemory_fromtemp();
    void write_uppi_2sharedmemory_fromtemp();
    // Input variables
    int temp_modality_from_gui                  = 0;
    float temp_saturation_current_from_gui      = 0.0;
    float temp_pulse_width_from_gui             = 0.0;
    float temp_target_cadence_from_gui          = 0.0;
    float temp_current_cadence                  = 0.0;
    double temp_mean_cadence                    = 0.0;
    bool temp_input_running                     = 0;
    int temp_supp_flag                          = 0;
    int temp_flag_save                          = 0;

    int temp_stimulator_calibration             = 0;
    int temp_current_calibration                = 0;
    int temp_period_calibration                 = 0;
    int temp_pulsewidth_calibration             = 0;
    int temp_channel_calibration                = 0;
    int temp_flag_calibrate                     = 0;

    double temp_current_quadriceps_left         = 0.0;
    double temp_current_hamstring_left          = 0.0;
    double temp_current_gluteus_left            = 0.0;
    double temp_current_gastro_left             = 0.0;

    double temp_current_quadriceps_right        = 0.0;
    double temp_current_hamstring_right         = 0.0;
    double temp_current_gluteus_right           = 0.0;
    double temp_current_gastro_right            = 0.0;

    int temp_min_u                              = 0;
    int temp_sec_u                              = 0;
    int temp_min_d                              = 0;
    int temp_sec_d                              = 0;

    int temp_min_u_sat                          = 0;
    int temp_sec_u_sat                          = 0;
    int temp_min_d_sat                          = 0;
    int temp_sec_d_sat                          = 0;

    // BLE
    double temp_m_POL                           = 0.0;
    double temp_m_POR                           = 0.0;
    double temp_sim_left                        = 0.0;
    double temp_sim_right                       = 0.0;
    double temp_HR                              = 0.0;

    // Others
    bool temp_start_training                    = 0;
    bool temp_pause_training                    = 0;
    bool temp_stop_training                     = 0;
    bool temp_pid                               = 0;
    bool temp_up                                = 0;
    bool temp_down                              = 0;

    int temp_trg_cad                            = 0;
     std::string temp_file_name;
//    int temp_filename;
    char temp_file_name_char;
    bool temp_thread_running                    = 1;
    bool temp_stop_thread_running               = 0;

    bool temp_ok_stim1                          = 0;
    bool temp_ok_stim2                          = 0;

    bool temp_ok_pedal_left                     = 0;
    bool temp_ok_pedal_right                    = 0;
    bool temp_ok_cardio                         = 0;


    double temp_correnti_iniziali[8] = {};
    double temp_correnti_finali[8] = {};

    double temp_range_iniziali_sx[8] = {};
    double temp_range_iniziali_dx[8] = {};

    bool temp_pippo_start = 0;
    bool temp_pippo_pid   = 0;
    bool temp_pippo_up    = 0;
    bool temp_pippo_down  = 0;

    int temp_type_training_from_gui = 0;

    int temp_angle_encoder = 0;



};

#endif // TEMP2_H
