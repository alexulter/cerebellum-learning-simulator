#pragma once

class InputVectorX
{
public:
	InputVectorX(void);
	~InputVectorX(void);
	double GetXi(int Xtag);
	SetXi(int Xtag, double XiValue);
private:
	int NumberOfVariablesX;
	double *Xi;
	//double** Xij;
	int XiMossyNumber;
	double Xmin, Xmax;
};
