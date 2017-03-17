#include "CImg.h"

class Steganographer
{
	Steganographer();
	~Steganographer();
	public:
		static int compress(const char *imageFile, const char *inputfile);
		static int decompress(const char *imageFile, const char *inputfile);

};
