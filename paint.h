#include <cstdint>
#include <string>
#include <vector>
using namespace std;

struct Color {
	int r;
	int g;
	int b;
};

class Paint {
	public:
		Paint();
		~Paint();

		int getImageWidth();
		int getImageHeight();
		Color getColor(int x, int y);
		int loadImage(string name);
		
	private:
		int imageWidth;
		int imageHeight;
		int bitsPerColor;
		vector<Color> image;
};
