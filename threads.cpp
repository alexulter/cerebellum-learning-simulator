#include "mauk.h"

VOID Purkinje::ComputingThread(UINT i)
{
	for (int mytimevar = 0; mytimevar<50; mytimevar++) 
	{
		timestep++;
		StepForwardOptimized();
		//StepForward();
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
	WaitForSingleObject(threadHandle, INFINITE);
}