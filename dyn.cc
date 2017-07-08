#include "dyn.h"

void update_xv (Particle GP [], double U);
void update_ang(Particle GP[]);

//void get_SP(Particle GP[], double F_SP[][D]){
void get_SP(Particle GP[]){
    

    for (int i=0;i<N;i++){

        double e[D];
        e[0]=cos(GP[i].ang);
        e[1]=sin(GP[i].ang);

        for (int d=0;d<D;d++)
             GP[i].f[d]+=gam*v0*e[d]; // the angle will be updated as follows
    }

}



//void get_BM(Particle GP[], double F_BM[][D]){
void get_BM(Particle GP[]){

    // random generator    
    int seed=rand();  // don't forget renew the seed!
    mt19937   rng( seed );  // renew the seed! 
    normal_distribution<double> normal(0,1); //mean, std derivation:sigma   e^{-(x-m)**2/2*sigma**2}
    /****************************************/

    const double f0=sqrt(2*gam*T/h);

    for (int i=0;i<N;i++){

        double eta[D];
        eta[0]=normal(rng);
        eta[1]=normal(rng);

        for (int d=0;d<D;d++){
            GP[i].f[d]+=-gam*GP[i].vel[d]+f0*eta[d];
        }

    }

}




//get interaction between the probe and bath particles
void get_PB(Particle GP[], Particle& Probe){

// clean memory of the Probe
    Probe.f[0]=0;
    Probe.f[1]=0;
    Probe.tau=0;


    Probe.n=0;
    for (int i=0;i<N;i++){

        Particle bath=GP[i];
        bath.f[0]=0;
        bath.f[1]=0;
        bath.tau=0;

        Interaction(Probe, bath);  // get interaction force between the probe and N bath particles!
        
        for (int d=0;d<D;d++){
            GP[i].f[d]+=bath.f[d];  // force acting on the particle i from the probe.
        }
        GP[i].tau+=bath.tau;
   
        double fn=sqrt( pow(bath.f[0],2)+pow(bath.f[1],2) );
        if (fn>0)
           Probe.n++;

    }

}






/*************************************************************************************/
void Dyn(Particle GP[], Particle& Probe, double U){
  
    //clear force memory  
    for (int i=0;i<N;i++)
    for (int d=0;d<D;d++) GP[i].f[d]=0;
    
    for (int d=0;d<D;d++) Probe.f[d]=0;

    //get B-B interaction
    if (BB>0) get_Inter_force_B(GP);


    get_SP(GP); // get self-propelled force of the bath particles

    get_BM(GP); // get Brownian motion force 

    get_PB(GP, Probe); // get interaction between the probe and bath particles
    

    update_xv(GP,U);
    update_ang(GP);

}


// update (pos, vel)
//over-damped



void update_xv (Particle GP [], double U){

     void PB_particle (double x[]);

     double v[2]; v[0]=-U; v[1]=0;
     for (int i=0;i<N;i++){
            for (int d=0;d<D;d++){
                GP[i].vel[d]=(GP[i].f[d]/gam)+GP[i].vel[d]+v[d];
                GP[i].pos[d]+=GP[i].vel[d]*h;
            }
            PB_particle (GP[i].pos); // Periodical boundary condition
     }



}



void update_ang(Particle GP[]){

    // random generator    
    int seed=rand();  // don't forget renew the seed!
    mt19937   rng( seed ); 
    normal_distribution<double> normal(0,1); //mean, std derivation:sigma   e^{-(x-m)**2/2*sigma**2}
    /****************************************/




    for (int i=0;i<N;i++){

        GP[i].omg=normal(rng)*sqrt(2*Dr/h); //speed of the angle: \sqrt(2Dr)*Gaussian  (over-damped)
      
        GP[i].ang+=h*(GP[i].omg);
    }

}






/*================================PBC====================================================*/
void PB_particle (double x[]){

    double L[D]; L[0]=Lx; L[1]=Ly;
    for (int d=0;d<D;d++){
        x[d]=x[d]-(floor (x[d]/L[d]))*L[d];
    }

}
