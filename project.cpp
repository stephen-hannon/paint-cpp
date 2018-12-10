// Stephen Hannon and Julius Boateng
// Lab 12
// project.cpp

#include <iostream>
using namespace std;

#include "paint.h"
#include "gfx3.h"

void drawPixel(Paint &paint, int color, int scale, int imageWidth, int imageHeight, int &lastx, int &lasty);
void setColor(Paint &paint, unsigned int color);
void drawImage(Paint &paint, int scale, int imageWidth);

int main(int argc, char *argv[])
{
	if (argc == 2 || argc == 3) {
		const int width = 1200, height = 700;
		char c;
		int event;
		Paint paint;

		paint.setInFilename(argv[1]);
		// If the second argument is not given, use the first as
		// outFilename
		paint.setOutFilename(argv[(argc == 3) ? 2 : 1]);

		bool loadStatus = paint.loadImage();
		if (loadStatus != 0) {
			cout << "Error reading file " << argv[1] << endl;
			return 1;
		}

		int imageWidth = paint.getImageWidth();
		int imageHeight = paint.getImageHeight();

		int scale = 5; // Size of the square for an image pixel
		int color = 7; // white
		bool mousedown = false;
		int lastx = -1, lasty = -1;

		gfx_open(width, height, "Paint");

		drawImage(paint, scale, imageWidth);

		while (true) {
			event = gfx_event_waiting();
			// If there's no event waiting, try again
			if (event == 0) continue;

			c = gfx_wait();
			gfx_flush();

			setColor(paint, color);

			if (event == 3) mousedown = true; // mousedown
			if (event == 4) mousedown = false; // mouseup
			if (event == 5 && mousedown) { // mousemove
				drawPixel(paint, color, scale, imageWidth, imageHeight, lastx, lasty);
			}

			if (c == 'q') {
				break;
			} else if (c == 's') {
				paint.saveImage();
			} else if (c >= '0' && c <= '7') {
				color = c - '0';
			} else if (c == '='){
				if (scale < 10){
					scale = scale + 1;
					gfx_clear();
					drawImage(paint, scale, imageWidth);
				}
			} else if (c == '-'){
				if (scale >= 2){
					scale = scale - 1;
					gfx_clear();
					drawImage(paint, scale, imageWidth);
				}
			} else if (c == 1) {
				drawPixel(paint, color, scale, imageWidth, imageHeight, lastx, lasty);
			}
		}
	} else {
		cout << "Expected 1 or 2 arguments, got " << argc - 1 << endl;
		return 1;
	}

	return 0;
}

void drawPixel(Paint &paint, int color, int scale, int imageWidth, int imageHeight, int &lastx, int &lasty)
{
	int x = gfx_xpos() / scale,
		y = gfx_ypos() / scale;

	// Only draw if the point is within the bounds and it isn't
	// so close to the previous one that it is the same pixel
	if (x < imageWidth && y < imageHeight && (x != lastx || y != lasty)) {
		paint.addPoint(x, y, color);
		gfx_fill_rectangle(x * scale, y * scale, scale, scale);

		lastx = x;
		lasty = y;
	}
}

void setColor(Paint &paint, unsigned int color)
{
	if (color > 7) return;

	Color col = paint.intToColor(color);

	gfx_color(col.r, col.g, col.b);
}

void drawImage(Paint &paint, int scale, int imageWidth)
{
	// Draw every pixel for each of the 8 colors
	for (int i = 0; i < 8; i++) {
		setColor(paint, i);

		for (int index: paint.getCompressedColors(i)) {
			int x = scale * (index % imageWidth),
				y = scale * (index / imageWidth);
			gfx_fill_rectangle(x, y, scale, scale);
		}
	}

	vector<string> menu = {
		"Click/drag to draw",
		"",
		"Commands:",
		"q    Quit",
		"s    Save",
		"-    Zoom out",
		"+    Zoom in",
		"",
		"Colors:",
		"0    Black",
		"1    Blue",
		"2    Green",
		"3    Cyan",
		"4    Red",
		"5    Magenta",
		"6    Yellow",
		"7    White"
	};
	int width = gfx_windowwidth();
	int menuX = width - 150;
	int menuY = 80;

	gfx_color(255, 255, 255);
	gfx_changefont((char*)"12x24");
	gfx_text(menuX, menuY, "Paint 0.1");
	menuY += 30;

	gfx_changefont((char*)"fixed");
	for (string item: menu) {
		gfx_text(menuX, menuY, item.c_str());
		menuY += 15;
	}
}
