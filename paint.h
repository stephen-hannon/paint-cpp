#include <string>
#include <vector>
using namespace std;

class Paint {
	public:
		Paint();
		~Paint();

		int loadImage(string name);
		
	private:
		int imageWidth;
		int imageHeight;
		vector<unsigned char[3]> image;
};
