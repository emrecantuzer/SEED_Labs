#include <stdio.h>
#include <openssl/bn.h>
#define NBITS 256

void printBN(char *msg, BIGNUM * a)
{
	/* Use BN_bn2hex(a) for hex string
	* Use BN_bn2dec(a) for decimal string */
	char * number_str = BN_bn2hex(a);
	printf("%s %s\n", msg, number_str);
	OPENSSL_free(number_str);
}

void bn2free_func(BIGNUM *bn1, BIGNUM *bn2, BIGNUM *bn3, BIGNUM *bn4, BIGNUM *bn5)
{
BN_free(bn1);
BN_free(bn2);
BN_free(bn3);
BN_free(bn4);
BN_free(bn5);
}


int main ()
{
	BN_CTX *ctx = BN_CTX_new();
	BIGNUM *n = BN_new();
	BIGNUM *e = BN_new();
	BIGNUM *Message = BN_new();
	BIGNUM *d = BN_new();
	BIGNUM *Signature = BN_new();

	// Initialize n, e, d and C
	BN_hex2bn(&n,"DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");
	BN_hex2bn(&e, "010001");
	BN_hex2bn(&d, "74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");
	//BN_hex2bn(&Message, "49206f776520796f752024323030302e"); //I owe you $2000.
	BN_hex2bn(&Message, "49206f776520796f752024333030302e"); //I owe you $3000.
	
	// Digital signature: S = E(PR_a, H(M)) = Mˆd mod n
	BN_mod_exp(Signature, Message, d, n, ctx);
	printBN("Signature : ", Signature);
	bn2free_func(n, e, Message, d, Signature);
	BN_CTX_free(ctx);
	return 0;
}