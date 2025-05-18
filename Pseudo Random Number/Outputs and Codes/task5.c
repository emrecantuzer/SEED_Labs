#include <stdio.h>
#include <stdlib.h>

#define LEN 16 // 128 bit = 16 byte

int main() {
    unsigned char *key = (unsigned char *) malloc(sizeof(unsigned char) * LEN);
	
	FILE* random = fopen("/dev/urandom", "r");
	if (!random) {
    perror("Not allowed open  /dev/urandom");
    return EXIT_FAILURE; }
	
    if (!key) {
    perror("Not allowed to allocate memory ");
    return EXIT_FAILURE; }



    fread(key, sizeof(unsigned char), LEN, random);
    fclose(random);

	printf("KEY: ");							
    for (int i = 0; i < LEN; i++) {
        printf("%.2x", key[i]);
    }
    printf("\n");
    free(key);
    return 0;
}
