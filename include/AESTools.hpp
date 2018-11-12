#ifndef DEF_AES_TOOLS
#define DEF_AES_TOOLS

#include <array>
#include <cmath>

#define WORD_SIZE 4
#define SBOX_SIZE 256

    	// Rijndael S-box
	extern const unsigned char sbox[SBOX_SIZE];

    	// Rijndael Inverted S-box
    	extern const unsigned char rsbox[SBOX_SIZE];

	// mixColumn matrix
	extern const int coef[16];

	void printHex(unsigned char *vector, int size);
	int printVector(std::array<unsigned char, 16> vector);
	int printVector(unsigned char *vector, int size);
	int printVectorLine(unsigned char *vector, int size);
	int printMatrix(unsigned char *matrix, int columns, int lines);
	int printSubkey(unsigned char *matrix, int columns, int ind);

#endif
