// proj1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h> 
#include <math.h>
#include <time.h>
//#include <stdio.h> //included in project's other part
//#include <malloc.h> //Говорят, что он нужен для маллока, но вроде бы stdlib.h уже достаточно для компиляции
//#include <wchar.h> //<tchar.h> is included in the project's other file
#include "common_func.h"
#include "generate_read_g.h"


double* generate_vect_sigma(int N, double sigma_init)
{
	double *vector_sigma;
	vector_sigma = (double*)calloc(N,sizeof(double));
	if (vector_sigma == NULL) {printf("HELLO: memory allocation error\n"); exit(-1);}
//	srand(time(NULL));
	for (int i=0; i<N; i++)
	{
		vector_sigma[i] = sigma_init;//(double)rand()/(500*RAND_MAX);//0.0005;//0.001;
	}
return vector_sigma;
}
double** gen_elig_exp(int N)
{
	double** eligibility_exp;
	eligibility_exp = (double**)calloc(2,sizeof(double*));
		if (eligibility_exp == NULL) {printf("HELLO: memory allocation error\n"); exit(-1);}
	eligibility_exp[0] = (double*)calloc(N,sizeof(double));
		if (eligibility_exp[0] == NULL) {printf("HELLO: memory allocation error\n"); exit(-1);}
	eligibility_exp[1] = (double*)calloc(N,sizeof(double));
		if (eligibility_exp[1] == NULL) {printf("HELLO: memory allocation error\n"); exit(-1);}
	for (int i = 0; i<N; i++) 
	{
		eligibility_exp[0][i] = 0;
		eligibility_exp[1][i] = 0;
	}
	return eligibility_exp;
}
double* generate_eligibility(int N)
{
	double* vector_e;
	vector_e = (double*)calloc(N,sizeof(double));
	if (vector_e == NULL) {printf("HELLO: memory allocation error\n"); exit(-1);}
	for (int i = 0; i<N; i++) 
	{
		vector_e[i] = 0;
	}
	return vector_e;
}
int eligibility(double** g, double* elig/*, double **eligibility_exp*/, int timestep, int N, int L)
{
	double Te1 = 10;
	double Te0 = 3;
	for (int i = 0; i<N; i++)
	{
		/*eligibility_exp[1][i] = eligibility_exp[1][i]*exp(-1/Te1) + g[timestep%L][i];
		eligibility_exp[0][i] = eligibility_exp[0][i]*exp(-1/Te0) + g[timestep%L][i];*/
		//elig[i] = (eligibility_exp[1][i] - eligibility_exp[0][i])/10;
		//elig[i] = elig[i]*exp(-1/Te) + g[timestep%L][i];
		elig[i] = g[timestep%L][i];
		//elig[i] = (i<30)?g[timestep%L][i]:g[timestep%L][i-30];
		//elig[i] = (g[timestep%L][i] == 0)? elig[i]*exp(-1/Te): g[timestep%L][i];
	}
	return 0;
}

// Function /chi(\tau = CSpikeTime)
double LTDP_ImitationFunction(double CSpikeTime)
{
	double PlasticityTime = 30;//msec, 10-100 msec
	
	//if (CSpikeTime < PlasticityTime) return -99;
	if (CSpikeTime < PlasticityTime) return -47;
	else return 1;
}
int changing_weights(double* sigma, double* vector_e, double CSpikeTime, int N, int L, double epsilon)
{
	for (int i = 0; i<N; i++)
	{
		sigma[i] = sigma[i] + epsilon*LTDP_ImitationFunction(CSpikeTime)*vector_e[i];
		if (sigma[i] < 0) {sigma[i] = 0; printf("zero weight %d ", i);getchar();}
		//sigma[i] = sigma[i]*(1 + epsilon*LTDP_ImitationFunction(CSpikeTime)*g[i]);
	}
	return 0;
}
bool LianaCellFiringFunction(double alpha_atm, double Purkinje, double& Liana_buf)
{
	double H = 300;
	double Tl = 20;//msec, 20-100 msec
	double beta = 1;
	/// bH + a !!!!!!
	//Liana_buf = Liana_buf*exp(-1/Tl) + alpha_atm + beta*Purkinje;
	Liana_buf = Liana_buf*0.4*0 + alpha_atm + beta*Purkinje;
	if (Liana_buf >= H) {Liana_buf = 0; return true;}
	else if (Liana_buf < H) return false;
	printf("AAAAAAAAAA!!!\n");
	exit(-1);
}
double alpha(int timestep,double a_amp, double a_period, int mode)
{
	double alpha_atm = 0;
	if ((timestep%(int)(500*a_period)) < (timestep%(int)(1000*a_period))) alpha_atm = 500*a_period - 
		(timestep%(int)(500*a_period));
	else if ((timestep%(int)(500*a_period)) == (timestep%(int)(1000*a_period))) alpha_atm = timestep%(int)(500*a_period);
	else {printf("Oo\n"); getchar(); exit(-1);}
	
	//alpha_atm in interval [0,2]+4 when a_period=2, a_amp = 2
	//alpha_atm = 50;//alpha_atm/500/a_period*a_amp+50;
	if (mode == 0) alpha_atm = 50;
	else if (mode == 1) alpha_atm = alpha_atm/500/a_period*a_amp+50;
	else {printf("alpha error\n"); getchar();exit(-1);}
	return alpha_atm;
}

int _tmain(int argc, _TCHAR* argv[])
{
	double** g; //PF firings vector
	int timestep; // timestep i++ = + 1 msec
	
	//PF synapces weights vector
	double *sigma, *vector_e;//, **eligibility_exp;
	double scalar_Purkinje_presynap, sigma_sum;
	//full time fo running
	int fulltime;// = 200000;//100000;//40000;

	//Purkinje summation window parameter
	double T_p = 20; //msec (while dt = 1 msec)
	
	double Liana_buf = 0;
	double CSpikeTime = 0;

	//initial Purkinje firing frequency
	double Purkinje = 0;

	//number of PF synapces on Purkinje cell
	int N;// = 2000;//1000;
	double epsilon;// = 0.000001;//0.000001;//0.0000001;
	int L;// = 1000;//2000; //lenght of "snake-in-a-box"
	//input_alpha(t): alpha-atm - static, alpha(timestep) - dynamic
	//double alpha_atm = 5;

	//read settings (N,L, alpha parameters) from file
	double a_amp, a_period, sigma_init;
	int gen_snake, alpha_mode;

	read_settings_file(N,L,a_amp,a_period, fulltime, gen_snake, epsilon, sigma_init, alpha_mode);
	
	//random numbers generator
	srand(time(NULL));
	vector_e = generate_eligibility(N);
	//eligibility_exp = gen_elig_exp(N);
	sigma = generate_vect_sigma(N, sigma_init);
	if (gen_snake == 1)g = generate_vect_g(N,L); //slow cause of snake/////// Write snake's file
	else if (gen_snake == 0) g = vector_g_from_file(N,L); //quick
	else if (gen_snake == 2) g = generate_random_g(N,L);
	else {printf("wrong 'gen_snake' value"); getchar();exit(-1);}

	FILE* myfile1, *myfile2, *myfile3, *myfile4, *myfile5;

	myfile1 = create_output_file("1");
	myfile2 = create_output_file("2");
	myfile3 = create_output_file("3");
	myfile4 = create_output_file("4");
	myfile5 = create_output_file("5");

	for (timestep = 0; timestep < fulltime; timestep++)
	{
		
		if (LianaCellFiringFunction(alpha(timestep,a_amp,a_period, alpha_mode), Purkinje, Liana_buf) == true) CSpikeTime = 0;
		eligibility(g, vector_e/*, eligibility_exp*/, timestep, N, L);
		changing_weights(sigma, vector_e, CSpikeTime, N, L, epsilon);
				
		//calculating of Purkinje output
		scalar_Purkinje_presynap = 0;
		sigma_sum = 0;
		for (int k = 0; k < N; k++)
		{
			scalar_Purkinje_presynap = scalar_Purkinje_presynap + sigma[k]*g[timestep%L][k];
			sigma_sum = sigma_sum + sigma[k];
		}

		//Purkinje = Purkinje*exp(-1/T_p)+scalar_Purkinje_presynap;
		Purkinje = Purkinje*0.5*0+scalar_Purkinje_presynap;
		if (timestep<200000)fprintf(myfile1, "%d %f %f %f %f %f\n",
			timestep, sigma[0], sigma_sum, Liana_buf, Purkinje, alpha(timestep, a_amp, a_period, alpha_mode));
		else if (timestep<400000)fprintf(myfile2, "%d %f %f %f %f %f\n",
			timestep, sigma[0], sigma_sum, Liana_buf, Purkinje, alpha(timestep, a_amp, a_period, alpha_mode));
		else if (timestep<600000)fprintf(myfile3, "%d %f %f %f %f %f\n",
			timestep, sigma[0], sigma_sum, Liana_buf, Purkinje, alpha(timestep, a_amp, a_period, alpha_mode));
		else if (timestep<800000)fprintf(myfile4, "%d %f %f %f %f %f\n",
			timestep, sigma[0], sigma_sum, Liana_buf, Purkinje, alpha(timestep, a_amp, a_period, alpha_mode));
		else if (timestep<1000000)fprintf(myfile5, "%d %f %f %f %f %f\n",
			timestep, sigma[0], sigma_sum, Liana_buf, Purkinje, alpha(timestep, a_amp, a_period, alpha_mode));
		else {printf("\ntimestep is out of range\n"); getchar();exit(-1);}

		CSpikeTime++;
	}

	fclose(myfile1);
	for (int i = 0; i<L; i++) free(g[i]);
	free(g);
	free(vector_e);
	fclose(myfile1); fclose(myfile2); fclose(myfile3); fclose(myfile4); fclose(myfile5);
	//free(eligibility_exp[1]);free(eligibility_exp[0]);free(eligibility_exp);
	free(sigma);

	return 0;
}

