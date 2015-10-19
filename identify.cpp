#include "identify.h"

const char Identify::plaintext[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ .,-!?'";

uint32_t Identify::countPlaintext(unsigned char *input, uint32_t length)
{
	int count = 0;
	for(int i = 0; i < length; i++)
	{
		for(int j = 0; j < sizeof(plaintext); j++)
		{
			if(input[i] == plaintext[j])
			{
				count++;
				break;
			}
		}
	}
	return count;
}

bool Identify::isEnglish(unsigned char *input, uint32_t length)
{
	if(length == 0)
		return false;
	int count = Identify::countPlaintext(input, length);
	if(count == 0)
		return false;
	if((float) count / (float) length < 0.95f)
		return false;
	bool hasTriples = Identify::hasTripleLetters(input, length);
	if(hasTriples)
		return false;
	if(nullsInText(input, length))
		return false;

	return true;
}

bool Identify::hasTripleLetters(unsigned char *input, uint32_t length)
{
	for(int i = 0; i < length - 2; i++)
	{
		unsigned char ch = input[i];
		if(input[i + 1] == ch && input[i + 2] == ch)
		{
			return true;
		}
	}
	return false;
}

bool Identify::nullsInText(unsigned char *input, uint32_t length)
{
	for(int i = 0; i < length; i++)
	{
		if(input[i] == (unsigned char) 0)
			return true;
	}
	return false;
}

uint32_t Identify::mostLikelyXorByte(unsigned char *input, uint32_t length)
{
	char *output = new char[length];
	uint32_t ret = -1;
	for(int i = 0; i < 256; i++)
	{
		if(Identify::isEnglish((unsigned char *) output, length))
		{
			ret = i;
			break;
		}
	}
	delete[] output;
	return ret;
}

std::vector<uint32_t> Identify::mostLikelyXorByte(std::vector<std::string>& input, uint32_t length)
{
	std::vector<uint32_t> ret;
	ret.push_back(-1);
	ret.push_back(-1);

	for(int j = 0; j < input.size(); j++)
	{
		int ml = Identify::mostLikelyXorByte((unsigned char *) input[j].c_str(), length);
		if(ml != -1)
		{
			ret[0] = ml;
			ret[1] = j;
			break;
		}
	}

	return ret;
}

uint32_t Identify::mostLikelyXorByteMixed(unsigned char *input, uint32_t length)
{
	int key[2] = { 0 };
	char *output = new char[length + 1];
	for(int i = 0; i < 256; i++)
	{
		Xor::xorBufferWithByte((unsigned char *) input, (unsigned char *) output, i, length);
		output[length] = (char) 0;
		int count = Identify::countPlaintext((unsigned char *) output, length);
		if(count > key[1])
		{
			key[0] = i;
			key[1] = count;
		}
	}
	delete[] output;
	return key[0];
}

uint32_t Identify::hammingDistance(unsigned char *buffer1, unsigned char *buffer2, uint32_t length)
{
	uint32_t total = 0;
	uint8_t xord;

	for(int i = 0; i < length; i++)
	{
		xord = ((uint8_t) buffer1[i] ^ (uint8_t) buffer2[i]);
		for(int j = 0; j < 8; j++)
		{
			if(xord & 0x1 == 1)
				total++;
			xord >>= 1;
		}
	}

	return total;
}

uint32_t Identify::equalBlockScore(unsigned char *buffer, uint32_t bufferLength, uint32_t blockLength)
{
	uint32_t score = 0;
	for(int i = 0; i < bufferLength; i += blockLength)
	{
		for(int j = i + blockLength; j < bufferLength; j += blockLength)
		{
			bool same = true;
			for(int k = 0; k < blockLength; k++)
			{
				if(buffer[i + k] != buffer[j + k])
				{
					same = false;
					break;
				}
			}
			if(same)
				score++;
		}
	}
	return score;
}
