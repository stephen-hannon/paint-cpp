// paintmain.cpp

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
		const int width = 800, height = 500;
		char c;
		int event;
		Paint paint;

		paint.setInFilename(argv[1]);
		paint.setOutFilename(argv[(argc == 3) ? 2 : 1]);
		paint.loadImage();

		int imageWidth = paint.getImageWidth();
		int imageHeight = paint.getImageHeight();

		char font[] = "12x24";
		char text[] = "hello world";
		int scale = 5;
		int color = 7; // white
		bool mousedown = false;
		int lastx = -1, lasty = -1;

		gfx_open(width, height, "Paint");

		drawImage(paint, scale, imageWidth);

		while (true) {
			event = gfx_event_waiting();
			if (!event) continue;

			c = gfx_wait();
			gfx_flush();
			cout << c << event << endl;

			gfx_color(255, 255, 255);
			gfx_text(100, 50, text);
			setColor(paint, color);

			c = gfx_wait();
			gfx_flush();
				
			if (event == 3) mousedown = true;
			if (event == 4) mousedown = false;
			if (event == 5 && mousedown) { // mousemove
				drawPixel(paint, color, scale, imageWidth, imageHeight, lastx, lasty);
			}

			if (c == 'q') {
				break;
			} else if (c == 's') {
				paint.saveImage();
			} else if (c >= '0' && c <= '7') {
				color = c - '0';
				//setColor(color);
				cout << "color " << c << endl;
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
	int x = gfx_xpos() / scale, y = gfx_ypos() / scale;
	if (x < imageWidth && y < imageHeight && (x != lastx || y != lasty)) {
		paint.addPoint(x, y, color, 1);
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

		cout << "color " << i << endl;
		for (int index: paint.getCompressedColors(i)) {
			int x = scale * (index % imageWidth),
				y = scale * (index / imageWidth);
			gfx_fill_rectangle(x, y, scale, scale);
			if (index > imageWidth*imageWidth) cout << x << ' ' << y << endl;
		}
	}
}
