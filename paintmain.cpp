// paintmain.cpp

#include <iostream>
using namespace std;

#include "paint.h"
#include "gfx3.h"

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

	gfx_open(width, height, "Paint");

	while (true) {
		event = gfx_event_waiting();
		if (!event) continue;

		c = gfx_wait();
		gfx_flush();
		cout << c << event << endl;

		gfx_color(255, 255, 255);
		gfx_text(100, 50, text);

		// Draw every pixel for each of the 8 colors
		for (int i = 0; i < 8; i++) {
			int r = 255 * (i >> 2);
			int g = 255 * ((i >> 1) & 1);
			int b = 255 * (i & 1);
			gfx_color(r, g, b);

			for (int index: paint.getCompressedColors(i)) {
				int x = scale * (index % imageWidth),
					y = scale * (index / imageWidth);
				gfx_fill_rectangle(x, y, scale, scale);
			}
		}


		c = gfx_wait();
		gfx_flush();
			
		if (c == 'q') {
			break;
		} else if (c == '='){
			if (scale < 10){
				scale = scale + 1;
				gfx_clear();
			}
		} else if (c == '-'){
			if (scale >= 2){
				scale = scale - 1;
				gfx_clear();
			}
		} else if (c == 1) {
			paint.addPoint(gfx_xpos() / scale, gfx_ypos() / scale, 4, 1);
		}
	}

	return 0;
}

