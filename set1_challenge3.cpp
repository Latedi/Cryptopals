#include <stdio.h>
#include <string.h>

#include "hex.h"
#include "xor.h"
#include "identify.h"

int main(int argc, char *argv[])
{
	char input[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
	char data[100] = { 0 };
	Hex::decodeHex((unsigned char *) input, (unsigned char *) data, sizeof(input) - 1); 
	char output[100] = { 0 };
	int key = Identify::mostLikelyXorByte((unsigned char*) data, (sizeof(input) - 1) / 2);
	if(key != -1)
	{
		Xor::xorBufferWithByte((unsigned char *) data, (unsigned char *) output, key, (sizeof(input) - 1) / 2);
		printf("%s\n", output);
	}
	else
		printf("Could not find the key\n");
}
