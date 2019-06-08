#include <stdio.h>								//used standard libraries
#include <stdlib.h>
#include <time.h>

#include "inputdat.h"							//created libraries
#include "neigh.h"

double setup_neighbor(int x, int y)
{
	int a, b, c, d, e, f, g, xy, rem, quo;		//create important variables
	double sum = 0;								//variable for energy interfacial calculation
	int neigh[9];								//store values of neighbors of siteSpin of the interest
	
	xy = y*xdim+x;								//calculations
	rem = xy%xdim;								//reassessed x coordinate of the siteSpin
	quo = xy/xdim;								//reassessed y coordinate of the siteSpin

	neighPos[1] = (quo-(xdim-rem)/xdim)*xdim+rem+1;		//equation for neigh[1]
	neigh[1] = siteSpin[neighPos[1]];					
		
	a = quo+ydim-1-(xdim-rem)/xdim;						//equations for neigh[2]
	neighPos[2] = a%ydim*xdim+rem+1;
	neigh[2] = siteSpin[neighPos[2]];					
			
	b = (ydim-1+quo)*xdim+rem;							//equations for neigh[3]
	neighPos[3] = b%nsp+(nsp-abs(b-nsp))/nsp*nsp;
	neigh[3] = siteSpin[neighPos[3]];					
		
	c = (ydim-1+quo)*xdim+rem-1;						//equations for neigh[4]
	neighPos[4] = c%nsp+(xdim-abs(rem-1))/xdim*xdim;
	neigh[4] = siteSpin[neighPos[4]];					
		
	d = quo*xdim+rem-1;									//equations for neigh[5]
	neighPos[5] = d+(xdim-d%xdim)/xdim*xdim;
	neigh[5] = siteSpin[neighPos[5]];					
		
	e = (quo+1)*xdim+rem-1;								//equations for neigh[6]
	neighPos[6] = e%nsp+(xdim-abs(rem-1))/xdim*xdim;
	neigh[6] = siteSpin[neighPos[6]];					
		
	f = (quo+1)*xdim+rem;								//equations for neigh[7]
	neighPos[7] = f%nsp+(nsp-f%nsp)/nsp*nsp;
	neigh[7] = siteSpin[neighPos[7]];					
		
	g = (quo+1)*xdim+rem+1-(xdim-rem)/xdim*xdim;		//equations for neigh[8]
	neighPos[8] = g%nsp+(nsp-g%nsp)/nsp*nsp;
	neigh[8] = siteSpin[neighPos[8]];					

	int i;
	for(i = 1; i <= 8; i++)
	{
		if((siteSpin[xdim*quo+rem] < 0 && neigh[i] > 0) || (siteSpin[xdim*quo+rem] > 0 && neigh[i] < 0))		//if the siteSpin and its neighbor have opposite signs
			sum = sum + Ehi;																					//add heterointerfacial energy
			
		else if(siteSpin[xdim*quo+rem] > 0 && neigh[i] > 0 && siteSpin[xdim*quo+rem] != neigh[i])		//if the siteSpin and its neighbor are solids and have different values
			sum = sum + Egb;
	}
	return sum;
}
