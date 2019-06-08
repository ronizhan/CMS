#include <stdio.h>										//used standard libraries
#include <stdlib.h>
#include <time.h>
#include "inputdat.h"

#include "photo.h"										//created library

void aux_function()										//write auxiliary information (to be readable by paraview program) to the output vtk file 
{
	int i;
	
	fputs("# vtk DataFile Version 2.0\n data set from 2dmcgg\nASCII\nDATASET RECTILINEAR_GRID\nDIMENSIONS ", w);
	fprintf(w, "%d %d %d\n", xdim+1, ydim+1, zdim+1);
	fputs("X_COORDINATES   ", w);
	fprintf(w, "%d", xdim+1);
	fputs("   Float\n", w);
	
	for(i = 0; i <= xdim; i++)
	{
		fprintf(w, "%8.3f\n", (float)i);
	}
	
	fputs("Y_COORDINATES   ", w);
	fprintf(w, "%d", ydim+1);
	fputs("   Float\n", w);
	
	for(i = 0; i <= ydim; i++)
	{
		fprintf(w, "%8.3f\n", (float)i);
	}
	
	fputs("Z_COORDINATES   ", w);
	fprintf(w, "%d", zdim+1);
	fputs("   Float\n", w);
	
	for(i = 0; i <= zdim; i++)
	{
		fprintf(w, "%8.3f\n", (float)i);
	}
	
	fputs("CELL_DATA ", w);
	fprintf(w, "%d\n", nsp);
	fputs("SCALARS GrainIDs int 1\n", w);
	fputs("LOOKUP_TABLE default\n", w);
}


void output_micro_vtk()				//print values of siteSpins to the output file
{
	int j = 1;
	
	aux_function();					//apply above function
	while(j <= nsp)
	{
		fprintf(w, "%d	", siteSpin[j]);
		if(j%xdim == 0)
			fprintf(w, "\n");
		j++;
	}
}
