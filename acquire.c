//
//  acquire.c
//  
//
//  Created by jean gautier on 13/05/2016.

//

#include "acquire.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>


sem_t mutex;

/* Fonction pour tirer un nombre au sort entre 0 et max. */
static int get_random (int max)
{
    double val;
    
    val = (double) max * rand ();
    val = val / (RAND_MAX + 1.0);
    
    return ((int) val);
}

void get_image(char *tab){
    int i=0,j=0;
    
    sem_init(&mutex, 0, 1);
    
    sem_wait(&mutex); /* initialisation semaphore */
    
    for(i=0;i<10;i++)
    {
        tab[i]=get_random(50);
    }
    
    for(i=0;i<10;i++)
    {
        printf("%d\t",tab[i]);
    
        
    }
    printf("\naffichage tableau apres acquisition\n");
    
    sem_post(&mutex);/* terminaison semaphore */
   
    
    
    j = get_random(5);
    sleep(j);
               
    
}

void acquire(){
    
    
}
