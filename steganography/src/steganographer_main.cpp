#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <iostream>
#define cimg_use_png
#include "steganographer.h"
using namespace cimg_library;

int main(int argc, char *argv[])
{
	Steganographer steg;
	if(argc < 3)
	{
		std::cout << "Missing arguments" << std::endl
				<< "Usage:\n\t Compression: " << argv[0] << " compress <imagefile> <input file> <output image>" << std::endl
				<< "\t Decompression: " << argv[0] << " decompress <imagefile> <output file>" << std::endl;
		return 0;
	}
	if(strcmp(argv[1], "compress")==0 && argc == 5)
	{
		steg.compress(argv[2], argv[3], argv[4]);
	}
	else if(strcmp(argv[1], "decompress")==0 && argc == 4)
	{
		steg.decompress(argv[2], argv[3]);
	}
	else
	{
		std::cout << "Wrong usage. Number of Args: "<< argc << std::endl
				<< "Usage:\n\t Compression: " << argv[0] << " compress <imagefile> <input file> <output image>" << std::endl
				<< "\t Decompression: " << argv[0] << " decompress <imagefile> <output file>" << std::endl;
		return 0;
	}

	return 0;
}
