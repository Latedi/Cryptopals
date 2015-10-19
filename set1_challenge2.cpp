#include <stdio.h>

#include "hex.h"
#include "xor.h"

int main(int argc, char *argv[])
{
	char i1[] = "1c0111001f010100061a024b53535009181c";
	char i2[] = "686974207468652062756c6c277320657965";
	char h1[100] = { 0 };
	char h2[100] = { 0 };
	Hex::decodeHex((unsigned char *) i1, (unsigned char *) h1, sizeof(i1) - 1);
	Hex::decodeHex((unsigned char *) i2, (unsigned char *) h2, sizeof(i2) - 1);
	char out[100] = { 0 };
	Xor::xorBuffers((unsigned char *) h1, (unsigned char *) h2, (unsigned char *) out, sizeof(i1) - 1);
	printf("%s\n", out);
}
