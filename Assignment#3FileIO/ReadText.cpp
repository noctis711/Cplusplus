#include "FileReader.h"
#include "StringFunctions.h"

#include <iostream>
#include <vector>
#include <string>

int main(int argc, char * argv[])
{
	std::vector<std::string> strings;
	std::vector<int> alphaCount(26,0);
	char input;
	int count;
	try
	{
		FileReader in("wordlist.txt");
		while (!in.endOfFile())
		{
			std::string line = in.readLine();
			line = StringFunctions::toupper(line);
			if (line.size() > 0)
			{
				strings.push_back(line);
				char A = line.at(0);
				int B = A;
				alphaCount[B-65]++;
			}
		}
		while(true){
		std::cout << "Enter a capital letter from A-Z or q to quit. ";
		(std::cin >> input).ignore(1000, '\n');
		if(input == 'q'){
			return(0);
		}
		else{
			int B = input;
			count = alphaCount[B-65];
		}
		std::cout << "There are " << count << " words that start with "<< input <<std::endl;
		}

	
	}
	catch (std::string err)
	{
		std::cout << "Error: " << err << std::endl;
	}
}