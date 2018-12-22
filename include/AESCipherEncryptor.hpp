#ifndef DEF_AES_CIPHER_ENCRYPTOR
#define DEF_AES_CIPHER_ENCRYPTOR

#include <fstream>
#include <array>

#include "AESEncryptor.hpp"
//#include "AESTools.hpp"

class AESCipherEncryptor : public AESEncryptor
{

	public :
	
	// Constructor
	AESCipherEncryptor(unsigned char *t_key, unsigned int t_keySize, std::string t_mode);

	// Destructor
	~AESCipherEncryptor();

	// Methods
	int doCipher(std::ifstream t_inputStream, std::ofstream t_outputStream);
	int doCipherCBC(std::ifstream t_inputStream, std::ofstream t_outputStream);

	int copyByteBuffer(std::array<unsigned char, ARRAY_SIZE> dest, unsigned char *src) {

	private :
	// Attributes
	std::string m_mode;
};

#endif
