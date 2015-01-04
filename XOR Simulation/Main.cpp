#include <iostream>
#include "Brain.h"
#include "Testing.h"
#include <fstream>
using namespace std;

int main(){
	ofstream Results;
	Results.open("Results_Of_Trainning.txt");
	cout << "Loading trainning data" << endl;
	Testing learn;
	cout << "Data Loaded" << endl;
	system("cls");

	vector<unsigned> topography;
	topography.push_back(2);
	topography.push_back(4);
	topography.push_back(1);

	Net myNet(topography);
	vector<double> resultVals;
	cout << "Running trails" << endl;
	for (int i = 0; i < learn.Practice.size() ; i++){
		Results << "Example Number: " << i << endl;
		Results << "input is:" << endl;
		for (double x : learn.Practice[i].input){
			Results << x << endl;
		}
		Results << "----------" << endl;
		Results << "Expected Value: " << learn.Practice[i].finalVal[0] << endl;;
		myNet.feedForward(learn.Practice[i].input);
		myNet.getResults(resultVals);
		Results << "Output is:" << round(abs(resultVals.back())) << endl;
		myNet.backProp(learn.Practice[i].finalVal);
		Results << endl;
		
	}
	cout << "trails Complete" << endl;
	system("pause");
	return 0;
}