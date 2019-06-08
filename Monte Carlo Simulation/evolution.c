#include <stdio.h>												//used standard libraries
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "inputdat.h"											//created libraries
#include "evolution.h"
#include "neigh.h"
#include "random.h"

void sweep_spinExch_Potts()										//do MCS
{
	int x1, y1, x2, y2, m;
	int temp[2], neighRan;
	double enOld = 0, enNew = 0, enDif;
	long seed;
	
	int count = 1;
	do
	{
		seed = (long )time(NULL);								//create random seed
		x1 = (int )(xdim*ran3(&seed))+1; 						//create x coordinate of the first siteSpin
		y1 = (int )(ydim*ran3(&seed)); 							//create y coordinate of the first siteSpin
		temp[0] = siteSpin[y1*xdim+x1];							//store value of the first siteSpin in the temp[0]
		enOld = enOld + setup_neighbor(x1, y1);					//calculate interfacial energy of the first siteSpin with its neighbors
		
		neighRan = (int )(nNeighbor*ran3(&seed))+1;				//number of the first siteSpin's neighbor(second siteSpin)
		m = neighPos[neighRan]%xdim;							//variable for calculations
		x2 = m+(xdim-m)/xdim*xdim;								//x coordinate of the second siteSpin
		y2 = (neighPos[neighRan]-x2)/xdim;						//y coordinate of the second siteSpin
		temp[1] = siteSpin[y2*xdim+x2];							//store value of the first siteSpin in the temp[1]
		enOld = enOld + setup_neighbor(x2, y2) - Ehi;			//sum of interfacial energies for two adjacent siteSpins
		
		if((temp[0] < 0 && temp[1] > 0) || (temp[0] > 0 && temp[1] < 0))	//if siteSpins from opposite phases, proceed
		{
			if(temp[0] > temp[1])											//if first sitespin is solid
			{
				siteSpin[y1*xdim+x1] = temp[1];								//first siteSpin now liquid
				siteSpin[y2*xdim+x2] = (int )(maxQ*ran3(&seed))+1;			//second siteSpin receives new random solid value 
			}
			else if(temp[0] < temp[1])										//if first sitespin is liquid
			{
				siteSpin[y1*xdim+x1] = (int )(maxQ*ran3(&seed))+1;			//first siteSpin receives new random solid value
				siteSpin[y2*xdim+x2] = temp[0];								//first siteSpin now liquid
			}
			
			enNew = enNew + setup_neighbor(x1, y1) + setup_neighbor(x2, y2) - Ehi;		//calculate interfacial energies of changed siteSpins
			enDif = enNew - enOld;														//calculate eenrgy difference btw final and initial states
			
			if(enDif > 0)													//if energy difference is more than 0, do Metropolis algorithm
			{
				double z;
				z = ran3(&seed);											
				if(exp(-enDif/kT) < z)										//if exp value less than random number, return initial siteSpin values
				{
					siteSpin[xdim*y1+x1] = temp[0];
					siteSpin[xdim*y2+x2] = temp[1];
				}
																			//if exp value more or equal to random number, proceed with new siteSpin values 
			}
		}
		
		enOld = 0;															//reset energy values to 0
		enNew = 0;
		enDif = 0;
		
		count++;
	}
	while(count <= nsp);
}
