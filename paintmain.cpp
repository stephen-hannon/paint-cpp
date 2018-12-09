// paintmain.cpp

#include <iostream>
using namespace std;

#include "paint.h"
#include "gfx3.h"

void drawPixel(Paint &paint, int color, int scale, int &lastx, int &lasty);
void setColor(unsigned int color);
void drawImage(Paint &paint, int scale, int imageWidth);

int main()
{
	const int width = 800, height = 500;
	char c;
	int event;
	Paint paint;

	paint.loadImage("test2.ppm");
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
		setColor(color);

		c = gfx_wait();
		gfx_flush();
			
		if (event == 3) mousedown = true;
		if (event == 4) mousedown = false;
		if (event == 5 && mousedown) { // mousemove
			drawPixel(paint, color, scale, lastx, lasty);
		}

		if (c == 'q') {
			break;
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
			drawPixel(paint, color, scale, lastx, lasty);
		}
	}

	return 0;
}

void drawPixel(Paint &paint, int color, int scale, int &lastx, int &lasty)
{
	int x = gfx_xpos() / scale, y = gfx_ypos() / scale;
	if (x != lastx || y != lasty) {
		paint.addPoint(x, y, color, 1);
		gfx_fill_rectangle(x * scale, y * scale, scale, scale);

		lastx = x;
		lasty = y;
	}
}

void setColor(unsigned int color)
{
	if (color > 7) return;

	int r = 255 * (color >> 2);
	int g = 255 * ((color >> 1) & 1);
	int b = 255 * (color & 1);

	gfx_color(r, g, b);
}

void drawImage(Paint &paint, int scale, int imageWidth)
{
	// Draw every pixel for each of the 8 colors
	for (int i = 0; i < 8; i++) {
		setColor(i);

		cout << "color " << i << endl;
		for (int index: paint.getCompressedColors(i)) {
			int x = scale * (index % imageWidth),
				y = scale * (index / imageWidth);
			gfx_fill_rectangle(x, y, scale, scale);
			if (index > imageWidth*imageWidth) cout << x << ' ' << y << endl;
		}
	}
}
