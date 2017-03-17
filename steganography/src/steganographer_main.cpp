#include <cstdio>
#include <unistd.h>
#include <iostream>
#define cimg_use_png
#include "steganographer.h"
using namespace cimg_library;

int main()
{
	Steganographer::compress("lena.png","sample.txt");
	
#if 0

	CImg<unsigned char> image, visu(500,400,1,3,0);
	const unsigned char red[] = { 255,0,0 }, green[] = { 0,255,0 }, blue[] = { 0,0,255 };

	image.load("lena.png");
	unsigned char out;
	int height = image.height();
	int width = image.width();
	
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

	
	image.save("sample2.png");
	CImg<unsigned char> image2;
	image.load("sample2.png");
	
	height = image.height();
	width = image.width();
	a= 0;
	for(int x = 0; x < width; x++)
	{
		for(int y=0; y < height; y++)
		{
		//	std::cout <<"R: "<<int(image(x,y,0,0)) << " G: "<<int(image(x,y,0,1)) << " B: "<<int(image(x,y,0,2)) << " A: "<<int(image(x,y,0,3)) << std::endl;
			int expected = int(image(x,y,0,0));
			if(expected != vals[a])
				std::cout << "dang "<<x<<" "<<y<<"\n";
			a++;
		}
	}
	image.blur(2.5);
	CImgDisplay main_disp(image,"Click a point"), draw_disp(visu,"Intensity profile");
	while (!main_disp.is_closed() && !draw_disp.is_closed()) {
		main_disp.wait();
		if (main_disp.button() && main_disp.mouse_y()>=0) {
			const int y = main_disp.mouse_y();
			visu.fill(0).draw_graph(image.get_crop(0,y,0,0,image.width()-1,y,0,0),red,1,1,0,255,0);
			visu.draw_graph(image.get_crop(0,y,0,1,image.width()-1,y,0,1),green,1,1,0,255,0);
			visu.draw_graph(image.get_crop(0,y,0,2,image.width()-1,y,0,2),blue,1,1,0,255,0).display(draw_disp);
		}
	}
#endif
	return 0;
}
