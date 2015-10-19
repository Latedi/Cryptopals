#include "xor.h"

void Xor::xorBuffers(unsigned char *input1, unsigned char *input2, unsigned char *output, uint32_t length)
{
	for(int i = 0; i < length; i++)
	{
		output[i] = input1[i] ^ input2[i];
	}
}

void Xor::xorBufferWithByte(unsigned char *input, unsigned char *output, int key, uint32_t length)
{
	for(int i = 0; i < length; i++)
	{
		output[i] = input[i] ^ key;
	}
}

void Xor::xorRepeatingKey(unsigned char *input, unsigned char *output, unsigned char *key, uint32_t bufferLength, uint32_t keyLength)
{
	for(int i = 0; i < bufferLength; i++)
	{
		output[i] = input[i] ^ key[i % keyLength];
	}
}
