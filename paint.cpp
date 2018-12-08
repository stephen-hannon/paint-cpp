// paint.cpp
#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <vector>
#include <array>
using namespace std;

#include "paint.h"

Paint::Paint()
{
	imageCompressed.fill(vector<int>());
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

vector<int> Paint::getCompressedColors(int color)
{
	return imageCompressed[color];
}

void Paint::addPoint(int x, int y, int color, int size)
{
	imageCompressed[color].push_back(y * imageWidth + x);
	cout << y * imageWidth + x << endl;
}

int Paint::loadImage(string name)
{
	ifstream ifs (name);

	if (ifs.get() != 'P') return 1;
	if (ifs.get() != '3') return 1;

	ifs >> imageWidth >> imageHeight;
	//cout << imageWidth << ' ' << imageHeight << endl;

	ifs >> bitsPerColor;

	int index = 0;
	unsigned int r, g, b;
	unsigned int compColor;
	bool rc, gc, bc; // r, g, b compressed
	while (ifs.peek() != EOF) {
		ifs >> r >> g >> b;

		rc = r >> 7;
		gc = g >> 7;
		bc = b >> 7;
		compColor = rc;
		compColor = (compColor << 1) | gc;
		compColor = (compColor << 1) | bc;
		//cout << compColor << endl;
		
		imageCompressed[compColor].push_back(index);

		Color triplet = {r, g, b};
		image.push_back(triplet);
		//cout << r << ' ' << g << ' ' << b << endl;
		ifs >> ws;
		index++;
	}
	cout << "image loaded" << endl;
}
