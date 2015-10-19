#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

#include "b64.h"
#include "identify.h"
#include "hex.h"

#define MAXSIZE 40

struct keyHammingPair
{
	int keysize;
	float hdNormalized;
};
bool sortKHP(const keyHammingPair &khp1, const keyHammingPair &khp2)
{
	return khp1.hdNormalized < khp2.hdNormalized;
}

int main(int argc, char *argv[])
{
	char filename[] = "6.txt";
	std::ifstream ifile(filename);
	std::string line;
	char input[4096] = { 0 };
	while(getline(ifile, line))
	{
		strcpy(input + strlen(input), line.c_str());
	}

	char data[4096] = { 0 };
	uint32_t dataLength = strlen(input) / 4 * 3;

	B64::decodeB64((unsigned char *) input, (unsigned char *) data, strlen(input));

	std::vector<keyHammingPair> keysizes;
	for(int i = 2; i < MAXSIZE; i++)
	{
		uint32_t distance = Identify::hammingDistance((unsigned char *) input, (unsigned char *) input + i, i);
		float newNormalized = (float) distance / (float) i;

		keyHammingPair newPair;
		newPair.keysize = i;
		newPair.hdNormalized = newNormalized;
		keysizes.push_back(newPair);
	}

	std::sort(keysizes.begin(), keysizes.end(), sortKHP);

	for(int j = 0; j < keysizes.size(); j++)
	{
		int keysize = keysizes[j].keysize;
		std::vector<std::string> transposedBlocks;
		for(int i = 0; i < keysize; i++)
			transposedBlocks.push_back("");
		for(int i = 0; i < dataLength; i++)
		{
			transposedBlocks[i % keysize] += data[i];
		}

		char finalKey[MAXSIZE] = { 0 };
		for(int i = 0; i < transposedBlocks.size(); i++)
		{
			int subKey = Identify::mostLikelyXorByteMixed((unsigned char *) transposedBlocks[i].c_str(), transposedBlocks[i].length());
			finalKey[i] = (char) subKey;
		}

		char output[4096] = { 0 };
		Xor::xorRepeatingKey((unsigned char *) data, (unsigned char *) output, (unsigned char *) finalKey, strlen(input) / 4 * 3, strlen(finalKey));
		if(Identify::isEnglish((unsigned char *) output, strlen(output)))
		{
			printf("%s\n", output);
			printf("Key = %s\n", finalKey);
			return 0;
		}
	}
	printf("No key found\n");
}
