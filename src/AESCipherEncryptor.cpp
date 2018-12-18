// AESCipherEncryptor.cpp

#include <iostream>
#include <cstring>
#include <cmath>
#include "AESCipherEncryptor.hpp"

	// Constructor
	AESCipherEncryptor::AESCipherEncryptor(unsigned char *t_key, unsigned int t_keySize, std::string t_mode) : AESEncryptor(t_key, t_keySize) {
		m_mode = t_mode;	
	}

	// Destructor
	AESCipherEncryptor::~AESCipherEncryptor() {
	}

	// MEthods
	int AESCipherEncryptor::doCipher(std::ifstream t_inputStream, std::ofstream t_outputStream) {

		return NOT_IMPLEMENTED;
	}

	int doCipherCBC(std::ifstream t_inputStream, std::ofstream t_outputStream) {

		return NOT_IMPLEMENTED;
	}

	//int AESEncryptor::encryptBlock(std::array<unsigned char, ARRAY_SIZE> &inputVector);
