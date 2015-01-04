#include "Testing.h"
#include <vector>

Testing::Testing()
{
	try{
		read.open("Example.txt");
		for (int i = 0; i < 4; i++)
			getline(read, data[i]);
		read.close();
	} catch (...){}

	for (int i = 0; i < 70000; i++)
		Practice.push_back(example(data[rand() % 4]));
}


Testing::~Testing()
{
}
