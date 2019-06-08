#include <stdio.h>							//used standard libraries
#include <stdlib.h>
#include <time.h>
#include "inputdat.h"

#include "random.h"							//created library


void qRan(int q)							//transform siteSpins from liquid to solid state
{
	long seed;
	int x, y, numRan;
	int count = 0;
	
	do										//change -1 to any positive value
	{
		seed = (long)time(NULL);			//create random number 
		x = (int )(xdim*ran3(&seed))+1;		//create x coordinate
		y = (int )(ydim*ran3(&seed));		//create y coordinate
		numRan = (int )(q*ran3(&seed))+1;	//create solid value in the range (1 to maxQ)
		
		if(siteSpin[y*xdim+x] == -1)		//if siteSpin is liquid
		{
			siteSpin[y*xdim+x] = numRan;	//change to created solid value 
			count++;
		}									
	}
	while(count <= solidMax);
}



double ran3(long *idum)				//generate uniform random number value
{
	static int inext,inextp;
	static long ma[56];
	static int iff=0;
	long mj,mk;
	int i,ii,k;

	if (*idum < 0 || iff == 0) { 
		iff=1;
		mj=labs(MSEED-labs(*idum)); 
		mj %= MBIG;
		ma[55]=mj;
		mk=1;
		for (i=1;i<=54;i++) {
			ii=(21*i) % 55;
			ma[ii]=mk;
			mk=mj-mk;
			if (mk < MZ) mk += MBIG;
			mj=ma[ii];
		}
		for (k=1;k<=4;k++)
			for (i=1;i<=55;i++) {
				ma[i] -= ma[1+(i+30) % 55];
				if (ma[i] < MZ) ma[i] += MBIG;
			}
		inext=0;
		inextp=31;
		*idum=1;
	}

	if (++inext == 56) inext=1;
	if (++inextp == 56) inextp=1;
	mj=ma[inext]-ma[inextp];
	if (mj < MZ) mj += MBIG; 
	ma[inext]=mj;
	return mj*FAC;
}

