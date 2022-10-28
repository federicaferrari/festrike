#include "thread_app.h"
#include "globalvariables.h"
#include "header.h"


using namespace std;

thread_app::thread_app()
{

}


//double thread_app::compute_simmetry_coefficients(double tfmedia_left, double tfmedia_right) {
//    if(tfmedia_left>tfmedia_right){
//        double delta= [(tfmedia_left-tfmedia_right)/tfmedia_left]*100;
//        if(delta>15){

//            simm_coeff[0]= delta/2;
//            simm_coeff[1]= -(delta/2);
//        }
//    }
//    else if(tfmedia_left<tfmedia_right){
//        double delta= [(tfmedia_right-tfmedia_left)/tfmedia_right]*100;
//        if(delta>15){
//            simm_coeff[1]= delta/2;
//            simm_coeff[0]= -(delta/2);

//       }
//   }
//    return simm_coeff;
//}

int soglia= 0;
double delta= 0.0;
vector<double> simm_coeff(2);

//vector<double> thread_app::compute_simmetry_coefficients(double fsx_med, double fdx_med) {




//    if(fsx_med>fdx_med){
//       delta= ((fsx_med-fdx_med)/fsx_med)*100;
//        if(delta>soglia){
//            simm_coeff[0]= delta/2;
//            simm_coeff[1]= -(delta/2);

//        }
//    }
//    else if(fsx_med<fdx_med){
//        delta= ((fdx_med-fsx_med)/fdx_med)*100;
//        if(delta>soglia){
//            simm_coeff[1]= delta/2;
//            simm_coeff[0]= -(delta/2);
//       }
//   }
//   return simm_coeff;
//}

double thread_app::compute_simmetry_coefficients(double fsx_med, double fdx_med) {
    soglia=0.2;
    double coeff_symm=0.0;
//    delta =(fsx_med/(fdx_med+fsx_med))-0.5;
//    if((delta>soglia)||(delta<-soglia)){
//        coeff_symm=delta;
    delta= abs(fsx_med-fdx_med)/(abs(fsx_med)+abs(fdx_med));
    if(delta>soglia){
    if (fsx_med>fdx_med){

       delta= abs(fsx_med-fdx_med)/(abs(fsx_med)+abs(fdx_med));
        coeff_symm=delta;
    }
    else {
        coeff_symm=-delta;
    }

 //   }
    return coeff_symm;
    }

}



