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
	BIGNUM *Recover = BN_new();
	BIGNUM *Signature = BN_new();


	BN_hex2bn(&n,"AE1CD4DC432798D933779FBD46C6E1247F0CF1233595113AA51B450F18116115");
	BN_hex2bn(&e, "010001");
	//BN_hex2bn(&Signature, "643D6F34902D9C7EC90CB0B2BCA36C47FA37165C0005CAB026C0542CBDB6802F");
	BN_hex2bn(&Signature, "643D6F34902D9C7EC90CB0B2BCA36C47FA37165C0005CAB026C0542CBDB6803F"); //modified S
	BN_hex2bn(&Message, "4c61756e63682061206d697373696c652e"); //Launch a missile.
	

	BN_mod_exp(Recover, Signature, e, n, ctx);
	printBN("Original : ", Message);
	printBN("Recover  : ", Recover);
	
	if (BN_cmp(Message, Recover)==0){
		printf("Valid Signature!\n");
	}
	else {
		printf("Not Valid Signature!\n");
	}
	bn2free_func(n, e, Message, Recover, Signature);
	BN_CTX_free(ctx);
	
	return 0;
}