#ifndef IDENTIFY_H
#define IDENTIFY_H

#include <stdint.h>
#include <vector>
#include <string>
#include <cstring>
#include <stdio.h>

#include "xor.h"

class Identify
{
private:
	static const char plaintext[];

	static uint32_t countPlaintext(unsigned char *input, uint32_t length);
	static bool hasTripleLetters(unsigned char *input, uint32_t length);
	static bool nullsInText(unsigned char *input, uint32_t length);
public:
	static bool isEnglish(unsigned char *input, uint32_t length);
	static uint32_t mostLikelyXorByte(unsigned char *input, uint32_t length);
	static std::vector<uint32_t> mostLikelyXorByte(std::vector<std::string>& input, uint32_t length);
	static uint32_t mostLikelyXorByteMixed(unsigned char *input, uint32_t length);
	static uint32_t hammingDistance(unsigned char *buffer1, unsigned char *buffer2, uint32_t length);
	static uint32_t equalBlockScore(unsigned char *buffer, uint32_t bufferLength, uint32_t blockLength);
};

#endif /* IDENTIFY_H */
