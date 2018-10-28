#ifndef DEF_AES_ENCRYPTOR
#define DEF_AES_ENCRYPTOR

#include <fstream>

class AESEncryptor
{

	public :
	
	// Constructor
	AESEncryptor(unsigned char *t_key, unsigned int t_keySize);

	// Methods
	void subBytes();
	void shiftRows();
	void mixColumns();
	void addRoundKey();

	int getThree();

	void encrypt(std::ifstream t_inputStream, std::ofstream t_outputStream);

	private :
	
	// Attributes
	std::ifstream m_inputStream;
	std::ofstream m_outputStream;
	unsigned char *m_key;
	unsigned int m_keySize;

};

#endif
