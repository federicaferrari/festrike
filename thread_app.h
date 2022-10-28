#ifndef THREAD_APP_H
#define THREAD_APP_H
#include "shared_memory.h"
#include "string.h"
#include "string"

class thread_app
{
public:
    thread_app();
    shared_memory c;

    int count  =  0;
    double compute_simmetry_coefficients(double fsx, double fdx);
    void loop();
//    void write_fesbike_file();
//    void open_fesbike_file();
    bool change_mode = 0;
    std::string pilot_name;

    double coeff_simmetry1 = 1;
    double coeff_simmetry2 = 1;

};

#endif // THREAD_APP_H
