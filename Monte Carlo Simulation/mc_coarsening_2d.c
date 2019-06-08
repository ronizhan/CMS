#include <stdio.h>													//used standard libraries
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "inputdat.h"												//created libraries
#include "setup.h"
#include "random.h"
#include "neigh.h"
#include "photo.h"
#include "evolution.h"

int main()
{
	int choice;
	
	siteSpin = (int *)malloc((nsp+1)*sizeof(int));					//store values of all siteSpins
	neighPos  = (int *)malloc((nNeighbor+1)*sizeof(int));			//store positions of all 8 neighbors for siteSpin of interest

	printf("Select one of the choices:\n");
	printf("1. Read data from existing vtk file\n");
	printf("2. Create random configuration of data\n");
	printf("\nYour choice: ");
	scanf("%d", &choice);											//User's choice of action
	

	if(choice == 1)													//read data from existing file
	{
		r = fopen(input_keyword, "r");								//pointer to read only file
		setup_init_micro(choice);									//copy values of siteSpins from reading file
		fclose(r);
	}
	
	else if(choice == 2)											//create set of random values
		setup_init_micro(choice);
	
	int i;															//number of Monte Carlo simulation
	for(i = 0; i <= maxMCS; i++)
	{
		if(i%1000 == 0)												//output 0th and every 1000th MCS
		{
			char mod_output_keyword[20], supplement[20];			//used to change the name of each output file 
			
			strcpy(mod_output_keyword, output_keyword);				//copy string value of output_keyword to mod_output_keyword
			sprintf(supplement, "%d.vtk", i);						//store string(number_of_simulation.vtk) in the supplement string variable
			strcat(mod_output_keyword, supplement);					//bind both strings to get destination file name
			
			w = fopen(mod_output_keyword, "w");						//pointer to write only file
			output_micro_vtk();										//store data in 
			fclose(w);
		}
		sweep_spinExch_Potts();										//do MCS
	}
			
	return 0;
}
