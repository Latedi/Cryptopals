#include "b64.h"

const char B64::b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void B64::encodeBlockB64(unsigned char *input, unsigned char *output, int length)
{
	output[0] = b64[(int) input[0] >> 2];
	output[1] = b64[(int) (input[0] << 4 & 0x30 | input[1] >> 4)];
	output[2] = (length > 1 ? b64[(int) (input[1] << 2 & 0x3c | input[2] >> 6)] : '=');
	output[3] = (length > 2 ? b64[(int) (input[2] & 0x3f)] : '=');
}

void B64::decodeBlockB64(unsigned char *input, unsigned char *output)
{
	int indices[4];
	for(int i = 0; i < 4; i++)
	{
		if(input[i] != '=')
			indices[i] = b64Index(&input[i]);
		else
			indices[i] = 0;
	}
	output[0] = indices[0] << 2 | indices[1] >> 4;
	output[1] = indices[1] << 4 & 0xf0 | indices[2] >> 2;
	output[2] = indices[2] << 6 & 0xc0 | indices[3];
}

bool B64::validateB64(unsigned char *data, uint32_t length)
{
	if(length % 4 != 0)
		return false;
	for(int i = 0; i < length; i++)
	{
		bool found = false;
		for(int j = 0; j < 64; j++)
		{
			if(data[i] == b64[j])
			{
				found = true;
				break;
			}
		}
		if(!found)
		{
			if(data[i] != '=' || i < length - 2)
				return false;
		}
	}
	return true;
}

uint32_t B64::b64Index(unsigned char *ch)
{
	for(int i = 0; i < 64; i++)
	{
		if(*ch == b64[i])
			return i;
	}
}

uint32_t B64::encodeB64(unsigned char *input, unsigned char *output, uint32_t length)
{
	int i;
	for(i = 0; i < length; i += 3)
	{
		B64::encodeBlockB64(input + i, output + (i / 3 * 4), (length >= i + 3 ? 3 : length - i));
	}
	return SUCCESS;
}

uint32_t B64::decodeB64(unsigned char *input, unsigned char *output, uint32_t length)
{
	if(!B64::validateB64(input, length))
		return INVALID_B64;
	for(int i = 0; i < length; i+= 4)
	{
		B64::decodeBlockB64(input + i, output + (i / 4 * 3));
	}
	return SUCCESS;
}
