#include "stdafx.h"
#include <stdlib.h> 
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <tchar.h>
//#include <stdio.h> //included in project's other part
//#include <malloc.h>
//#include <wchar.h> //<tchar.h> is included in the project's other file

//#include "common_func.h"
//#include "generate_read_g.h"
#include "mauk.h"

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
bool Purkinje::LianaCellFiringFunction()
{
	//double Tl = 20;//msec, 20-100 msec -> moved to k_liana in LoadedOptions
	//double alpha_atm = alpha(timestep,a_amp,a_period, alpha_mode, alpha_min);
	/// bH + a !!!!!!
	//Liana_buf = Liana_buf*exp(-1/Tl) + alpha_atm + beta*Purkinje;
	Liana_buf = Liana_buf*k_liana + Alpha() + beta*PurkinjeFreq;
	if (Liana_buf >= H) {Liana_buf = 0; return true;}
	else if (Liana_buf < H) return false;
	printf("AAAAAAAAAA!!!\n");
	exit(-1);
}

double Purkinje::Alpha()
{
	double alpha_atm = 0;
	if ((timestep%(int)(500*a_period)) < (timestep%(int)(1000*a_period))) alpha_atm = 500*a_period - 
		(timestep%(int)(500*a_period));
	else if ((timestep%(int)(500*a_period)) == (timestep%(int)(1000*a_period))) alpha_atm = timestep%(int)(500*a_period);
	else {printf("Oo\n"); getchar(); exit(-1);}
	
	//alpha_atm in interval [0,2]+4 when a_period=2, a_amp = 2
	//alpha_atm = 50;//alpha_atm/500/a_period*a_amp+50;
	if (alpha_mode == 0) alpha_atm = alpha_min; //0;//50;
	else if (alpha_mode == 1) alpha_atm = alpha_atm/500/a_period*a_amp+alpha_min;//50;
	else {printf("alpha error\n"); getchar();exit(-1);}
	return alpha_atm;
}
bool Purkinje::LoadSettings()
{
	FILE* myfile;
         myfile = fopen("settings.txt","r");
         if(myfile == NULL)
		 {
               puts("cannot open settings file"); getchar(); return false; exit(-10);
         }
		 char buffer_string[20];
		 fscanf(myfile, "%s", buffer_string);
		 printf("reading %s\n", buffer_string);
		 fscanf(myfile, "%d",&N);
 		 fscanf(myfile, "%s", buffer_string);
		 printf("reading %s\n", buffer_string);
		 fscanf(myfile, "%d",&L);
		 fscanf(myfile, "%s", buffer_string);
		 printf("reading %s\n", buffer_string);
		 fscanf(myfile, "%lf",&a_amp);
		 fscanf(myfile, "%s", buffer_string);
		 printf("reading %s\n", buffer_string);
		 fscanf(myfile, "%lf",&alpha_min);
		 fscanf(myfile, "%s", buffer_string);
		 printf("reading %s\n", buffer_string);
		 fscanf(myfile, "%lf",&a_period);
		 fscanf(myfile, "%s", buffer_string);
		 printf("reading %s\n", buffer_string);
		 fscanf(myfile, "%d",&fulltime);
		 fulltime = fulltime*1000;
		 fscanf(myfile, "%s", buffer_string);
		 printf("reading %s\n", buffer_string);
		 fscanf(myfile, "%d",&gen_snake);
		 fscanf(myfile, "%s", buffer_string);
		 printf("reading %s\n", buffer_string);
		 fscanf(myfile, "%lf",&epsilon);

		 fscanf(myfile, "%s", buffer_string);
		 printf("reading %s\n", buffer_string);
		 fscanf(myfile, "%lf",&H);
		 fscanf(myfile, "%s", buffer_string);
		 printf("reading %s\n", buffer_string);
		 fscanf(myfile, "%lf",&k_liana);
		 fscanf(myfile, "%s", buffer_string);
		 printf("reading %s\n", buffer_string);
		 fscanf(myfile, "%lf",&k_purk);
		 fscanf(myfile, "%s", buffer_string);
		 printf("reading %s\n", buffer_string);
		 fscanf(myfile, "%lf",&beta);

		 fscanf(myfile, "%s", buffer_string);
		 printf("reading %s\n", buffer_string);
		 fscanf(myfile, "%lf",&sigma_init);
		 fscanf(myfile, "%s", buffer_string);
		 printf("reading %s\n", buffer_string);
		 fscanf(myfile, "%d",&alpha_mode);
		 		 fscanf(myfile, "%s", buffer_string);
		 printf("reading %s\n", buffer_string);
		 fscanf(myfile, "%d",&sigma_reset);
		 fclose(myfile);
		 printf("loaded values ->\n N %d L %d \n a_amp %f alpha_min %f a_period %f \n fulltime %dsec gen_snake %d\n",
			 N,L,a_amp, alpha_min, a_period, fulltime/1000, gen_snake);
		 printf(" epsilon %f H %f k_liana %f f_purk %f \n beta %f sigma_init %f alpha_mode %d\n",
			 epsilon, H, k_liana, k_purk, beta, sigma_init, alpha_mode);
		 printf(" sigma_reset %d\n",
			 sigma_reset);
	return true;
}
Purkinje::Purkinje()
{
	RunThread = 1;
	T_p = 20; //msec (while dt = 1 msec)	//Purkinje summation window parameter
	Liana_buf = 0;
	CSpikeTime = 1000; //not 0 to avoid first Liana spike ghost
	PurkinjeFreq = 0; //initial Purkinje firing frequency
	//epsilon = 0.000001;//0.0000001;
	if (!LoadSettings()) exit(-20);//read_settings_file(N,L,a_amp,a_period, fulltime, gen_snake);
	//	read_settings_file(N,L,a_amp,a_period, fulltime, gen_snake, epsilon, sigma_init, alpha_mode);
	srand(time(NULL));
	vector_e = generate_eligibility(N);
//	eligibility_exp = gen_elig_exp(N);
	sigma = generate_vect_sigma(N, sigma_init);//	sigma =  generate_vect_sigma(N);
	if (gen_snake == 1) g = generate_vect_g(N,L); //slow cause of snake/////// Write snake's file
	else if (gen_snake == 0) g = vector_g_from_file(N,L); //quick
	else if (gen_snake == 2) g = generate_random_g(N,L);
	else {printf("wrong 'gen_snake' value"); getchar();exit(-1);}
	
	//Optimization of g->g_optimized
	ConvertG2Optimized();

	//printf("snake OK\n");
	timestep = 0;
	//f_Tequ.open(L"Tequ.txt");
	f_Tequ = fopen("Tequ.txt","w");
	counter_tequ = 0;
	if(f_Tequ == NULL){puts("cannot open file");getchar();exit(-10);}
	//output_file = fopen("out.txt","w");
	//if(output_file == NULL)
	//{
	//	puts("cannot open file");
	//	getchar();
	//	exit(-10);
	//}
	
	omyfile1 = create_output_file("1");
	omyfile2 = create_output_file("2");
	omyfile3 = create_output_file("3");
	omyfile4 = create_output_file("4");
	omyfile5 = create_output_file("5");
	out_var_1 = (double*)malloc (10000000*sizeof(double));
	if (out_var_1 == NULL) exit(-10);
	out_var_2 = (double*)malloc (10000000*sizeof(double));
	if (out_var_2 == NULL) exit(-20);
		out_var_3 = (double*)malloc (10000000*sizeof(double));
	if (out_var_3 == NULL) exit(-30);
}

Purkinje::~Purkinje()
{
	RunThread = 0;
	WaitForSingleObject(threadHandle, INFINITE);
	for (int i = 0; i<L; i++) free(g[i]);
	free(g);
	for(int it = 0; it < L;++it) free(g_halfop[it]);
	free(g_halfop);
	fclose(f_Tequ);
	free(vector_e);
	fclose(omyfile1); fclose(omyfile2); fclose(omyfile3); fclose(omyfile4); fclose(omyfile5);
	//free(eligibility_exp[1]);free(eligibility_exp[0]);free(eligibility_exp);
	free(sigma);
	free(out_var_1); free(out_var_2); free(out_var_3);
}
void Purkinje::Run()
{ 
	for (timestep = 0; timestep < fulltime; timestep++) StepForwardOptimized(); 
}

void  Purkinje::ConvertG2Optimized()
{
	unsigned int NumberOfUnits, MaxNumberOfUnits = 0;
	g_halfop = (unsigned int**)malloc(L*sizeof(unsigned int*));
	if (g_halfop == NULL) {puts("ERRR");exit(-1);}
	for(int i = 0;i<L;i++)
	{
			NumberOfUnits = 0;
		for(int j = 0;j<N;j++)
			NumberOfUnits += g[i][j];
		g_halfop[i] = (unsigned int*)malloc((NumberOfUnits+2)*sizeof(unsigned int));
		if (g_halfop[i] == NULL) {puts("ERRR");exit(-1);}
		if (MaxNumberOfUnits<NumberOfUnits) MaxNumberOfUnits = NumberOfUnits;
	}
	for (int t = 0; t < L; t++)
	{
		int ptt = 0;
		for (int k = 0; k < N; k++)
		{
			if (g[t][k]  == 1) {g_halfop[t][ptt]=k; ptt++;}
		}
		g_halfop[t][ptt] = -1;
	}
}

bool Purkinje::StepForwardOptimized(void)
{
	if (LianaCellFiringFunction() == true) 
	{
		counter_tequ++;
		fprintf(f_Tequ,"%d %d %d\n",counter_tequ, CSpikeTime, timestep);
		CSpikeTime = 0;
	}
		SynapticWeightsStep();

		//calculating of Purkinje output
		scalar_Purkinje_presynap = 0;
		for(int it = 0; g_halfop[timestep%L][it]!=-1;++it)
		{
			scalar_Purkinje_presynap = scalar_Purkinje_presynap + sigma[g_halfop[timestep%L][it]];
		}
		sigma_sum = 0;
		for (int k = 0; k < N; k++)
		sigma_sum = sigma_sum + sigma[k];
		//Purkinje = Purkinje*exp(-1/T_p)+scalar_Purkinje_presynap;
		PurkinjeFreq = PurkinjeFreq*k_purk+scalar_Purkinje_presynap;
		PurkinjeFreqPublic = PurkinjeFreq;
		Liana_Public = Liana_buf;
		alpha_Public = Alpha();
		/*if (timestep<200000)fprintf(omyfile1, "%d %f %f %f %f %f\n",
			timestep, sigma[0], sigma_sum, Liana_buf, PurkinjeFreq, Alpha());
		else if (timestep<400000)fprintf(omyfile2, "%d %f %f %f %f %f\n",
			timestep, sigma[0], sigma_sum, Liana_buf, PurkinjeFreq, Alpha());
		else if (timestep<600000)fprintf(omyfile3, "%d %f %f %f %f %f\n",
			timestep, sigma[0], sigma_sum, Liana_buf, PurkinjeFreq, Alpha());
		else if (timestep<800000)fprintf(omyfile4, "%d %f %f %f %f %f\n",
			timestep, sigma[0], sigma_sum, Liana_buf, PurkinjeFreq, Alpha());
		else if (timestep<1000000)fprintf(omyfile5, "%d %f %f %f %f %f\n",
			timestep, sigma[0], sigma_sum, Liana_buf, PurkinjeFreq, Alpha());*/
		if ((fulltime-timestep)<200000)fprintf(omyfile5, "%d %f %f %f %f %f\n",
			timestep, sigma[0], sigma_sum, Liana_buf, PurkinjeFreq, Alpha());
		//else {printf("\ntimestep is out of range\n"); getchar();exit(-1);}*/

		CSpikeTime++;
		return true;
}
bool Purkinje::SynapticWeightsStep()
{
	for (int it = 0; g_halfop[timestep%L][it]!=-1;++it)
	{
		if (sigma_reset != 2) {sigma[g_halfop[timestep%L][it]] = sigma[g_halfop[timestep%L][it]] + epsilon*LTDP_ImitationFunction(CSpikeTime);}
		else {sigma[g_halfop[timestep%L][it]] = sigma[g_halfop[timestep%L][it]]*(1 + epsilon*LTDP_ImitationFunction(CSpikeTime));}
		if (sigma[g_halfop[timestep%L][it]] < 0)
		{
			if (sigma_reset == 0) {printf("negative sigma detected\n"); sigma_reset = 21;}
			if (sigma_reset == 11)sigma[g_halfop[timestep%L][it]] = 0;
			else if (sigma_reset == 1){sigma[g_halfop[timestep%L][it]] = 0; printf("zero weight %d -> sigma reset....\n", it);sigma_reset = 11;}
		}
		
	}
	return true;
}

bool NewInit()
{
	
	//Формируется вектор M_{i} (0,1), который потом подаётся на вход
	Vector <Cell> M;
	M.push(new Cell(MOSSY));
	//Создать/Загрузить зернистые клетки, со входами с M.
	//4 units of M --> presynap GranuleCell[i];
	Vector <Cell> GranuleCell;//Cell* GranuleCell;
	GranuleCell.push(new Cell(GRANULE));//GranuleCell[i] = new Cell
	if (IfCreateGlomeruli) CreateGlomeruliConnections(M, GranuleCell, DataBase);
	if (IfLoadGlomeruli) LoadGlomeruliConnections(M,GranuleCell, DataBase);
	
	
	return true;
};
bool CreateGlomeruliConnections (MF, GrC, DataBase)
{
	NeuralNetSettings.AskSetSettings();//Read
	return true;
}
bool LoadGlomeruliConnections()
{
	//Read neuron database file
	OpenFile("DataBase");
	for (int i; i<NUMBER_OF_NEURONS; i++)
	GrC[m].SetPresynap(MF[n]);
	return true;
}
