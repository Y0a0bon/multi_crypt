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

	// Destructor
	~AESEncryptor();

	// Methods
	int subBytes(std::array<unsigned char, ARRAY_SIZE> &inputVector);
	int subBytes(unsigned char *inputVector, int size);

	int shiftRows(std::array<unsigned char, ARRAY_SIZE> &inputVector);
	int shiftRows(unsigned char *inputVector, int size);
	
	int mixColumns(std::array<unsigned char, ARRAY_SIZE> &inputVector);
	
	int addRoundKey(std::array<unsigned char, ARRAY_SIZE> &inputVector, unsigned char *subKey);
	int addRoundKey(unsigned char *inputVector, unsigned char *subKey, int size);
	
	int copyArray(unsigned char *dest, unsigned char *src, int size);
	void printHex(unsigned char *vector, int size);
	
	int keyExpansion(unsigned char *subKey);

	int encryptBlock(std::array<unsigned char, ARRAY_SIZE> &inputVector);

	void encrypt(std::ifstream t_inputStream, std::ofstream t_outputStream);

	int printVector(std::array<unsigned char, 16> vector);
	int printVector(unsigned char *vector, int size);
	int printVectorLine(unsigned char *vector, int size);

	private :
	
	// Attributes
	std::ifstream m_inputStream;
	std::ofstream m_outputStream;
	unsigned char *m_key;
	unsigned int m_keySize;
	unsigned int m_rounds;

};

#endif
