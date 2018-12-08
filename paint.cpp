// paint.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "paint.h"

Paint::Paint()
{
}

Paint::~Paint()
{ }


int Paint::loadImage(string name)
{
	ifstream ifs (name);

	cout << ifs.get() << endl;
}
