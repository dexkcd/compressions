#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <string>
#include <sstream>

#define cimg_use_png
#include "steganographer.h"
using namespace cimg_library;

Steganographer::Steganographer(){}
Steganographer::~Steganographer(){}

int Steganographer::compress(const char *imageFile, const char *inputFile, const char *outputImage)
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
			for(int i = 7; i >= 0; i--)
			{
				  input << ((c >> i) & 1);
			}
			size++;
		} while (c != EOF);
		fclose (pFile);
		std::cout <<  int(c) <<" " <<EOF << std::endl;
	}

	std::cout << strlen(input.str().c_str())<<" "<<size <<std::endl;
	
	std::string bitlist = input.str();
	std::string::iterator it = bitlist.begin(); 
	
	CImg<unsigned char> image;
	std::cout <<imageFile<<std::endl;
	image.load(imageFile);
	unsigned char out;
	int height = image.height();
	int width = image.width();
	
	int vals[width*height];
	if(width*height <  strlen(input.str().c_str()))
		return -1;
	for(int x = 0; x < width; x++)
	{
		for(int y=0; y < height; y++)
		{
			for(int spect = 0; spect < 3; spect++) // iterate through spectrum
			{
				if(it == bitlist.end()) break;
				int r = int(image(x,y,0,spect));
				if(r%2==0 && *it=='1') //even shift to odd
					r = r + 1;
				else if(r%2==1 && *it=='0') //odd shift to even
					r = r - 1;
				image(x,y,spect) = r; 	
				it++;
			}
			if(it == bitlist.end()) break;
		}
		if(it == bitlist.end()) break;
	}
	image.save(outputImage);
	return 0;
}

int Steganographer::decompress(const char *imageFile, const char *outputfile)
{
	FILE * pFile;
	int c;
	int n = 0;

	pFile=fopen(outputfile, "w");
	int s=0;
	int sz=0;
	std::stringstream message;
	CImg<unsigned char> image;
	std::cout <<imageFile<<std::endl;
	image.load(imageFile);
	unsigned char out;
	int height = image.height();
	int width = image.width();
	std::string bits ="";
	for(int x = 0; x < width; x++)
	{
		for(int y=0; y < height; y++)
		{
			for(int spect = 0; spect < 3; spect++) // iterate through spectrum
			{
				int r = int(image(x,y,0,spect));
				bits+= (char(r%2) + '0');
				if(strlen(bits.c_str()) == 8)
				{
					char c = 0;
					int shift = 0;
					for(std::string::iterator it = bits.begin(); it != bits.end(); it++)
					{
						c = (c << 1) + (*it-'0');
						shift++;
					}
					if(bits.compare("11111111")==0)
						goto here;
						
					message << c;
					bits="";
				}
			}
		}
	}
	here:
	fprintf(pFile,"%s",message.str().c_str());
	fclose(pFile);
//	std::cout << message.str()<< std::endl;
	return 0;
}


