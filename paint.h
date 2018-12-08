#include <cstdint>
#include <string>
#include <vector>
#include <array>
using namespace std;

struct Color {
	unsigned int r;
	unsigned int g;
	unsigned int b;
};
struct Point {
	unsigned int x;
	unsigned int y;
};

class Paint {
	public:
		Paint();
		~Paint();

		int getImageWidth();
		int getImageHeight();
		Color getColor(int x, int y);
		vector<int> getCompressedColors(int color);
		void addPoint(int x, int y, int color, int size);
		int loadImage(string name);
		
	private:
		int imageWidth;
		int imageHeight;
		int bitsPerColor;
		vector<Color> image;
		array<vector<int>, 8> imageCompressed;
};
