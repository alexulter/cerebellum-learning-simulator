//common func
#include <stdio.h>
#include <tchar.h>

#include "stdafx.h"
#include <vector>

#include <iostream>			/////std::cout std::endl std::wofstream
//#include <fstream> /// std::wofstream T_equ;

double distance(double* v1, double* v2, int length);
int read_settings_file(int &N, int &L, double &a_amp, double &a_period, int &fulltime,
					   int &gen_snake, double &epsilon, double &sigma_init, int &alpha_mode);
FILE* create_output_file(char* ID);
//generate_g
double** generate_random_g(int N, int L);
double** generate_vect_g(int N, int L);
double** vector_g_from_file(int N, int L);
//main
double* generate_vect_sigma(int N, double sigma_init);
double** gen_elig_exp(int N);
double* generate_eligibility(int N);
int eligibility(double** g, double* elig/*, double **eligibility_exp*/, int timestep, int N, int L);
double LTDP_ImitationFunction(double CSpikeTime);
int changing_weights(double* sigma, double* vector_e, double CSpikeTime, int N, int L, double epsilon);
//double alpha(int timestep,double a_amp, double a_period, int mode, double alpha_min);

//std::vector<std::vector <unsigned int>>  ConvertG2Optimized(double **g, int L, int N);

class Purkinje
{
public:
	Purkinje();
	bool LoadSettings();
	void Run();
	void  ConvertG2Optimized();
	bool StepForwardOptimized();
	//thread
	HANDLE threadHandle;
	static UINT ThreadFunc(LPVOID param);
	VOID StartThreadFunc();
	////
	bool SynapticWeightsStep();
	~Purkinje();
	UINT timestep;
	double PurkinjeFreqPublic, Liana_Public, alpha_Public;
	virtual VOID Purkinje::ComputingThread(UINT i);
	int RunThread;
	double *out_var_1;
	double *out_var_2;
	double *out_var_3;
private:
	double Alpha();
	bool LianaCellFiringFunction();
	double** g;
	//std::vector<std::vector <unsigned int>> g_optimized;
	unsigned int ** g_halfop;
	double* sigma, *vector_e;//, **eligibility_exp;
	double scalar_Purkinje_presynap, sigma_sum;
	int fulltime;
	double T_p; //msec (while dt = 1 msec)
	double Liana_buf;
	double H;// = 300;
	double k_liana;// = 0;
	double k_purk;
	double beta;// = 1;
	int CSpikeTime;
	//initial Purkinje firing frequency
	double PurkinjeFreq;
	//number of PF synapces on Purkinje cell
	int N;
	double epsilon;// = 0.000001;//0.0000001;
	int L;// = 1000;//2000; //lenght of "snake-in-a-box"
	//read settings (N,L, alpha parameters) from file
	double a_amp, alpha_min, a_period, sigma_init;
	int gen_snake, alpha_mode, sigma_reset;
	//FILE* output_file;
	FILE *omyfile1, *omyfile2, *omyfile3, *omyfile4, *omyfile5;
	FILE *f_Tequ;
	int counter_tequ;
};

