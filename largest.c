#include <limits.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "parking.h"

#ifndef MYLARGEST
TODO(USING THE SOLUTION largest.c NOT MY CODE)
#else

/*
 * largest
 *     find the vehicle with the largest number of
 *     tickets and largest fine in database
 *     and print it
 */
void
largest(void)
{
    struct vehicle *count = NULL; // vehicle with largest number of tickets
    struct vehicle *fine = NULL;  // vehicle with largest total fine

/* your code here */
    struct vehicle *vehptr = NULL;
   // struct ticket *ticptr = NULL;
    uint32_t lgfine = 0;
    uint32_t lgcount = 0;

    for(uint32_t i = 0; i<tabsz; i++){
	    vehptr = *(htable + i);
	//    ticptr=vehptr->head;
	    while(vehptr != NULL){
		if((vehptr->tot_fine)>=lgfine){
			lgfine = (vehptr->tot_fine);
    			fine = vehptr;
		}
		if((vehptr->cnt_ticket)>=lgcount){
			lgcount = (vehptr->cnt_ticket);
			count = vehptr;
		}
		vehptr = vehptr->next;
	    }
    }
    
    
    if ((count == NULL) || (fine == NULL)) {
        printf("Empty database\n");
        return;
    }
    printf("Most tickets Plate: %s, State: %s tickets: %u, total fine: $%u\n",
            count->plate, count->state, count->cnt_ticket, count->tot_fine);
    printf("Largest fine Plate: %s, State: %s tickets: %u, total fine: $%u\n",
            fine->plate, fine->state, fine->cnt_ticket, fine->tot_fine);
    return;
}
#endif
