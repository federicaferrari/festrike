#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <ostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <vector>
#include <numeric>
#include <string>
//#include <QtDebug>
//#include <QCoreApplication>
//#include <QtCore/QCoreApplication>
#include <thread>
#include <pthread.h>
#include <chrono>
#include <time.h>
#include <sys/time.h>
#include <termios.h>
#include <fcntl.h>
#include <getopt.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <fstream>
#include <libconfig.h++>
//#include <wiringPi.h>


#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32

# include <windows.h>

#define sleep(x) Sleep(1000 * (x))

#endif

using namespace std;

// SCIENCE HEADERS
#include "smpt_ll_client.h"
#include "smpt_client.h"
#include "smpt_ml_client.h"
#include "smpt_messages.h"
#include "smpt_packet_number_generator.h"
#include "smpt_ll_packet_validity.h"

#endif // HEADER_H
