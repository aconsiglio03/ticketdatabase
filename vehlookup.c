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

#ifndef MYVEHLOOKUP
TODO(USING THE SOLUTION vehlookup.c NOT MY CODE)
#else

/*
 * vehiclelookup
 *          look for vehicle in the database
 *          vehicle must match both plate and state strings
 * args
 *  plate   plate id string to be found
 *  state   state id string to be found
 *
 * returns  pointer to vehicle if found NULL otherwise
 */

struct vehicle *
vehiclelookup(char *plate, char *state)
{
   
    	struct vehicle *ptr;
	uint32_t hashval;
	hashval = hash(plate) % tabsz;
	ptr = *(htable+hashval);

	if(ptr == NULL){
		return NULL;
	}
	while(strcmp(plate, ptr->plate)!=0 || strcmp(state, ptr->state)!=0){
		if(ptr->next == NULL){
			return NULL;
		}
		ptr = ptr->next;
	}
	return ptr;
}
#endif
