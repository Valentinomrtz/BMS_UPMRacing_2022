/* 
 * Balance Control File
 * Application Layer
 */


#include "main_config.h"

#include "balance_control.h"
#include "slave_comm.h"
/* Apply balancing to the cells that need it, if Balance Mode is active*/
void balance_control(bms* bms){
    int i,j, cont=1;
    check_cells(bms);
    if(bms->bms_mode == BALANCE){
        if(bms->bcount == 0){
            slave_cell_balancing(0,0);           
        }  
        for(i=0;i<N_SLAVES;++i){
            for(j=0;j<N_CELLS;++j){
                if(bms->bcell[i][j] == 1){
                    cont++;
                    if (cont<=3) {
                        slave_cell_balancing(i+1,j+1);
                    }
                    else {
                        if (i<N_SLAVES-1) {
                            i++;
                            j=0;
                            cont=1;
                        }   
                    }
                }
            }
        }
        bms->bcount = bms->bcount + 1 ;
        if(bms->bcount == MAX_CYCLE_BALANCE){
            bms->bcount = 0;          
        }  
    }
    else{
        slave_cell_balancing(0,0);
        bms->bcount = 0;
    } 
}
/* Check which cells need to be balanced depending on the voltage difference*/
void check_cells(bms* bms){
    int i,j,k;
    for(i=0; i<N_STACKS; ++i){
        for(j=0; j<SLAVES_PER_STACK; ++j){
            for(k=0; k < N_CELLS - bms->maskcell[bms->mstack[i][j]]; ++k){
                if((bms->vcell[bms->mstack[i][j]][k] - bms->vminstack[i])*0.1 > MAX_CELL_DIFF_BALANCE){
                    bms->bcell[bms->mstack[i][j]][k] = 1;
                }else{
                    bms->bcell[bms->mstack[i][j]][k] = 0;
                }
            }
        }
    }
    /*for(i=0;i<N_SLAVES;++i){
        for(j=0;j<N_CELLS;++j){
            if((bms->vcell[i][j]- bms->vmin[i])*0.1 > MAX_CELL_DIFF_BALANCE){
                bms->bcell[i][j] = 1;
            }else{
                bms->bcell[i][j] = 0;                
            }    
        }   
    }    */
}
