#pragma once

struct CELL_STATE {
	double MembranePotential;
};
struct CELL_INC_SYN{
	int presyn_id;
	int syn_type;
	int syn_weight;
};
	class Cell
{
public:
	Cell(void);
	~Cell(void);
	AddIncomingSynapse(parameters, target);
	AddIncomingSynapses(parameters, targets);
	EvaluateState();
	double EvaluateMossy();
private:
	int type;
	CELL_STATE state;
	int axon_odd_t;
	int axon_even_t;
	int inc_syn_N;
	CELL_INC_SYN* inc_syn;
};
