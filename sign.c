/*
 ============================================================================
 Name        : sign.c
 Author      : Víctor Jesús
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>

 int main(int argn, char *argv[]) {

 	FILE *f;
 	unsigned char* buffer;
 	unsigned char md[SHA512_DIGEST_LENGTH];
 	int leidos;
 	SHA512_CTX context;

 	int length = 1000;

 	if (argn != 2) {
 		printf("Usage: %s fichero\n", argv[0]);
 		return -1;
 	}

 	f = fopen(argv[1], "rb");

 	if (f == NULL) {
 		perror("No se puede abrir el fichero");
 		return -1;
 	}

 	if (!SHA512_Init(&context))
 		return -1;
 	buffer = (unsigned char*) malloc ( length*sizeof(unsigned char));
 	leidos = fread (buffer,sizeof(unsigned char), length, f);
 	while (leidos!=0)
 	{
 		if (!SHA512_Update(&context, (unsigned char*) buffer, leidos))
 			return -1;
 		leidos = fread (buffer, 1, length, f);
 	}

 	SHA512_Final(md, &context);

 	for (int i = 0; i < SHA512_DIGEST_LENGTH; i++) {
 		printf("%02x",md[i]);
 	}
 	printf("\n");


 	return EXIT_SUCCESS;
 }


//gcc -Wall -g sign.c -lssl -lcrypto -Wno-deprecated-declarations -o sign
// para imprimir en exadecimal %02x
//SHA512_DIGEST_LENGTH    64 constante para SHA512
