#ifndef DEF_AES_DECRYPTOR
#define DEF_AES_DECRYPTOR

#include <fstream>
#include <array>

#include "AESManipulator.hpp"

class AESDecryptor : public AESManipulator
{

	public :
	
	// Constructor
	AESDecryptor(unsigned char *t_key, unsigned int t_keySize);

	// Destructor
	~AESDecryptor();

	int keyExpansionComplete();

	int getExpandedKeySize();
	int getSubkey(unsigned char *tmp, int ind);

	int invSubBytes(std::array<unsigned char, ARRAY_SIZE> &inputVector);
	int invSubBytes(unsigned char *inputVector, int size);

	int invShiftRow(unsigned char *inputVector, int size);
	int invShiftRows(std::array<unsigned char, ARRAY_SIZE> &inputVector);
	int invShiftRows(unsigned char *inputVector, int size);
	
	int invMixColumnsWord(unsigned char *multiplicator, unsigned char *word); 
	int invMixColumns(std::array<unsigned char, ARRAY_SIZE> &inputVector);

	int subBytes(unsigned char *inputVector, int size);
	int shiftRow(unsigned char *inputVector, int size);

	int equivalentCipherExpansion();

	int decryptBlock(std::array<unsigned char, ARRAY_SIZE> &inputVector);

	private :
	
};

#endif
