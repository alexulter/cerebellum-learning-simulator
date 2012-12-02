#pragma once

class NeuralNetSettings
{
public:
	NeuralNetSettings(void);
	~NeuralNetSettings(void);
	int NeuronCounts[NUMBER_OF_NEURON_TYPES];
	int ConnectionScenario;
	
	int AskSetSettings();
};