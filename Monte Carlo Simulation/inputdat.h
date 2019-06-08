#define nNeighbor 8							//number of neighbors for each siteSpin

#define xdim 300							//dimensions of the working space
#define ydim 300							//...
#define zdim 1								//...

#define firstLines (xdim+ydim+zdim+14)		//first lines of input vtk file (include strings and cell dimensions)

#define nsp (xdim*ydim*zdim)				//total number of siteSpins

#define maxQ 100							//number of solid variations

#define dx 1.0								//single pixel dimensions
#define dy 1.0								//...
#define dz 1.0								//...


#define solidFrac 0.7						//fraction of solid pixels in the system
#define solidMax (solidFrac*nsp)			//number of solid pixels in the system

#define input_keyword "abc.vtk"				//input file
#define output_keyword "181203_2dmcc_"		//part of output file's name 

#define MBIG 1000000000						//constants for function ran3
#define MSEED 161803398						//...
#define MZ 0								//...
#define FAC (1.0/MBIG)						//...

#define kT 1.2								//temperature representing variable
#define Egb 2.0								//grain boundary interfacial energy
#define Ehi 0.8								//heterointerfacial energy

#define maxMCS 10000						//number of MCSs

int *siteSpin;								//pointer to the set of siteSpin values
int *neighPos;								//pointer to the set of neighbors of siteSpin of interest
FILE *r;									//pointer to read file
FILE *w;									//pointer to write file
