#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define KEYSIZE 16

int main() {
    int i;
    char key[KEYSIZE];

    printf("Zaman: %lld\n", (long long) time(NULL));
    //srand(time(NULL));  

    for (i = 0; i < KEYSIZE; i++) {
        key[i] = rand() % 256;
        printf("%.2x", (unsigned char) key[i]);
    }
    printf("\n");
    return 0;
}
