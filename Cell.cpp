#include "StdAfx.h"
#include "Cell.h"

Cell::Cell(void)
{
}

Cell::~Cell(void)
{
}
Cell::EvaluateState(InputVectorX &X, Cell &CellArray)
{
	if (type == MOSSY) MembranePotential = EvaluateMossy(X);//exp(-mu*(Xi-Xij)^2);
	else MembranePotential = IntegrateSpikes(CellArray, inc_syn);
}
double Cell::EvaluateMossy(InputVectorX &X)
{
	double Xij, Ximn, Xmax;
//	for (i = 1; i <= inc_syn_N; i++)
//	{
		if ((inc_syn[i] != EXT_INPUT)||(inc_syn_N>1)) terminate("ERROR");
		Xij = ...[j = inc_syn[i].weight, Xmin = X.GetXimin(inc_syn[i].id), Xmac = X.GetXimax(inc_syn[i].id)];
		M = exp(-mu*(X.GetXi(inc_syn[i].id) - Xij)^2)
//	}
	return M;
}