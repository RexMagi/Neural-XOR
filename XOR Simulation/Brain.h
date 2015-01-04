#pragma once
#include <vector>
#include <cstdlib>
#include <cassert>
#include <cmath>

using namespace std;
struct Connection{
	Connection(){
		weights = 0;
		deltaWeights=0;
	}
	double weights;
	double deltaWeights;

};
class Neuron;
typedef vector<Neuron> layer;
//*********** class Neuron ****************
class Neuron{
public:
	Neuron(unsigned numOutputs, unsigned my_index);
	double getOutputVal()const { return m_outputVal; }
	void setOutputVal(double Output) { m_outputVal = Output; }
	void feedForward(const layer &preLayer);
	void calculateOutputGradients(double);
	void calculateHiddenGradients(const layer &next);
	void updateInputWeights(layer&);
private:
	double transferFunction(double x);
	double transferFunctionDerivative(double x);
	static double randomWeight(){
		return rand() / double(RAND_MAX);
	};
	double m_outputVal;
	double sumDOW(const layer&) const;
	vector<Connection> m_outputWeights;
	unsigned m_myIndex;
	static double eta;
	static double alpha;
	double m_gradient;
};

//*********** class Net ****************
class Net{

public:
	Net(const vector<unsigned> &topography);
	void feedForward(const vector<double> &inputVals);
	void backProp(const vector<double> &targetVals);
	void getResults(vector<double> &resultVals) const;

private:
	vector<layer> m_layers;
	double m_error;
	double m_recentAverageError;
	double m_recentAverageSmoothingFactor;
};