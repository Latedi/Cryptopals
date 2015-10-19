#include "b64.h"
#include "hex.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char input[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
	char output[100] = { 0 };
	char temp[100] = { 0 };

	Hex::decodeHex((unsigned char *) input, (unsigned char *) temp, sizeof(input) - 1);
	B64::encodeB64((unsigned char *) temp, (unsigned char *) output, strlen(temp));
	printf("%s\n", output);

	//Expected output:
	//SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t

	return 0;
}
