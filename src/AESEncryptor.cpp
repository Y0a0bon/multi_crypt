// AESEncruptor.cpp

#include <cstring>
#include <deque>
#include "AESEncryptor.hpp"
#include "AESTools.hpp"


	// Constructor
	AESEncryptor::AESEncryptor(unsigned char *t_key, unsigned int t_keySize){
		m_key = new unsigned char[t_keySize];
		std::memcpy(m_key, t_key, t_keySize);
		m_keySize = t_keySize;
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

	void AESEncryptor::mixColumns(std::array<unsigned char, ARRAY_SIZE> &inputVector){
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
	}

	void AESEncryptor::addRoundKey(){

	}


