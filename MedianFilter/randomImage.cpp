#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char * argv[])
{
	if (argc != 4)
	{
		cout << "Please specify filename, width, and height." << endl;
		return -1;
	}

	srand(time(NULL));

	ofstream ppmFile;
	ppmFile.open (argv[1]);
	int width = atoi(argv[2]);
	int height = atoi(argv[3]);

	ppmFile << "P3" << endl 
			<< "# CREATOR: randomImage.cpp" << endl 
			<< width << " " <<  height << endl 
			<< "255" << endl;
	for (int h = 0; h < height; h++)
	{
			for (int w = 0; w < width*3; w++)
			{
				ppmFile << rand()%256 << endl;
			}
	}
	ppmFile.close();	
}