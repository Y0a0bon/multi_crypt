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

	void AESEncryptor::mixColumns(){

	}

	void AESEncryptor::addRoundKey(){

	}

	void AESEncryptor::multiplyArray(std::array<unsigned char, ARRAY_SIZE> &inputVector, std::array<unsigned char, ARRAY_SIZE> &coef){
		int tmp = 0;
		for (int i = 0 ; i < inputVector.size(); i++){
			for (int j = 0 ; j < inputVector.size(); j++){
				for (int k = 0 ; k < inputVector.size(); k++){
					tmp += coef[j*inputVector.size() + k] * inputVector[k*inputVector.size() + j];
				}
			}	
		}
	}

	int AESEncryptor::getThree(){
		return 3;
	}


