#include "StdAfx.h"
#include "InputVectorX.h"

InputVectorX::InputVectorX(void)
{
	Xi = new double[NumberOfVariablesX];//malloc(NumberOfVariablesX*sizeof(double));
	//Xij = new (double[NumberOfVariablesX][XiMossyNumber]);//malloc(NumberOfVariablesX*sizeof(double*));
	//for (int i =0; i<NumberOfVariablesX; i++)
	//	Xij[i] = malloc(XiMossyNumber*sizeof(double));
}

InputVectorX::~InputVectorX(void)
{
	delete Xi;
	//delete Xij;
	//free(Xi);
	//for (int i =0; i<NumberOfVariablesX; i++)
	//	free(Xij[i]);
	//free(Xij);
}
	//�H�p�t�p�v�} �r�����t�~���z ���y���|���r���z �r�u�{������ �t�|�� �}���x�w�u���{���r���s�� �}���t���|��
	//�D�|�� �~�p���p�|�p ������ �}���w�~�� ���t�u�|�p���� �x�p�t�p�r �{���~�����p�~���� �y�|�y ���|�u�}�u�~���p���~���� �����~�{���y��
InputVectorX::GetX_i(int Xtag)
{
	return X[Xtag];
}
