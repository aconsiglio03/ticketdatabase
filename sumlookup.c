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

#ifndef MYSUMLOOKUP
TODO(USING THE SOLUTION sumlookup.c NOT MY CODE)
#else

/*
 * summlookup
 *     find the vehicle with a specified summons number
 * Input:
 *      summ: string of summons number
 * returns:   a pointer to the vehicle
 */
struct vehicle *
sumlookup(char *summ)
{
    unsigned long long summid;
    struct vehicle *vehptr;
    struct ticket *ticptr;

    if (strtosumid(summ, &summid) != 0) {
        fprintf(stderr, "%s:sumlookup bad summons number:%s\n", argv0, summ);
        return NULL;
    }
    for(uint32_t i =0; i<tabsz; i++){
    	vehptr = *(htable+i);
	while(vehptr != NULL){
		ticptr = vehptr->head;
		while(ticptr != NULL){
			if(ticptr->summons == summid){
				return vehptr;
			}
			ticptr = ticptr->next;
		}
		vehptr = vehptr->next;
	}
    }



/* your code here */
    return NULL; //delete this when you write your code
}
#endif
