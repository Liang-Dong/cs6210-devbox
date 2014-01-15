#include <omp.h>
#include "gtmp.h"

/*
    From the MCS Paper: A sense-reversing centralized barrier

    shared count : integer := P
    shared sense : Boolean := true
    processor private local_sense : Boolean := true

    procedure central_barrier
        local_sense := not local_sense // each processor toggles its own sense
	if fetch_and_decrement (&count) = 1
	    count := P
	    sense := local_sense // last processor toggles global sense
        else
           repeat until sense = local_sense
*/


static int P;
static int count;
static int sense;



void gtmp_init(int num_threads){
  P = num_threads;
  count = num_threads;
  sense = 1;
}

void gtmp_barrier(){
  int local_sense;

  /* Replaces the line 
  
        local_sense := not local_sense // each processor toggles its own sense
     
     from the paper.  Since sense == local_sense until all
     threads have hit the barrier, this is equivalent.
  */
  local_sense = !sense;

  if (1 == __sync_fetch_and_sub(&count, 1)){
    count = P;
    sense = local_sense;
  }
  else
    while( sense != local_sense);
}

void gtmp_finalize(){
  return;
}
