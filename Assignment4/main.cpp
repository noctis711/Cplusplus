#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <ctype.h>
#include "FileReader.h"
#include <algorithm>
#include <cstdlib>

using namespace std;

int main(int argc, char * argv[]){
	vector<int> strings;
	vector <vector<int>> imageValues;
	FileReader in1("PeskyImages/Pesky1.ppm");
	FileReader in2("PeskyImages/Pesky2.ppm");
	FileReader in3("PeskyImages/Pesky3.ppm");
	FileReader in4("PeskyImages/Pesky4.ppm");
	FileReader in5("PeskyImages/Pesky5.ppm");
	FileReader in6("PeskyImages/Pesky6.ppm");
	FileReader in7("PeskyImages/Pesky7.ppm");
	FileReader in8("PeskyImages/Pesky8.ppm");
	FileReader in9("PeskyImages/Pesky9.ppm");
	ofstream write;

	try
	{
		//cout << "before while" << endl;
		int count(0);

		//skip first 4 lines
		for(int i(0);i<4;i++){
			in1.readLine();
			in2.readLine();
			in3.readLine();
			in4.readLine();
			in5.readLine();
			in6.readLine();
			in7.readLine();
			in8.readLine();
			in9.readLine();
		}

		int w(495);
		int h(557);

		for(int i(0);i<(w*h*3);i++)
		{
			strings.push_back(atoi(in1.readLine().c_str()));
			strings.push_back(atoi(in2.readLine().c_str()));
			strings.push_back(atoi(in3.readLine().c_str()));
			strings.push_back(atoi(in4.readLine().c_str()));
			strings.push_back(atoi(in5.readLine().c_str()));
			strings.push_back(atoi(in6.readLine().c_str()));
			strings.push_back(atoi(in7.readLine().c_str()));
			strings.push_back(atoi(in8.readLine().c_str()));
			strings.push_back(atoi(in9.readLine().c_str()));
			
			sort(strings.begin(), strings.end());

			imageValues.push_back(strings);
			strings.clear();
			count++;
			//cout << "after image values" << endl;
		}
		
		//cout << "before open ppm" << endl;
		
		write.open("NotPesky.ppm");
		write << "P3" << endl;
		write << "#MY PPM Creator" << endl;
		write << w <<" "<< h << endl;
		write << "255" << endl;
		//cout << "count " << count <<endl;
		//cout << "image values size " << imageValues.size() <<endl;

		for(int i = 0; i < imageValues.size();i+=3){
			int red, green, blue;
			red = imageValues[i][4];
			green = imageValues[i+1][4];
			blue = imageValues[i+2][4];
			write << red << endl;
			write << green << endl;
			write << blue << endl;
			// 0 1 2 3 4 5 6 7 8
		}
		write.close();
		cout << "Your image is done." << endl;
		
	}
	catch (string err)
	{
		cout << "Error: " << err << endl;
	}

}
