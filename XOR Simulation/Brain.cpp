#include "Brain.h"
#include <iostream>
using namespace std;
double Neuron::eta = .15;
double Neuron::alpha = .5;

void Neuron::updateInputWeights(layer &prev){

	for (unsigned n = 0; n < prev.size(); n++){
		Neuron &neuron = prev[n];
		double oldDeltawight = neuron.m_outputWeights[m_myIndex].deltaWeights;

		double newDeltaWeight =
			eta
			*neuron.getOutputVal()
			*m_gradient
			+alpha
			*oldDeltawight;

		neuron.m_outputWeights[m_myIndex].deltaWeights = newDeltaWeight;
		neuron.m_outputWeights[m_myIndex].weights += newDeltaWeight;
	}

}
double Neuron::transferFunction(double x){

	return tanh(x);

}
double Neuron::sumDOW(const layer& next)const{
	double sum = 0.0;

	for (unsigned n = 0; n < next.size() - 1; n++){
		sum += m_outputWeights[n].weights * next[n].m_gradient;


	}
	return sum;
}
double Neuron::transferFunctionDerivative(double x){

	return 1.0 - x*x;
}
void Neuron::calculateOutputGradients(double targetVal){
	double delta = targetVal - m_outputVal;
	m_gradient = delta * Neuron::transferFunctionDerivative(m_outputVal);
}
void Neuron::calculateHiddenGradients(const layer &next){
	double dow = sumDOW(next);
	m_gradient = dow * Neuron::transferFunctionDerivative(m_outputVal);



}
Neuron::Neuron(unsigned numOutputs, unsigned my_index){
	m_myIndex = my_index;
	for (unsigned c = 0; c < numOutputs; c++){
		m_outputWeights.push_back(Connection());
		m_outputWeights.back().weights = randomWeight();

	}
}
void Neuron::feedForward(const layer &preLayer){

	double sum = 0.0;

	for (unsigned n = 0; n < preLayer.size(); n++){
		sum += preLayer[n].getOutputVal()*
			preLayer[n].m_outputWeights[m_myIndex].weights;
	}
	m_outputVal = Neuron::transferFunction(sum);
}

void Net::backProp(const vector<double> &targetVals){
	
	layer &outputlayer = m_layers.back();
	m_error = 0.0;
	
	for (unsigned n = 0; n < outputlayer.size() - 1; n++){
		double delta = targetVals[n] - outputlayer[n].getOutputVal();
		m_error += delta * delta;
	}
	
	m_error /= outputlayer.size()-1;
	m_error = sqrt(m_error);

	m_recentAverageError = (m_recentAverageError *
		m_recentAverageSmoothingFactor + m_error) /
		(m_recentAverageSmoothingFactor + 1);
	
	for (unsigned n = 0; n < outputlayer.size()-1; n++){
		outputlayer[n].calculateOutputGradients(targetVals[n]);
	}

	for (unsigned layerNum = m_layers.size() - 2; layerNum > 0; layerNum--){
		layer &hiddenLayer = m_layers[layerNum];
		layer &nextLayer = m_layers[layerNum + 1];

		for (unsigned n = 0; n < hiddenLayer.size() ; n++){
			hiddenLayer[n].calculateHiddenGradients(nextLayer);
		}
	}

	for (unsigned layerNum = m_layers.size()-1; layerNum > 0; layerNum--){
		layer &layer = m_layers[layerNum], &prevLayer = m_layers[layerNum - 1];

		for (unsigned n = 0; n < layer.size() - 1; ++n) {
			layer[n].updateInputWeights(prevLayer);
		}
	}
}
void Net::getResults(vector<double> &resultVals) const{

	resultVals.clear();

	for (unsigned n = 0; n < m_layers.back().size() - 1; n++){

		resultVals.push_back(m_layers.back()[n].getOutputVal());
	}
}
void Net::feedForward(const vector<double> &inputVals){

	//assert(inputVals.size() == m_layers[0].size() - 1);

	for (int i = 0; i < inputVals.size(); i++){
		m_layers[0][i].setOutputVal(inputVals[i]);
	}

	for (unsigned layerNum = 1; layerNum < m_layers.size(); layerNum++){
		layer &prevLayer = m_layers[layerNum - 1];
		for (unsigned n = 0; n < m_layers[layerNum].size() - 1; n++){
			m_layers[layerNum][n].feedForward(prevLayer);
		}
	}
}
Net::Net(const vector<unsigned> &topography){
	unsigned numLayers = topography.size();

	for (unsigned layerNum = 0; layerNum < numLayers; layerNum++){
		m_layers.push_back(layer());
		unsigned numOutputs = layerNum == topography.size() - 1 ? 0 : topography[layerNum + 1];

		for (unsigned neuroNum = 0; neuroNum <= topography[layerNum]; neuroNum++){
			m_layers.back().push_back(Neuron(numOutputs, neuroNum));
		}
		m_layers.back().back().setOutputVal(1);
	}

}