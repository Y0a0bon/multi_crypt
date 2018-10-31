// AESEncryptor.cpp

#include <cstring>
#include <deque>
#include "AESEncryptor.hpp"
#include "AESTools.hpp"


	// Constructor
	AESEncryptor::AESEncryptor(unsigned char *t_key, unsigned int t_keySize){
		m_key = new unsigned char[t_keySize];
		std::memcpy(m_key, t_key, t_keySize);
		m_keySize = t_keySize;
		m_rounds = 10;
	}

	// SubBytes
	// Y_i = Sbox(X_i)
	int AESEncryptor::subBytes(std::array<unsigned char, ARRAY_SIZE> &inputVector){
		if (inputVector.empty())
			return 1;
		for (int i = 0 ; i < inputVector.size(); i++){
			inputVector[i] = sbox[inputVector[i]];
		}
		return 0;
	}

	int AESEncryptor::subBytes(unsigned char *inputVector, int size) {
		if (inputVector == nullptr)
			return 1;
		for (int i = 0 ; i < size; i++){
			inputVector[i] = sbox[inputVector[i]];
		}
		return 0;
	}

	// Matrix
	int AESEncryptor::shiftRows(std::array<unsigned char, ARRAY_SIZE> &inputVector){
		std::deque<unsigned char> tmp;
		int ind = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				tmp.push_back(inputVector[i*4 + ((4-i+j) % 4)]);
			}
			for (int e : tmp) {
				inputVector[i*4 + ind] = e;
				ind++;
			}
			ind = 0;
			tmp.clear();
		}
		return 0;
	}

	// Vector
	int AESEncryptor::shiftRows(unsigned char *inputVector, int size){
		unsigned char tmp[size];
		int i;
		for (i = 0; i < 4; i++) {
			tmp[i] = inputVector[(i+3) % 4];
		}
		for (i = 0; i < 4; i++) {
			inputVector[i] = tmp[i];
		}
		return 0;
	}

	int AESEncryptor::mixColumns(std::array<unsigned char, ARRAY_SIZE> &inputVector){
		std::array<unsigned char, 4> tmpArray;
		int tmp = 0, i = 0, j = 0, k = 0;

		for (i = 0 ; i < 4; i++){
			// Compute vertical array
			for (j = 0 ; j < 4; j++){
				// Compute each element of the array
				for (k = 0 ; k < 4; k++){
					tmp += coef[j*4 + k] * int(inputVector[i + k*4]);
				}
				tmpArray[j] = tmp;
				tmp = 0;
			}
			// Store it into original array
			for (k = 0; k < 4; k++) {
				inputVector[i + k*4] = tmpArray[k];
			}
			tmpArray.empty();
		}
		return 0;
	}

	int AESEncryptor::addRoundKey(std::array<unsigned char, ARRAY_SIZE> &inputVector, unsigned char *subKey){
		for (int i = 0; i < ARRAY_SIZE; i++) {
			inputVector[i] = inputVector[i] ^ subKey[i];
		}
		return 0;
	}

	int AESEncryptor::addRoundKey(unsigned char *inputVector, unsigned char *subKey, int size) {
		if (size < 1) {
			return 1;
		}
		for (int i = 0; i < size; i++) {
			inputVector[i] = inputVector[i] ^ subKey[i];
		}
		return 0;
	}

	// FIXME Use memcpy ?!
	int AESEncryptor::copyArray(unsigned char *dest, unsigned char *src, int size) {
		if (size < 1) {
			return 1;
		}
		for (int i = 0; i< size; i++) {
			dest[i] = src[i];
		}
		return 0;
	}

	int AESEncryptor::keyExpansion(unsigned char *subKey) {
		unsigned char g_w_3[4];
		int i;
		// Put last word of key into g_w_3
		for (i = 0; i < 4; i++) {
			g_w_3[i] = subKey[12 + i];
		}
		// Compute w[4] ( = g(w[3]))
		shiftRows(g_w_3, 4);
		subBytes(g_w_3, 4);
		g_w_3[15] = int(g_w_3[15]) + 1;
		addRoundKey(subKey, g_w_3, 4);
		// Compute next subkey words
		for (i = 1; i < 4; i++){
			addRoundKey(&subKey[i*4], &subKey[(i-1)*4], 4);
		}
	}

	int AESEncryptor::encrypt(std::array<unsigned char, ARRAY_SIZE> &inputVector) {
		if (m_keySize != 128) {
			return 1;
		}
		unsigned char subKey[ARRAY_SIZE];
		int i;
		// Initial AddRoundKey
		addRoundKey(inputVector, m_key);
		// Intermediate and final rounds (10 for now, 128-bit key)
		for (i = 0; i < 10; i++) {
			subBytes(inputVector);
			shiftRows(inputVector);
			// Intermediate rounds
			if (i <9) {
				mixColumns(inputVector);
			}
			keyExpansion(subKey);
			addRoundKey(inputVector, subKey);
		}

		return 0;
	}
