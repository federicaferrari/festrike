#include "mythread.h"
#include <QtCore>

mythread::mythread(QObject *parent):
    QThread(parent)
{

}



void mythread::run(){


            // Modify with the name of your port

    if(stimolatore==1){
            const char *port_name = "/dev/RehamoveStim-left";
            Smpt_device device= {0};
            smpt_open_serial_port(&device, port_name);

            // Open serial port

            Smpt_ml_init ml_init = {0};           /* Struct for ml_init command */
            smpt_clear_ml_init(&ml_init);
            ml_init.packet_number = smpt_packet_number_generator_next(&device);
            smpt_send_ml_init(&device, &ml_init); /* Send the ml_init command to the stimulation unit */

            Smpt_ml_update ml_update = {0};
            smpt_clear_ml_update(&ml_update);

            ml_update.enable_channel[canale] = true;
            ml_update.packet_number = smpt_packet_number_generator_next(&device);

            ml_update.channel_config[canale].number_of_points = 3;
            ml_update.channel_config[canale].ramp = 3;
            ml_update.channel_config[canale].period = 30;

            ml_update.channel_config[canale].points[0].current = corrente;
            ml_update.channel_config[canale].points[1].current = 0;
            ml_update.channel_config[canale].points[2].current = -corrente;

            ml_update.channel_config[canale].points[0].time = pulsewidth;
            ml_update.channel_config[canale].points[1].time = 0;
            ml_update.channel_config[canale].points[2].time = pulsewidth;

            while(this->Stop==false){

            qDebug()<< "corrente" << corrente;
            qDebug()<< "frequenza" << frequenza;
            qDebug()<< "pulsewidth" << pulsewidth;
            qDebug() << "canale" << canale;

            check_send=smpt_send_ml_update(&device, &ml_update);
            qDebug() << "check send" << check_send;

            Smpt_ml_get_current_data ml_get_current_data = {0};
            ml_get_current_data.packet_number = smpt_packet_number_generator_next(&device);
            ml_get_current_data.data_selection[Smpt_Ml_Data_Stimulation] = true;

            check_data=smpt_send_ml_get_current_data(&device, &ml_get_current_data);
            qDebug() << "check data" << check_data;
            //this->usleep(2000*1000);
            this->sleep(1);
            }

            if(this->Stop==true){

            ml_update.enable_channel[canale] = false;
            smpt_send_ml_stop(&device, smpt_packet_number_generator_next(&device));
            check_close= smpt_close_serial_port(&device);
            }
    }

    if(stimolatore==2){
            const char *port_name = "/dev/RehamoveStim-right";
            Smpt_device device= {0};
            smpt_open_serial_port(&device, port_name);

            // Open serial port

            Smpt_ml_init ml_init = {0};           /* Struct for ml_init command */
            smpt_clear_ml_init(&ml_init);
            ml_init.packet_number = smpt_packet_number_generator_next(&device);
            smpt_send_ml_init(&device, &ml_init); /* Send the ml_init command to the stimulation unit */

            Smpt_ml_update ml_update = {0};
            smpt_clear_ml_update(&ml_update);

            ml_update.enable_channel[canale] = true;
            ml_update.packet_number = smpt_packet_number_generator_next(&device);

            ml_update.channel_config[canale].number_of_points = 3;
            ml_update.channel_config[canale].ramp = 3;
            ml_update.channel_config[canale].period = 30;

            ml_update.channel_config[canale].points[0].current = corrente;
            ml_update.channel_config[canale].points[1].current = 0;
            ml_update.channel_config[canale].points[2].current = -corrente;

            ml_update.channel_config[canale].points[0].time = pulsewidth;
            ml_update.channel_config[canale].points[1].time = 0;
            ml_update.channel_config[canale].points[2].time = pulsewidth;

            while(this->Stop==false){

            qDebug()<< "corrente" << corrente;
            qDebug()<< "frequenza" << frequenza;
            qDebug()<< "pulsewidth" << pulsewidth;
            qDebug() << "canale" << canale;

            check_send=smpt_send_ml_update(&device, &ml_update);
            qDebug() << "check send" << check_send;

            Smpt_ml_get_current_data ml_get_current_data = {0};
            ml_get_current_data.packet_number = smpt_packet_number_generator_next(&device);
            ml_get_current_data.data_selection[Smpt_Ml_Data_Stimulation] = true;

            check_data=smpt_send_ml_get_current_data(&device, &ml_get_current_data);
            qDebug() << "check data" << check_data;
            //this->usleep(2000*1000);
            this->sleep(1);
            }

            if(this->Stop==true){

            ml_update.enable_channel[canale] = false;
            smpt_send_ml_stop(&device, smpt_packet_number_generator_next(&device));
            check_close= smpt_close_serial_port(&device);
            }
    }


}








