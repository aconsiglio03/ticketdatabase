#include <limits.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "parking.h"
#include "hashdb.h"

#ifndef MYFREETICKETS
TODO(USING THE SOLUTION freetickets.c NOT MY CODE)
#else

/*
 * freetickets
 *      tears down the database freeing all allocated memory
 *      count the number of tickets freed in the database and
 *      print it out before returning
 *
 *      unsigned long cnt = 0UL
 *      printf("Total tickets freed: %lu\n", cnt);
 */
void
freetickets(void)
{
    int empty = 1; // set to zero when there is at least one vehicle in the database

    /*
     * walk down each chain
     */
	unsigned long cnt = 0UL;
	struct vehicle *vehptr;
	struct vehicle *delveh;
	struct ticket *ticptr;
	struct ticket *deltic;
      	vehptr = *(htable);
	for(uint32_t i = 0; i<tabsz; i++){
		vehptr = *(htable + i);
		while(vehptr != NULL){
			empty = 0;
			ticptr = vehptr->head;
			while(ticptr != NULL){
				deltic = &(*ticptr);
				*deltic = *ticptr;
				ticptr = ticptr -> next;
		//		free(deltic->summons);
			//	free(deltic->date);
			//	free(deltic->code);
		//		free(deltic->next);
				free(deltic);
				cnt++;
			}
			delveh =&(*vehptr);
			*delveh = *vehptr;
			vehptr = vehptr -> next;
		//	*delveh = NULL;
			free(delveh->state);
			free(delveh->plate);
		//	free(delveh->tot_fine);
	//		free(delveh->cnt_ticket);
		//	free(delveh->next);
		//	free(delveh->head);
			free(delveh);
			*(htable + i) = NULL;
		}
	}
	/*
     * remove all the tickets for all vehicles
     * on this chain
     */

    /*
     * free the vehicle
     */

    /*
     * chain is removed, update the htable entry
     */

    if (empty)
        printf("Empty Database\n");
    printf("Total tickets freed: %lu\n", cnt);
    return;
}
#endif
