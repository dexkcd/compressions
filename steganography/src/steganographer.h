#include "CImg.h"

class Steganographer
{
	public:
		Steganographer();
		~Steganographer();
	public:
		int compress(const char *imageFile, const char *inputfile, const char *outputImage);
		int decompress(const char *imageFile, const char *inputfile);

};
