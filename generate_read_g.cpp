#include "stdafx.h"
#include <stdlib.h> 
#include <math.h>
#include <time.h>
//#include "common_func.h"
#include "mauk.h"
double** generate_random_g(int N, int L)
{
	//Generate parallel fiber input g[i]
	double **vector_g;
	int counter = 0;
	FILE* myfile_snake;
	myfile_snake = fopen("snake","w");
	if(myfile_snake == NULL){puts("cannot open file");getchar();exit(-10);}

	vector_g = (double**)calloc(L,sizeof(double*));
	if (vector_g == NULL) {printf("HELLO: memory allocation error\n"); exit(-1);}

	for (int i=0; i<L; i++)
	{
		vector_g[i] = (double*)calloc(N,sizeof(double));
		if (vector_g[i] == NULL) {printf("HELLO: memory allocation error\n"); exit(-1);}
		for(int k = 0; k<N; k++)
		{
			if (0.7<((double)rand()/RAND_MAX)) vector_g[i][k] = 1;
			else vector_g[i][k] = 0;
			//vector_g[i][k] = 1;
			fprintf(myfile_snake, "%f\n",vector_g[i][k]);
		}

	}
	printf("vector_g has been generated\n");
	fclose(myfile_snake);
	return vector_g;
}
double** generate_vect_g(int N, int L)
{
	//Generate parallel fiber input g[i]
	double **vector_g;
	bool snake_retry_flag;
	int cycle_counter = 0;
	int p;//variable for what element change in next snake's step
	vector_g = (double**)malloc(L*sizeof(double*));
	if (vector_g == NULL) {printf("HELLO: memory allocation error\n"); exit(-1);}
	
	vector_g[0] = (double*)malloc(N*sizeof(double));
	if (vector_g[0] == NULL) {printf("HELLO: memory allocation error\n"); exit(-1);}
	int counter = 0;
	for(int k = 0; k<N; k++)
		{
			//vector_g[0][k] = floor((double)rand()/RAND_MAX); <----why doesn't work?
			if (0.9<((double)rand()/RAND_MAX)) vector_g[0][k] = 1;
			else vector_g[0][k] = 0;
			if (vector_g[0][k] == 1 ) counter++;
		}
	printf("number of 1s: %d\n",counter);

	for (int i=1; i<L; i++)
	{
		vector_g[i] = (double*)malloc(N*sizeof(double));
		if (vector_g[i] == NULL) {printf("HELLO: memory allocation error\n"); exit(-1);}
		
		// next vector for "snake-in-a-box"
		snake_retry_flag = true;
		cycle_counter = 0;
		while (snake_retry_flag)
		{
			for(int k = 0; k<N; k++)
			{
				if (i<1) {printf("ERROR\n"); getchar(); exit(-10);}
				vector_g[i][k] = vector_g[i-1][k];
			}
			p = -1;
			while (p == -1)
			{
				p = int(N*(double)rand()/RAND_MAX);
				if (vector_g[i][p] == 1) vector_g[i][p] = 0;
				else p = -1;
			}
			p = -1;
			while (p == -1)
			{
				p = int(N*(double)rand()/RAND_MAX);
				if (vector_g[i][p] == 0) vector_g[i][p] = 1;
				else p = -1;
			}
			
			snake_retry_flag = false;
			for(int n = 0;n<i;n++) if(distance(vector_g[n], vector_g[i], N)<2)snake_retry_flag = true;
			cycle_counter++;
			if (cycle_counter > 2*N) {printf(" %d bad snake\n",i); getchar(); exit(-1);}
		}
		
	}
	printf("vector_g has been generated ");

	FILE* myfile_snake;
	myfile_snake = fopen("snake","w");
	if(myfile_snake == NULL)
	{
		puts("\n cannot open file");
		getchar();
		exit(-10) ;
	}
	//double vector[6][6];
	for(int i = 0; i < L; ++i) 
		for (int k = 0; k<N; ++k)
		{
			fprintf(myfile_snake, "%f\n",vector_g[i][k]);
		}
	fclose(myfile_snake);
	printf("and saved\n");
return vector_g;
}
double** vector_g_from_file(int N, int L)
{
	FILE* myfile_snake;
	myfile_snake = fopen("snake","r");
	if(myfile_snake == NULL) 
	{
		puts("cannot open file"); getchar(); exit(-10) ;
	}
	double **vector_g;
	vector_g = (double**)malloc(L*sizeof(double*));
	if (vector_g == NULL) {printf("HELLO: memory allocation error\n"); exit(-1);}
	for (int i=0; i<L; i++)
	{
		vector_g[i] = (double*)malloc(N*sizeof(double));
		if (vector_g[i] == NULL) {printf("HELLO: memory allocation error\n"); exit(-1);}
		for (int k = 0; k<N; ++k)
		{
			fscanf(myfile_snake, "%lf",&vector_g[i][k]);
			//printf("%f\n",vector_g[i][k]);
		}
	}
	return vector_g;
}