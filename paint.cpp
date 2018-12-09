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


void Paint::setInFilename(string name)
{ inFilename = name; }

void Paint::setOutFilename(string name)
{ outFilename = name; }

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

Color Paint::intToColor(unsigned int color)
{
	unsigned int r = 255 * (color >> 2);
	unsigned int g = 255 * ((color >> 1) & 1);
	unsigned int b = 255 * (color & 1);

	return {r, g, b};
}

void Paint::addPoint(int x, int y, int color, int size)
{
	int address = y * imageWidth + x;
	imageCompressed[color].push_back(address);
	image[address] = intToColor(color);
	cout << "color " << color << ' ' << imageCompressed[color].size() << ' ';
	cout << "addr" << x << ' ' << y << endl;
}

int Paint::loadImage()
{
	ifstream ifs (inFilename);

	if (ifs.get() != 'P') return 1;
	if (ifs.get() != '3') return 1;

	ifs >> imageWidth >> imageHeight;
	//cout << imageWidth << ' ' << imageHeight << endl;

	ifs >> maxColor;

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
	ifs.close();
}

int Paint::saveImage()
{
	ofstream ofs (outFilename);

	ofs << "P3\n";
	ofs << imageWidth << ' ' << imageHeight << '\n';
	ofs << maxColor << '\n';

	int x = 0;
	for (Color triplet: image) {
		ofs << triplet.r << ' '
			<< triplet.g << ' '
			<< triplet.b << '\t';

		if (x == imageWidth - 1) {
			ofs << '\n';
			x = 0;
		} else x++;
	}
	
	ofs.close();

	return 0;
}
