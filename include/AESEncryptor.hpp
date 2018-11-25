#ifndef DEF_AES_ENCRYPTOR
#define DEF_AES_ENCRYPTOR

#include <fstream>
#include <array>

#include "AESManipulator.hpp"

class AESEncryptor : public AESManipulator
{

	public :
	
	// Constructor
	AESEncryptor(unsigned char *t_key, unsigned int t_keySize);

	// Destructor
	~AESEncryptor();

	// Methods
	int keyExpansionComplete();

	int getExpandedKeySize();
	int getSubkey(unsigned char *tmp, int ind);

	int subBytes(std::array<unsigned char, ARRAY_SIZE> &inputVector);
	int subBytes(unsigned char *inputVector, int size);

	int shiftRow(unsigned char *inputVector, int size);
	int shiftRows(std::array<unsigned char, ARRAY_SIZE> &inputVector);
	int shiftRows(unsigned char *inputVector, int size);
	
	int mixColumnsWord(unsigned char *multiplicator, unsigned char *word); 
	int mixColumns(std::array<unsigned char, ARRAY_SIZE> &inputVector);
	
	int encryptBlock(std::array<unsigned char, ARRAY_SIZE> &inputVector);

	void encrypt(std::ifstream t_inputStream, std::ofstream t_outputStream);

	private :

};

#endif
