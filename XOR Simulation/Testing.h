#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>

struct example{
	std::vector<double> input;
	std::vector<double> finalVal;
	example(std::string x){
		input.push_back(x[0]=='0'?0:1);
		input.push_back(x[1] == '0' ? 0 : 1);
		finalVal.push_back(x[3] == '0' ? 0 : 1);
	};
};

class Testing
{
public:
	Testing();
	~Testing();
	std::vector<example> Practice;
private:
	std::ifstream read;
	std::string data[4];

};

