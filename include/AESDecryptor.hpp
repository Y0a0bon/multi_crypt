#ifndef DEF_AES_DECRYPTOR
#define DEF_AES_DECRYPTOR

#include <fstream>
#include <array>

#define ARRAY_SIZE 16
#define BLOCK_SIZE 128

class AESDecryptor
{

	public :
	
	// Constructor
	AESDecryptor(unsigned char *t_key, unsigned int t_keySize);

	// Destructor
	~AESDecryptor();

	int subBytes(std::array<unsigned char, ARRAY_SIZE> &inputVector);
	int subBytes(unsigned char *inputVector, int size);

	int shiftRow(unsigned char *inputVector, int size);
	int shiftRows(std::array<unsigned char, ARRAY_SIZE> &inputVector);
	int shiftRows(unsigned char *inputVector, int size);
	
	int mixColumnsWord(unsigned char *multiplicator, unsigned char *word); 
	int mixColumns(std::array<unsigned char, ARRAY_SIZE> &inputVector);
	
	private :
	
	// Attributes
	std::ifstream m_inputStream;
	std::ofstream m_outputStream;
	unsigned char *m_key;
	unsigned int m_keySize;
	unsigned char *m_expandedKey;
	unsigned int m_expandedKeyWordSize;
	unsigned int m_rounds;

}
#endif
