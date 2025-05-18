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

void bn2free_func(BIGNUM *bn1, BIGNUM *bn2, BIGNUM *bn3, BIGNUM *bn4, BIGNUM *bn5, BIGNUM *bn6, BIGNUM *bn7, BIGNUM *bn8)
{
BN_free(bn1);
BN_free(bn2);
BN_free(bn3);
BN_free(bn4);
BN_free(bn5);
BN_free(bn6);
BN_free(bn7);
BN_free(bn8);
}

int main ()
{
	BN_CTX *ctx = BN_CTX_new();
	BIGNUM *p = BN_new(); BIGNUM *q = BN_new(); BIGNUM *e = BN_new();
	BIGNUM *n = BN_new(); BIGNUM *phi_n = BN_new();
	BIGNUM *d = BN_new();
	BIGNUM *p_m1 = BN_new(); BIGNUM *q_m1 = BN_new();
	BIGNUM *one = BN_new();

	// Initialize p, q, e and one
	BN_hex2bn(&one, "1");
	BN_hex2bn(&p, "F7E75FDC469067FFDC4E847C51F452DF");
	BN_hex2bn(&q, "E85CED54AF57E53E092113E62F436F4F");
	BN_hex2bn(&e, "0D88C3");
	
	
	// n = p*q
	BN_mul(n, p, q, ctx);
	printBN("(p * q) = ", n);
	
	// p-1, q-1
	BN_sub(p_m1,p,one);
	BN_sub(q_m1,q,one);
	
	// phi(n) = (p-1)(q-1)
	BN_mul(phi_n, p_m1, q_m1, ctx);
	printBN("(p-1) * (q-1) = ", phi_n);

	// d = eˆ-1 mod phi_n
	BN_mod_inverse(d, e, phi_n, ctx);
	printBN("Key = ", d);
	
	bn2free_func(p, q, e, n, phi_n, d, p_m1, q_m1);
    BN_CTX_free(ctx);
	
	return 0;
}