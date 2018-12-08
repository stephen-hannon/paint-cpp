// paintmain.cpp

#include <iostream>
using namespace std;

#include "paint.h"
#include "gfx3.h"

int main()
{
	const int width = 800, height = 500;
	char c;
	Paint paint;

	paint.loadImage("test2.ppm");
	int imageWidth = paint.getImageWidth();
	int imageHeight = paint.getImageHeight();

	char font[] = "12x24";
	char text[] = "hello world";

	gfx_open(width, height, "Paint");

	while (true) {
		gfx_color(255, 255, 255);
		gfx_text(100, 50, text);

		// Draw every pixel for each of the 8 colors
		for (int i = 0; i < 8; i++) {
			int r = 255 * (i >> 2);
			int g = 255 * ((i >> 1) & 1);
			int b = 255 * (i & 1);
			gfx_color(r, g, b);
			int scale = 5;

			for (int index: paint.getCompressedColors(i)) {
				int x = scale * (index % imageWidth),
					y = scale * (index / imageWidth);
				gfx_fill_rectangle(x, y, scale, scale);
			}
		}


		c = gfx_wait();
		gfx_flush();
		if (c == 'q') break;
	}

	return 0;
}

