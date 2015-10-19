#include <stdio.h>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>

#include "hex.h"
#include "identify.h"
#include "xor.h"

int main(int argc, char *argv[])
{
	char filename[] = "4.txt";
	std::ifstream ifile(filename);

	char data[31] = { 0 };
	std::vector<std::string> lines;
	std::string line;
	while(getline(ifile, line))
	{
		Hex::decodeHex((unsigned char *) line.c_str(), (unsigned char *) data, 60);
		lines.push_back(std::string(data));
	}

	std::vector<uint32_t> key = Identify::mostLikelyXorByte(lines, 30);

	if(key[0] != -1 && key[1] != -1)
	{
		Xor::xorBufferWithByte((unsigned char *) lines[key[1]].c_str(), (unsigned char *) data, key[0], 30);
		printf("%s", data);
	}
	else
		printf("Could not find the key\n");
}
