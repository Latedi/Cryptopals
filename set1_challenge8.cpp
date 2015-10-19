#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>

#include "hex.h"
#include "identify.h"

#define BLOCKSIZE 16

int main(int argc, char *argv[])
{
	char filename[] = "8.txt";
	std::ifstream ifile(filename);
	std::string line;
	std::vector<std::string> lines;
	while(getline(ifile, line))
	{
		lines.push_back(line);
	}

	char data[4096];
	for(int i = 0; i < lines.size(); i++)
	{
		//Hex::decodeHex((unsigned char * ) lines[i].c_str(), (unsigned char *) data, lines[i].length());
		//uint32_t score = Identify::equalBlockScore((unsigned char *) data, lines[i].length() / 2, BLOCKSIZE);
		uint32_t score = Identify::equalBlockScore((unsigned char *) lines[i].c_str(), lines[i].length(), BLOCKSIZE * 2);
		if(score > 0)
		{
			printf("%d\n", i);
			return 0;
		}
	}
}
