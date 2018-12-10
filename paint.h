// Stephen Hannon and Julius Boateng
// Lab 12
// paint.h
#include <string>
#include <vector>
#include <array>
using namespace std;

struct Color {
	unsigned int r;
	unsigned int g;
	unsigned int b;
};

class Paint {
	public:
		Paint();
		~Paint();

		void setInFilename(string name);
		void setOutFilename(string name);
		int getImageWidth();
		int getImageHeight();
		Color getColor(int x, int y);
		vector<int> getCompressedColors(int color);
		Color intToColor(unsigned int color);
		void addPoint(int x, int y, int color);
		int loadImage();
		int saveImage();
		
	private:
		string inFilename;
		string outFilename;
		int imageWidth;
		int imageHeight;
		int maxColor;
		vector<Color> image;
		array<vector<int>, 8> imageCompressed;
};
