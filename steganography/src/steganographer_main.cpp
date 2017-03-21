#include <cstdio>
#include <unistd.h>
#include <iostream>
#define cimg_use_png
#include "steganographer.h"
using namespace cimg_library;

int main(int arc, char *argv[])
{
	Steganographer steg;
	steg.compress("lena.png","sample.txt", "somesome.png");
	steg.decompress("somesome.png","sample2.txt");

	return 0;
}
