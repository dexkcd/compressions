#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <string>
#include <sstream>

#define cimg_use_png
#include "steganographer.h"
using namespace cimg_library;

int Steganographer::compress(const char *imageFile, const char *inputFile)
{
	//Read the inputfile
	//
	FILE * pFile;
	int c;
	int n = 0;
	pFile=fopen(inputFile, "r");
	std::stringstream input("");
	int size=0;
	if (pFile==NULL) perror ("Error opening file");
	else
	{
		do {
			c = fgetc (pFile);
			for(int i = 0; i < 8; i++)
			{
				  input << ((c >> i) & 1);
			}
			size++;
		} while (c != EOF);
		fclose (pFile);
	}

	std::cout << strlen(input.str().c_str())<<" "<<size <<std::endl;

	CImg<unsigned char> image;
	std::cout <<imageFile<<std::endl;
	image.load(imageFile);
	unsigned char out;
	int height = image.height();
	int width = image.width();
/*	
	image.save("sample.png");
	int vals[width*height];
	int a = 0;
	image.load("sample.png");
	for(int x = 0; x < width; x++)
	{
		for(int y=0; y < height; y++)
		{
		//	std::cout <<"R: "<<int(image(x,y,0,0)) << " G: "<<int(image(x,y,0,1)) << " B: "<<int(image(x,y,0,2)) << " A: "<<int(image(x,y,0,3)) << std::endl;
			int r = int(image(x,y,0,0));
			image(x,y,0) = r >0 ? r-1 : r+1;
			vals[a] =  r >0 ? r-1 : r+1;
			a++;
		}
	}
	*/
	return 0;
}

int Steganographer::decompress(const char *image, const char *outputfile)
{
	return 0;
}


