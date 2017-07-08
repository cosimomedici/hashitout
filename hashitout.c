#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/file.h>

#include <openssl/md5.h>
#include <openssl/sha.h>

#define CHUNK_SIZE			1024
#define MAX_PATH_SIZE		4096
#define FINAL_HASH_SIZE		16
#define FINAL_BUFFER_SIZE	40

#define EOS(str) ((str) + strlen(str))

char *hio_md5(const char *);
char *hio_sha256(const char *);

int main(int argc, char *argv[])
{
	char fhash[FINAL_BUFFER_SIZE];
	char *hptr;

	hptr = fhash;

	if(argc < 2) {
		fprintf(stderr, "Usage: %s <file to get md5sum of>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	memset(fhash, '\0', FINAL_BUFFER_SIZE);
	hptr = hio_md5((const char *)argv[1]);

	if(fhash == NULL) {
		printf("Could not calculate the hash.\n");
		exit(EXIT_FAILURE);
	}
	
	printf("final hash = %s\n", hptr);
	free(hptr);

	return(0);
}


char *hio_md5(const char *fpath)
{
	int i, bytes;
	FILE *inputfile;
	SHA_CTX mdcontext;
	unsigned char chunks[CHUNK_SIZE];
	unsigned char c[MD5_DIGEST_LENGTH];
	char *fptr;

	if((fptr = malloc(sizeof(unsigned char) * FINAL_BUFFER_SIZE)) == NULL) {
		fprintf(stderr, "Failed to allocate memory for the digest buffer in hex.\n");
		return NULL;
	}

	/* Zero the buffers, so they are initialized. */
	memset(chunks, '\0', CHUNK_SIZE);
	memset(c, '\0', MD5_DIGEST_LENGTH);
	memset(fptr, '\0', FINAL_BUFFER_SIZE);

	if((inputfile = fopen(fpath, "rb")) == NULL) {
		fprintf(stderr, "%s could not be opened.\n", fpath);
		return(NULL);
	}

	MD5_Init(&mdcontext);

	while((bytes = fread(chunks, 1, CHUNK_SIZE, inputfile)) != 0) {
		MD5_Update(&mdcontext, chunks, bytes);
	}

	MD5_Final(c, &mdcontext);


	/* Populate the buffer that holds final hash with each part */
	for(i = 0; i < MD5_DIGEST_LENGTH; i++) {
		sprintf(EOS(fptr), "%02x", c[i]);
	}

	/* Debug option to print the digest in this function */
	printf("in hio_md5() -- %s\n", fptr);

	return(fptr);

}


char *hio_sha256(const char *fpath)
{
	int i, bytes;
	FILE *inputfile;
	MD5_CTX mdcontext;
	unsigned char chunks[CHUNK_SIZE];
	unsigned char c[MD5_DIGEST_LENGTH];
	char *fptr;

	if((fptr = malloc(sizeof(unsigned char) * FINAL_BUFFER_SIZE)) == NULL) {
		fprintf(stderr, "Failed to allocate memory for the digest buffer in hex.\n");
		return NULL;
	}

	/* Zero the buffers, so they are initialized. */
	memset(chunks, '\0', CHUNK_SIZE);
	memset(c, '\0', SHA256_DIGEST_LENGTH);
	memset(fptr, '\0', FINAL_BUFFER_SIZE);
	memset(finalhash, '\0', FINAL_BUFFER_SIZE);

	if((inputfile = fopen(fpath, "rb")) == NULL) {
		fprintf(stderr, "%s could not be opened.\n", fpath);
		return(NULL);
	}

	SHA256_Init(&mdcontext);

	while((bytes = fread(chunks, 1, CHUNK_SIZE, inputfile)) != 0) {
		MD5_Update(&mdcontext, chunks, bytes);
	}

	SHA256_Final(c, &mdcontext);


	/* Populate the buffer that holds final hash with each part */
	for(i = 0; i < MD5_DIGEST_LENGTH; i++) {
		sprintf(EOS(fptr), "%02x", c[i]);
	}

	/* Debug option to print the digest in this function */
	printf("in hio_md5() -- %s\n", fptr);

	return(fptr);

}

