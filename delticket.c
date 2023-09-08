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

#ifndef MYDELTICKET
TODO(USING THE SOLUTION delticket.c NOT MY CODE)
#else

/*
 * delticket
 *      remove ticket (summons) from the database
 *      look up the summons for a vehicle and pay it (remove the ticket) 
 *
 *      Find the vehicle by the state and plate. if not found return -1
 *
 *      convert the summ string to a long long int using
 *      using strtosumid. This long long int is how the summons number
 *      is stored in the database in struct ticket.
 *      After being converted you can use it find a summons id match
 *      in the linked list of tickets attached to the strcut vehicle.      
 *
 *      After you have the vehicle, find the summons on the ticket chain
 *      that matches the converted summons string (summid in the example)
 *      example:
 *        unsigned long long summid
 *        if (strtosumid(summ, &summid) != 0)
 *           return -1;
 *        now search the ticket chain to find that summons
 *        struct ticket *tptr;
 *        if (tptr->summons == summid)
 *          found it
 *           
 *      If found, delete it from the ticket chain. If the vehicle
 *      no longer has any tickets, then remove the vehicle from the hash chain
 *      Otherwise you must update the tot_fine and cnt_tickets fields in
 *      the struct vehicle so the are accurate after removing the summons
 *      Make sure to delete all space that malloc()'d 
 *
 * Inputs:
 *  plate   plate id string to be found
 *  state   state id string to be found
 *  summ    summon id string to be found
 *
 * returns 0 if ok -1 if not found or error
 */

int
delticket(char *plate, char *state, char *summ)
{
    unsigned long long summid;
	struct vehicle *ptr;

	
    /*
     * convert the summons string to a number
     */
    if (strtosumid(summ, &summid) != 0){
        return -1;
    }

	uint32_t hashval;
	hashval = hash(plate)%tabsz;
	struct ticket *ticptr;
	ptr = *(htable+hashval);
	//Keeps track of position of vehicle and ticket in chain for easier removal
	int count = 0;
	int ticcount = 0;

	if(ptr == NULL){
		return -1;
	}

	//Find vehicle
	while(strcmp(plate, ptr->plate)!=0 || strcmp(state, ptr->state)!=0){
		if(ptr->next == NULL){
			return -1;
		}
		ptr = ptr->next;
		count++;
	}

   /*
    * did we find the vehicle?
    */

    /*
     * find the ticket
     */
  	 ticptr = ptr->head;
	 if(ticptr == NULL){
		 return -1;
	 }
	 while(summid!=ticptr->summons){
		 if(ticptr->next == NULL){
			 return -1;
		 }
		 ticptr = ticptr->next;
		 ticcount++;
	 }
    /*
     * if ticket not found we are done
     */

    /*
     * update the summary fields and remove the ticket
     */
	(ptr->cnt_ticket)--;
	unsigned int ticfine = fineTab[ticptr->code].fine;
	ptr->tot_fine = (ptr->tot_fine)-ticfine;
	struct ticket *deltic;
	deltic = ptr->head;
	if(ticcount == 0){
		ptr->head = ticptr->next;
	}
	else{
		for(int i = 0; i<ticcount-1; i++){
			deltic = deltic->next;
		}
		deltic->next = ticptr->next;
	}
	free(ticptr);
	ticptr=NULL;
	
    /*
     * was this the last ticket for the vehicle?
     * if so, remove the vehicle from the hash chain
     */
	struct vehicle *delveh;
	delveh = htable[hashval];
	if(ptr->cnt_ticket==0){
		if(count == 0){
			htable[hashval] = ptr->next;
		}
		else{
			for(int i = 0; i<count-1; i++){
				delveh = delveh->next;
			}
			delveh->next = ptr->next;
		}
		free(ptr->state);
		free(ptr->plate);
		free(ptr);
		ptr=NULL;
	}
    return 0;
}
#endif
