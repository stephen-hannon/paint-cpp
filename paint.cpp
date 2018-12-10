// Stephen Hannon and Julius Boateng
// Lab 12
// paint.cpp
#include <fstream>
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

// Convert an integer with a color represented as bits
// like 5 (101) --> {255, 0, 255}
Color Paint::intToColor(unsigned int color)
{
	unsigned int r = 255 * (color >> 2);
	unsigned int g = 255 * ((color >> 1) & 1);
	unsigned int b = 255 * (color & 1);

	return {r, g, b};
}

void Paint::addPoint(int x, int y, int color)
{
	int address = y * imageWidth + x;
	imageCompressed[color].push_back(address);
	image[address] = intToColor(color);
}

int Paint::loadImage()
{
	ifstream ifs;

	ifs.open(inFilename);

	if (!ifs) return 1;

	if (ifs.get() != 'P') return 1;
	if (ifs.get() != '3') return 1;

	ifs >> imageWidth >> imageHeight;

	ifs >> maxColor;
	if (maxColor != 255) return 1;

	int index = 0;
	unsigned int r, g, b;
	unsigned int compColor;
	bool rc, gc, bc; // r, g, b compressed
	while (ifs.peek() != EOF) {
		ifs >> r >> g >> b;

		// Pack the compressed color data into a 3-bit number
		// for easy storage
		rc = r >> 7;
		gc = g >> 7;
		bc = b >> 7;
		compColor = rc;
		compColor = (compColor << 1) | gc;
		compColor = (compColor << 1) | bc;
		
		imageCompressed[compColor].push_back(index);

		Color triplet = {r, g, b};
		image.push_back(triplet);
		ifs >> ws;
		index++;
	}

	ifs.close();

	return 0;
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
