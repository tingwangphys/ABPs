#include "interaction.h"



void min_dist(double r12[]);


/*=====================================================================================*/
// repulsive spring interaction:  -k (R1+R2-r12) for overlap
/*=====================================================================================*/
void Interaction (Particle &p1, Particle &p2){

    double r12[D]; for (int d=0;d<D;d++) r12[d]=(p1.pos[d]-p2.pos[d]);
    min_dist(r12);    // ! minimum image criterion
    double abs_r12=sqrt( pow(r12[0],2) + pow(r12[1],2) );
    double dr=abs_r12-(p1.r+p2.r);
    double f[D];

    if (dr<0){
        for (int d=0;d<D;d++)  {f[d]=-K*dr*(r12[d]/abs_r12); } // force acting on p1
        {p1.label=1; p2.label=1;} // labled if interacted
    }
    else
        for (int d=0;d<D;d++)  {f[d]=0; }

    for (int d=0;d<D;d++)
        {p1.f[d]=p1.f[d]+f[d]; p2.f[d]=p2.f[d]-f[d];} // add interaction between p1 and p2

}
/*=====================================================================================*/


/*=====================================================================================*/
// check min_dist due to Periodical boundary condition
/*=====================================================================================*/
void min_dist(double r12[]){

    // ! minimum image criterion
    double L[D]; L[0]=Lx; L[1]=Ly;
    for (int d=0;d<D;d++){
        r12[d]=r12[d]-int(r12[d]/(L[d]*0.5))*L[d];// ensure distance no larger than L/2;
    }

}
/*=====================================================================================*/
