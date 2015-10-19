#include "hex.h"

const char Hex::hex[] = "0123456789abcdef";

bool Hex::validateHex(unsigned char *data, uint32_t length)
{
	if(length % 2 != 0)
		return false;
	for(int i = 0; i < length; i++)
	{
		bool found = false;
		for(int j = 0; j < 16; j++)
		{
			if(Hex::hex[j] == data[i])
			{
				found = true;
				break;
			}
		}
		if(!found)
			return false;
	}
	return true;
}

void Hex::encodeByteHex(unsigned char *input, unsigned char *output)
{
	output[0] = Hex::hex[(int) input[0] >> 4];
	output[1] = Hex::hex[(int) input[0] & 0xf];
}

void Hex::decodeByteHex(unsigned char *input, unsigned char *output)
{
	output[0] = hexIndex(&input[0]) << 4 & 0xf0;
	output[0] += hexIndex(&input[1]);
}

uint8_t Hex::hexIndex(unsigned char *ch)
{
	for(int i = 0; i < 16; i++)
	{
		if(*ch == hex[i])
			return i;
	}
}

uint32_t Hex::encodeHex(unsigned char *input, unsigned char *output, uint32_t length)
{
	for(int i = 0; i < length; i++)
	{
		Hex::encodeByteHex(input + i, output + (i * 2));
	}
	return SUCCESS;
}

uint32_t Hex::decodeHex(unsigned char *input, unsigned char *output, uint32_t length)
{
	if(!Hex::validateHex(input, length))
		return INVALID_HEX;
	for(int i = 0; i < length; i += 2)
	{
		Hex::decodeByteHex(input + i, output + (i / 2));
	}
	return SUCCESS;
}
