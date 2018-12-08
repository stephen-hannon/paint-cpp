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

	char font[] = "12x24";
	char text[] = "hello world";

	gfx_open(width, height, "Paint");

	//gfx_changefont(font);

	while (true) {
		gfx_color(255, 255, 255);
		gfx_text(100, 50, text);

		cout << "draw start" << endl;
		for (int y = 0; y < paint.getImageHeight(); y++) {
			for (int x = 0; x < paint.getImageWidth(); x++) {
				int r, g, b;
				Color color = paint.getColor(x, y);
				gfx_color(color.r, color.g, color.b);
				gfx_point(x, y);
			}
		}
		cout << "draw" << endl;


		c = gfx_wait();
		gfx_flush();
		if (c == 'q') break;
	}

	return 0;
}

