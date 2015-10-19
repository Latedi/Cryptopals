#ifndef B64_H
#define B64_H

#include <stdint.h>

#define SUCCESS		0
#define INVALID_B64	1

class B64
{
//private:
public:
	static const char b64[];

	//Encode 1-3 bytes to 4
	static void encodeBlockB64(unsigned char *input, unsigned char *output, int length);
	//Decode 4 bytes to 1-3
	static void decodeBlockB64(unsigned char *input, unsigned char *output);
	//Divisible by 4 and containing only b64 characters and the =
	static bool validateB64(unsigned char *data, uint32_t length);
	//Get the b64 value from a character
	static uint32_t b64Index(unsigned char *ch);
public:
	//Encode data to b64
	static uint32_t encodeB64(unsigned char *input, unsigned char *output, uint32_t length);
	//Decode b64 to data
	static uint32_t decodeB64(unsigned char *input, unsigned char *output, uint32_t length);
};

#endif /* B64_H */
