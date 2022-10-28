#include "temp2.h"
#include "shared_memory.h"
shared_memory shmem2;
#include <iostream>


using namespace std;

temp2::temp2()
{

}
void temp2::initsm(){

    if(shmem2.init()){

        cout << "User Interface shared memory initialized with key" << hex << static_cast<int>(shmem2.get_shared_memory_key()) << dec << endl;
    }
    else{

        cout << "User Interface shared memory initialization has been failed" << endl;
        shmem2.detach_shared_memory();

    }

}

void temp2::write2sharedmemory_initial(){
    shmem2.data->correnti_iniziali[0]= temp_correnti_iniziali[0];
    shmem2.data->correnti_iniziali[1]= temp_correnti_iniziali[1];
    shmem2.data->correnti_iniziali[2]= temp_correnti_iniziali[2];
    shmem2.data->correnti_iniziali[3]= temp_correnti_iniziali[3];
    shmem2.data->correnti_iniziali[4]= temp_correnti_iniziali[4];
    shmem2.data->correnti_iniziali[5]= temp_correnti_iniziali[5];
    shmem2.data->correnti_iniziali[6]= temp_correnti_iniziali[6];
    shmem2.data->correnti_iniziali[7]= temp_correnti_iniziali[7];

    shmem2.data->correnti_finali[0]= temp_correnti_finali[0];
    shmem2.data->correnti_finali[1]= temp_correnti_finali[1];
    shmem2.data->correnti_finali[2]= temp_correnti_finali[2];
    shmem2.data->correnti_finali[3]= temp_correnti_finali[3];
    shmem2.data->correnti_finali[4]= temp_correnti_finali[4];
    shmem2.data->correnti_finali[5]= temp_correnti_finali[5];
    shmem2.data->correnti_finali[6]= temp_correnti_finali[6];
    shmem2.data->correnti_finali[7]= temp_correnti_finali[7];

    shmem2.data->range_iniziali_sx[0]= temp_range_iniziali_sx[0];
    shmem2.data->range_iniziali_sx[1]= temp_range_iniziali_sx[1];
    shmem2.data->range_iniziali_sx[2]= temp_range_iniziali_sx[2];
    shmem2.data->range_iniziali_sx[3]= temp_range_iniziali_sx[3];
    shmem2.data->range_iniziali_sx[4]= temp_range_iniziali_sx[4];
    shmem2.data->range_iniziali_sx[5]= temp_range_iniziali_sx[5];
    shmem2.data->range_iniziali_sx[6]= temp_range_iniziali_sx[6];
    shmem2.data->range_iniziali_sx[7]= temp_range_iniziali_sx[7];

    shmem2.data->range_iniziali_dx[0]= temp_range_iniziali_dx[0];
    shmem2.data->range_iniziali_dx[1]= temp_range_iniziali_dx[1];
    shmem2.data->range_iniziali_dx[2]= temp_range_iniziali_dx[2];
    shmem2.data->range_iniziali_dx[3]= temp_range_iniziali_dx[3];
    shmem2.data->range_iniziali_dx[4]= temp_range_iniziali_dx[4];
    shmem2.data->range_iniziali_dx[5]= temp_range_iniziali_dx[5];
    shmem2.data->range_iniziali_dx[6]= temp_range_iniziali_dx[6];
    shmem2.data->range_iniziali_dx[7]= temp_range_iniziali_dx[7];

}

void temp2::write_start_2sharedmemory_fromtemp(){
    shmem2.data->pippo_start=temp_pippo_start;
}

void temp2::write_uppi_2sharedmemory_fromtemp(){
    shmem2.data->up=temp_up;
}

void temp2::write_downi_2sharedmemory_fromtemp(){
    shmem2.data->down=temp_down;
}

void temp2::write2sharedmemory_fromtemp(){


      // Input from GUI
      shmem2.data->saturation_current_from_gui=temp_saturation_current_from_gui;
      shmem2.data->pulse_width_from_gui= temp_pulse_width_from_gui;
      shmem2.data->target_cadence_from_gui=temp_target_cadence_from_gui;
      shmem2.data->modality_from_gui=temp_modality_from_gui;
      shmem2.data->input_running=temp_input_running;
      shmem2.data->supp_flag_sh=temp_supp_flag;
      shmem2.data->flag_save=temp_flag_save;

      shmem2.data->type_training_from_gui=temp_type_training_from_gui;


      shmem2.data->start_training=temp_start_training;
      shmem2.data->stop_training=temp_stop_training;
      shmem2.data->pause_training=temp_pause_training;
      shmem2.data->up=temp_up;
      shmem2.data->down=temp_down;
      shmem2.data->pid=temp_pid;

      // Input from calibration
      shmem2.data->stimulator_calibration=temp_stimulator_calibration;
      shmem2.data->current_calibration=temp_current_calibration;
      shmem2.data->period_calibration=temp_period_calibration ;
      shmem2.data->pulsewidth_calibration=temp_pulsewidth_calibration;
      shmem2.data->channel_calibration=temp_channel_calibration;

      shmem2.data->flag_calibrate=temp_flag_calibrate;

      // Start stimulation program
      shmem2.data->thread_running = temp_thread_running;
      shmem2.data -> stop_thread_running = temp_stop_thread_running;





}

void temp2::write2temp_fromshmem(){

    temp_current_cadence           = shmem2.data->current_cadence;
    temp_mean_cadence              = shmem2.data->m_cadence;
    temp_trg_cad                   = shmem2.data->trg_cad;

    temp_current_quadriceps_left   = shmem2.data->current_quadriceps_left;
    temp_current_hamstring_left    = shmem2.data->current_hamstring_left;
    temp_current_gluteus_left      = shmem2.data->current_gluteus_left;
    temp_current_gastro_left       = shmem2.data->current_gastro_left;

    temp_current_quadriceps_right  = shmem2.data->current_quadriceps_right;
    temp_current_hamstring_right   = shmem2.data->current_hamstring_right;
    temp_current_gluteus_right     = shmem2.data->current_gluteus_right;
    temp_current_gastro_right      = shmem2.data->current_gastro_right;

    temp_min_d                     = shmem2.data->min_d;
    temp_min_u                     = shmem2.data->min_u;
    temp_sec_d                     = shmem2.data->sec_d;
    temp_sec_u                     = shmem2.data->sec_u;

    temp_min_d_sat                 = shmem2.data->saturation_min_d;
    temp_min_u_sat                 = shmem2.data->saturation_min_u;
    temp_sec_d_sat                 = shmem2.data->saturation_sec_d;
    temp_sec_u_sat                 = shmem2.data->saturation_sec_u;

    temp_HR                        = shmem2.data->heart_rate;
    temp_m_POL                     = shmem2.data->mean_power_left;
    temp_m_POR                     = shmem2.data->mean_power_right;
    temp_sim_left                  = shmem2.data->percentage_left;
    temp_sim_right                 = shmem2.data->percentage_right;

    temp_file_name                 = shmem2.data->file_name;
    temp_file_name_char            = shmem2.data->file_name_char;
    temp_pid                       = shmem2.data->pid;
    temp_start_training            = shmem2.data->start_training;

    //Check initialization of the stimulators
    temp_ok_stim1                  = shmem2.data->check_stim1;
    temp_ok_stim2                  = shmem2.data->check_stim2;

    temp_ok_pedal_left             =shmem2.data->check_pedal_left;
    temp_ok_pedal_right            =shmem2.data->check_pedal_right;
    temp_ok_cardio                 =shmem2.data->check_cardio;

    temp_angle_encoder             =shmem2.data->angle_encoder;

}


void temp2::writenametosm(){
    shmem2.data->file_name        = temp_file_name;
}
void temp2::writenametosm2(){

    shmem2.data->file_name_char        = temp_file_name_char;
}
