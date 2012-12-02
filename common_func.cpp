#include <stdlib.h> 
#include <math.h>
#include <time.h>
#include "stdafx.h"
#include <string.h>

//	if(a==0)
//		b=c
//	else
//		b=d
//		b=(a==0)?c:d;

double distance(double* v1, double* v2, int length)
{
	double d = 0;
	for(int i = 0; i<length; i++) 
		d += abs(v1[i]-v2[i]);
	//{d += abs(v1[i]-v2[i]); if (v1[i] != v2[i]) printf("%f %f %f\n", v1[i], v2[i], abs(v1[i]-v2[i]));}
	//printf("d= %f\n",d);
return d;
}

FILE* create_output_file(char* ID)
{
	FILE *myfile;
	char line[20] = "out";
	strcat(line,ID);
	strcat(line,".txt");
	myfile = fopen(line,"w");
         if(myfile == NULL)
         {
               puts("cannot open file");
			   getchar();
               exit(-10) ;
         }
	return myfile;
}