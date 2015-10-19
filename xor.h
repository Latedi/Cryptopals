#ifndef XOR_H
#define XOR_H

#include <stdint.h>

class Xor
{
//private:

public:
	static void xorBuffers(unsigned char *input1, unsigned char *input2, unsigned char *output, uint32_t length);
	static void xorBufferWithByte(unsigned char *input, unsigned char *output, int key, uint32_t length);
	static void xorRepeatingKey(unsigned char *input, unsigned char *output, unsigned char *key, uint32_t bufferLength, uint32_t keyLength);
};

#endif /* XOR_H */
