#include <stdio.h>

#include "xor.h"
#include "hex.h"

int main(int argc, char *argv[])
{
	char key[] = "ICE";
	char input[] = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
	//0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f
	char output[100] = { 0 };
	char outputhex[200] = { 0 };

	Xor::xorRepeatingKey((unsigned char *) input, (unsigned char *) output, (unsigned char *) key, sizeof(input) - 1, sizeof(key) - 1);
	Hex::encodeHex((unsigned char *) output, (unsigned char *) outputhex, sizeof(input) - 1);

	printf("%s\n", input);
	printf("%s\n", output);
	printf("%s\n", outputhex);
}
