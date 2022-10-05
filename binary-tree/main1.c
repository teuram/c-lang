#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sha256.h"

int cmp_sha256(char a[32], char b[32]) {
    for(int i = 0; i < 32; i++) {
        if(a[i] ^ b[i]) return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {

    char str[64];
    memset(&str, 0, 64);

    printf("enter string: ");
    scanf("%s", &str);
    printf("length of string: %d\r\n", strlen(str));

    char* tt = sha256(&str, strlen(str), NULL);

    for(int i = 0; i < strlen(tt); i++) {
        printf("%02x", *(tt + i));
    }
    puts("\r\n");

    return 0;
}

