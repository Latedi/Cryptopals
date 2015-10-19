#include <stdio.h>
#include <openssl/aes.h>
#include <string>
#include <fstream>
#include <string.h>

#include "b64.h"

int main(int argc, char *argv[])
{
	char input[4096] = { 0 };
	char data[4096] = { 0 };
	char output[4096] = { 0 };
	char charkey[] = "YELLOW SUBMARINE";
	char filename[] = "7.txt";

	AES_KEY key;
	AES_set_decrypt_key((unsigned char *) charkey, 128, &key);

	std::ifstream ifile(filename);
	std::string line;
	while(getline(ifile, line))
	{
		strcpy(input + strlen(input), line.c_str());
	}
	uint32_t dataLength = strlen(input) / 4 * 3;
	B64::decodeB64((unsigned char *) input, (unsigned char *) data, strlen(input));

	for(int i = 0; i < dataLength; i += AES_BLOCK_SIZE)
	{
		AES_decrypt((unsigned char *) data + i, (unsigned char *) output + i, &key);
	}

	printf("%s\n", output);
}
