// AESEncruptor.cpp

#include <cstring>
#include "AESEncryptor.hpp"


	// Constructor
	AESEncryptor::AESEncryptor(unsigned char *t_key, unsigned int t_keySize){
		m_key = new unsigned char[t_keySize];
		std::memcpy(m_key, t_key, t_keySize);
		m_keySize = t_keySize;
	}

	void AESEncryptor::subBytes(){
		

	}

	void AESEncryptor::shiftRows(){

	}

	void AESEncryptor::mixColumns(){

	}

	void AESEncryptor::addRoundKey(){

	}

	int AESEncryptor::getThree(){
		return 3;
	}


