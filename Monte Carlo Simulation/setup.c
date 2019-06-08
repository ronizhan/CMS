#include <stdio.h>							//used standard libraries
#include <stdlib.h>
#include <time.h>
#include "inputdat.h"

#include "setup.h"							//created libraries

void setup_init_micro(int choice)			//choose between reading of exisiting input file or creating new set of random values
{
	if(choice == 1)							//read existing file
		read_micro_vtk();
	else if(choice == 2)					//create random siteSpin values
	{
		int i;
		for(i = 1; i <= nsp; i++)			//firstly assign -1 to all siteSpins 
		{
			siteSpin[i] = -1;
		}
		qRan(maxQ);							//randomly select siteSpins and assign random values in the range (1 to maxQ)
	}
}


void read_micro_vtk()						//read existing input file
{	
	int i = 1, line = 1;
	char ignore[1000];
	while(line <= firstLines)				//ignore first lines that do not contain siteSpin values
	{
		fgets(ignore, 1000, r);
		line++;
	}
	while(i <= nsp)							//save siteSpin values
	{
		fscanf(r, "%i", &siteSpin[i]);
		i++;
	}
}

