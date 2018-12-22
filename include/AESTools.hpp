#ifndef DEF_AES_TOOLS
#define DEF_AES_TOOLS

#include <array>
#include <cmath>

#define WORD_SIZE 4
#define SBOX_SIZE 256

#define FUNC_OK 0x0
#define FUNC_ERROR 0x1
#define INPUT_ERROR 0x2
#define UNKNOWN_ERROR 0x3
#define NOT_IMPLEMENTED 0x4

    	// Rijndael S-box
	extern const unsigned char sbox[SBOX_SIZE];

    	// Rijndael Inverted S-box
    	extern const unsigned char rsbox[SBOX_SIZE];

	// mixColumn matrix
	extern const unsigned char coef[16];

	void printHex(unsigned char *vector, int size);
	int printVector(std::array<unsigned char, 16> vector);
	int printVector(unsigned char *vector, int size);
	int printVectorLine(unsigned char *vector, int size);
	int printMatrix(unsigned char *matrix, int columns, int lines);
	int printSubkey(unsigned char *matrix, int columns, int ind);
	bool compareArray(unsigned char *input, unsigned char *output, int size);

	// Random number as unsigned char
	//int getRand(unsigned char *buf, unsigned int length, int custom_seed);
	int getRand(unsigned char *buf, unsigned int length);

#endif
