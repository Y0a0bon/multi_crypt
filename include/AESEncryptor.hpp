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
	int getExpandedKeySize();
	int getSubkey(unsigned char *tmp, int ind);

	int subBytes(std::array<unsigned char, ARRAY_SIZE> &inputVector);
	int subBytes(unsigned char *inputVector, int size);

	int shiftRow(unsigned char *inputVector, int size);
	int shiftRows(std::array<unsigned char, ARRAY_SIZE> &inputVector);
	int shiftRows(unsigned char *inputVector, int size);
	
	int mixColumnsWord(unsigned char *multiplicator, unsigned char *word); 
	int mixColumns(std::array<unsigned char, ARRAY_SIZE> &inputVector);
	
	int getWordFromMatrix(unsigned char *word,unsigned char *matrix, int columns, int ind);
	int getWordFromMatrix(unsigned char *word, std::array<unsigned char, ARRAY_SIZE> &matrix, int ind);
	int putWordIntoMatrix(unsigned char *matrix, unsigned char *word, int columns, int ind);
	int putWordIntoMatrix(std::array<unsigned char, ARRAY_SIZE> &matrix, unsigned char *word, int ind);
	int getSubMatrix(unsigned char *dest, unsigned char *src, int columns, int ind);

	int xorArray(std::array<unsigned char, ARRAY_SIZE> &inputVector, unsigned char *subKey);
	int xorArray(unsigned char *inputVector, unsigned char *subKey, int size);
	
	int copyArray(unsigned char *dest, unsigned char *src, int size);
	int copyArrayToColumn(unsigned char *dest, unsigned char *src, int size, int ind);
	int copyColumnToArray(unsigned char *dest, unsigned char *src, int size, int ind);

	
	int keyExpansionComplete();

	int encryptBlock(std::array<unsigned char, ARRAY_SIZE> &inputVector);

	void encrypt(std::ifstream t_inputStream, std::ofstream t_outputStream);
	private :
	
	// Attributes
	std::ifstream m_inputStream;
	std::ofstream m_outputStream;
	unsigned char *m_key;
	unsigned int m_keySize;
	unsigned char *m_expandedKey;
	unsigned int m_expandedKeyWordSize;
	unsigned int m_rounds;

};

#endif
