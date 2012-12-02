#include "mauk.h"

VOID Purkinje::ComputingThread(UINT i)
{
	//for (int mytimevar = 0; mytimevar<50; mytimevar++) 
	while (RunThread != 0)
	{
		timestep++;
		StepForwardOptimized();
		out_var_1[timestep] = PurkinjeFreqPublic+10;
		out_var_2[timestep] = Liana_Public+10;
		out_var_3[timestep] = alpha_Public+10;
	}
}
UINT Purkinje::ThreadFunc(LPVOID param)
{
	Purkinje* This = (Purkinje*)param;
	//puts("ok\n");
	This->ComputingThread(0);
	return 0;
}
VOID Purkinje::StartThreadFunc()
{
	threadHandle = CreateThread(0,0,(LPTHREAD_START_ROUTINE)ThreadFunc,
		(LPVOID)this,0,0);
	//WaitForSingleObject(threadHandle, INFINITE);
}