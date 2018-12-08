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

	paint.loadImage("test.ppm");

	char font[] = "12x24";
	char text[] = "hello world";

	gfx_open(width, height, "Paint");

	gfx_changefont(font);

	while (true) {
		gfx_text(100, 50, text);

		if (gfx_wait() == 'q') break;
	}

	return 0;
}

