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
		doCipher(t_inputStream, t_outputStream, null);
	}
	
	int AESCipherEncryptor::doCipher(std::ifstream t_inputStream, std::ofstream t_outputStream, unsigned char *aad) {
		if (t_inputStream) {
			// Get length of file
			t_inputStream.seekg(0, t_inputStream.end);
			int length = t_inputStream.tellg();
			t_inputStream.seekg(0, t_inputStream.beg);

			// Init var
			bool readable = true;
			unsigned char buffer[ARRAY_SIZE];
			std::array<unsigned char, ARRAY_SIZE> buffer_array;
			
			// Init inputs
			unsigned char iv[12];
			getRand(iv, 12);

			// Init outputs
			unsigned char output_buffer[ARRAY_SIZE];
			unsigned char auth_tag[ARRAY_SIZE];

			do {
				// read block
				t_inputStream.read(buffer, ARRAY_SIZE);
				if(!t_inputStream) {
					readable = false;
				}
				
			} while (readable);

			if (!t_inputStream)
				return FUNC_ERROR;
			else
				return FUNC_OK;
		}
		else
			return INPUT_ERROR;
	}

	int AESCipherEncryptor::doCipherGCM(std::ifstream t_inputStream, std::ofstream t_outputStream) {

		// H = CIPH_key(0^128)
		//
		// J_0 = IV || 0^31 || 1
		//
		// C = GCTR_key (inc_32(J_0), plaintext)
		//
		// u = 128 . ceil(len(C)	/128) - 128 and v = 128 . ceil(len(A)/128) - 128
		//
		// s = GHASH_H(A || 0^v || C || 0^u || [len(A)]_64 || [len(C)]_64)
		//
		// T = MSB_t(GCTR_K(J_0,S))

		return NOT_IMPLEMENTED;
	}

	int AESCipherEncryptor::copyByteBuffer(std::array<unsigned char, ARRAY_SIZE> dest, unsigned char *src) {
		for (int i = 0; i < ARRAY_SIZE) {
			dest[i] = src[i];
		}
		return FUNC_OK;
	}

	//int AESEncryptor::encryptBlock(std::array<unsigned char, ARRAY_SIZE> &inputVector);
	//
	//
	//
