// paint.cpp
#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <vector>
using namespace std;

#include "paint.h"

Paint::Paint()
{
}

Paint::~Paint()
{ }


int Paint::getImageWidth()
{ return imageWidth; }

int Paint::getImageHeight()
{ return imageHeight; }

Color Paint::getColor(int x, int y)
{
	return image[y * imageWidth + x];
}

int Paint::loadImage(string name)
{
	ifstream ifs (name);

	//cout << ifs.get() << endl;
	if (ifs.get() != 'P') return 1;
	if (ifs.get() != '3') return 1;

	ifs >> imageWidth >> imageHeight;
	//cout << imageWidth << ' ' << imageHeight << endl;

	ifs >> bitsPerColor;

	//unsigned char r, g, b;
	unsigned int r, g, b;
	while (ifs.peek() != EOF) {
		ifs >> r >> g >> b;
		Color triplet = {r, g, b};
		image.push_back(triplet);
		cout << r << ' ' << g << ' ' << b << endl;
		ifs >> ws;
	}
}
