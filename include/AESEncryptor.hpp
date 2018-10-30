#ifndef DEF_AES_ENCRYPTOR
#define DEF_AES_ENCRYPTOR

#include <fstream>
#include <array>

#define ARRAY_SIZE 16
#define BLOCK_SIZE 128

class AESEncryptor
{

	public :
	
	// Constructor
	AESEncryptor(unsigned char *t_key, unsigned int t_keySize);

	// Methods
	int subBytes(std::array<unsigned char, ARRAY_SIZE> &inputVector);
	int shiftRows(std::array<unsigned char, ARRAY_SIZE> &inputVector);
	void mixColumns(std::array<unsigned char, ARRAY_SIZE> &inputVector);
	void addRoundKey();

	void encrypt(std::ifstream t_inputStream, std::ofstream t_outputStream);

	private :
	
	// Attributes
	std::ifstream m_inputStream;
	std::ofstream m_outputStream;
	unsigned char *m_key;
	unsigned int m_keySize;

};

#endif
