#ifndef __PARA_H_INCLUDED__

#define __PARA_H_INCLUDED__


//#include "Memory.h"

/*---------------------------------------------------------*/
#define D 2       //dimension

#define phi 0  // packing fraction


#define Lx 128     //Sys size Lx*Ly
#define Ly 128


//#define N int(phi*Lx*Ly/Pi)     //particle number

#define N 10000000

#define rho (N/(Lx*Ly-Pi*0.25))

//#define rho (N/(Lx*Ly))

#define BB  0 //0: no interaction between bath particles;   1: interactio between bath particles




//#define N 4     //particle number
//#define Lx 6    //Sys size Lx*Ly
//#define Ly 6

#define L_box 4   //small box size for neigbor list

#define R 0.5       // particle size

#define K 200     // Spring const

#define gam 1 //100//10//10 //100 //solvent friction coefficient
#define T   0 //100//1//10//100      // temperature

#define h  0.001          // time step

#define running_length  10  // running time (seconds)
//#define running_length  1  // running time (seconds)

//#define running_time 1000

//#define Dr  1000      //rotational diffusion
//#define v0 0.001

#define Dr  0   //rotational diffusion
#define v0  1

#define mu  0       //friction coefficient


#define Pi 3.1415926

//#define type "O"  //over-damped dynamics
//#define type "U" //under-damped dynamics






















/*---------------------------------------------------------*/

//1.58489 2.51189 3.98107 6.30957

//#define U   1//6.30957//100      //pulling velocity
//#define nd 1 //10     //loop of ic

#endif
