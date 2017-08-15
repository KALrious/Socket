//
//  process.c
//  
//
//  Created by jean gautier on 15/05/2016.
//
//

#include "process.h"

static int get_random (int max)
{
    double val;
    
    val = (double) max * rand ();
    val = val / (RAND_MAX + 1.0);
    
    return ((int) val);
}

int *process_image (char *tab)
{
    int tampon,i,j,k=0,p=0;
    
    for(i=0;i<10 ; i++)
    {
        for(j=i+1;j<10;j++)
        {
            if (tab[j] < tab[i])
            {
                tampon = tab[i];
                tab[i]= tab[j];
                tab[j]= tampon;
            }
        }
        
    }
    k = get_random(10);
    
    sleep(j);
    
    for(i=0; i<10;i++)
        printf("%d\t",tab[i]);
    printf("\naffichage après trie:\n");
    
    return(tab);
    
    
}