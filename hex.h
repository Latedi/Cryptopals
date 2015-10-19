#ifndef HEX_H
#define HEX_H

#include <stdint.h>

#define SUCCESS		0
#define INVALID_HEX	1

class Hex
{
private:
	static const char hex[];

	static bool validateHex(unsigned char *data, uint32_t length);
	static void encodeByteHex(unsigned char *input, unsigned char *output);
	static void decodeByteHex(unsigned char *input, unsigned char *output);
	static uint8_t hexIndex(unsigned char *ch);
public:
	static uint32_t encodeHex(unsigned char *input, unsigned char *output, uint32_t length);
	static uint32_t decodeHex(unsigned char *input, unsigned char *output, uint32_t length);
};

#endif /* HEX_H */
