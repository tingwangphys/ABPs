// get interaction of N particles by the neibor-boxes methods.
#include "box.h"

//Memory *memory;  // using Memory.cc


const int NBx= ceil(1.0*Lx/L_box);
const int NBy= ceil(1.0*Ly/L_box);

void PB_box (int &i,int &j);



void get_Box_chain (Particle GP[], vector< vector<int> > &GB );

void get_Box_chain (Particle GP[], vector< vector<int> > &GB);
void Inter_same_box(int i, int j, vector< vector<int> > &GB, Particle GP[]);
void Inter_neigbor_box(int i, int j, vector< vector<int> > &GB, Particle GP[]);

/*
void get_Box_chain (Particle GP[], int GB[][NBy]);
void Inter_same_box(int i, int j, int GB[][NBy], Particle GP[]);
void Inter_neigbor_box(int i, int j, int GB[][NBy], Particle GP[]);
*/



void get_Inter_force_B(Particle GP[]) {

    //clean force memory
    for (int i=0;i<N;i++) for (int d=0;d<D;d++)
       {   GP[i].f[d]=0;
        GP[i].tau=0;}
    

    //interaction between bath particles
      
     //  int **GB;
     //  GB=memory->create_2d_int(NBx,NBy);
     
      vector< vector<int> > GB( NBx, vector<int> (NBy) );
        //int GB[NBx][NBy];


      /*
      int **GB = new int*[NBx];
      for(int i = 0; i < NBx; ++i) {
         GB[i] = new int[NBy];
      }
      */



        for (int i=0;i<NBx;i++)
        for (int j=0;j<NBy;j++)
            GB[i][j]=-1;

        //get box chain
        get_Box_chain (GP,GB);


        for (int j=0;j<NBx;j++) for (int i=0;i<NBy;i++){
            Inter_same_box(i, j, GB, GP);  // in the same box
             if (NBx>1) Inter_neigbor_box(i, j,GB,GP); // neigbor   (i+1,j) (i-1,j+1),(i,j+1),(i+1,j+1)
        }




     
        /*
        for(int i = 0; i < NBx; ++i) {
            delete [] GB[i];
        }
        delete [] GB;
        */

        //--------------------------------------
     //   memory->destroy_2d_int(GB);
        //--------------------------------------




    /*
    //interactions between the probe and bath particles
    for (int d=0;d<D;d++) Probe.f[d]=0;
    for (int i=0;i<N;i++){
        Interaction(Probe, GP[i]);
        //if (GP[i].f[0]!=0) cout<<i<<"\t"<<GP[i].f[0]<<endl;
    }

    int i=0;
    if (GP[i].f[0]!=0) cout<<i<<"\t"<<GP[i].f[0]<<endl;

    */


}


/*========================================Neibor-box========================================*/

// get the location of each particle in the boxes with chain structure
void get_Box_chain (Particle GP[], vector< vector<int> > &GB ){
//void get_Box_chain (Particle GP[], int GB[][NBy]){



    // empty boxes
    for (int i=0;i<NBx;i++)
    for (int j=0;j<NBy;j++)
        GB[i][j]=-1;


    for (int i=0;i<N;i++)
        GP[i].next=-1;

    // clean force in the memory
    for (int i=0;i<N;i++)
    for (int d=0;d<D;d++){
        GP[i].f[d]=0;
    }


    double L0=Lx*1.0/NBx;
    for (int i=N-1;i>-1;i--){
        int n0,n1;
        n0=int (GP[i].pos[0]/L0);
        n1=int (GP[i].pos[1]/L0);
        GP[i].next=GB[n0][n1];
        GB[n0][n1]=i;
    }


}
/*------------------------------------------------------------------------------------*/

//void Inter_same_box(int i, int j, int GB[][NBy], Particle GP[]){
void Inter_same_box(int i, int j, vector< vector<int> > &GB, Particle GP[]){
//void Inter_same_box(int i, int j, int GB[][NBy], Particle GP[]){

    int k = GB[i][j];

  //  cout<<"("<<i<<" , "<<j<<")"<<"****************"<<endl<<endl;
    while (k !=-1 ){
        int l=GP[k].next;
        while (l !=-1 ){
            //cout<<"the same box \t ("<<k<<" , "<<l<<")"<<endl;
            Interaction(GP[k], GP[l]);
            l=GP[l].next;
        }
        k=GP[k].next;
    }

}


void Inter_neigbor_box(int i, int j, vector< vector<int> > &GB, Particle GP[]){
//void Inter_neigbor_box(int i, int j, int GB[][NBy], Particle GP[]){

    int k = GB[i][j];

    //neibor (i+1,j)
    while (k !=-1 ){
        int n0=i+1, n1=j;
        PB_box(n0,n1);
        int l=GB[n0][n1];
        while (l !=-1 ){
            //cout<<"neibor ("<<n0<<","<<n1<<")\t("<<k<<" , "<<l<<")"<<endl;
            Interaction(GP[k], GP[l]);
            l=GP[l].next;
        }
        k=GP[k].next;
    }


    //neibors (i-1,j+1),(i,j+1),(i+1,j+1)
    for (int di=-1;di<=1;di++){
        k = GB[i][j];
        while (k !=-1 ){
            int n0=i+di, n1=j+1;
            PB_box(n0,n1);

            int l=GB[n0][n1];
            while (l !=-1 ){
                //cout<<"neibor ("<<n0<<","<<n1<<")\t("<<k<<" , "<<l<<")"<<endl;
                Interaction(GP[k], GP[l]);
                l=GP[l].next;
            }
            k=GP[k].next;
        }
    }


}
/*=====================================================================================*/


/*================================PBC====================================================*/
void PB_box (int &i,int &j){

    i=i-floor(i*1.0/NBx)*NBx;
    j=j-floor(j*1.0/NBy)*NBy;

}
