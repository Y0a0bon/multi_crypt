// AESEncryptor.cpp

#include <deque>
#include <cstring>
#include "AESDecryptor.hpp"
#include "AESTools.hpp"

	AESDecryptor::AESDecryptor(unsigned char *t_key, unsigned int t_keySize) {
		m_key = new unsigned char[t_keySize];
		std::memcpy(m_key, t_key, t_keySize);
		m_keySize = t_keySize;
		m_rounds = 11;
		m_expandedKeyWordSize = 4 * m_rounds;
		m_expandedKey = new unsigned char[4 * m_expandedKeyWordSize];
		//keyExpansionComplete();
	}

	AESDecryptor::~AESDecryptor() {
		delete m_key;
		delete m_expandedKey;
	}


	int AESDecryptor::invSubBytes(std::array<unsigned char, ARRAY_SIZE> &inputVector) {
		if (inputVector.empty())
			return INPUT_ERROR;
		for (int i = 0 ; i < inputVector.size(); i++){
			inputVector[i] = rsbox[inputVector[i]];
		}
		return FUNC_OK;
	}

	int AESDecryptor::invSubBytes(unsigned char *inputVector, int size) {
		if (inputVector == nullptr)
			return INPUT_ERROR;
		for (int i = 0 ; i < size; i++){
			inputVector[i] = rsbox[inputVector[i]];
		}
		return FUNC_OK;
	}


	int AESDecryptor::invShiftRow(unsigned char *inputVector, int size) {
		unsigned char tmp[size];
		int i;
		for (i = 0; i < size; i++) {
			tmp[i] = inputVector[(i+3) % size];
		}
		for (i = 0; i < size; i++) {
			inputVector[i] = tmp[i];
		}
		return FUNC_OK;
	}

	int AESDecryptor::invShiftRows(std::array<unsigned char, ARRAY_SIZE> &inputVector) {
		std::deque<unsigned char> tmp;
		int ind = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				tmp.push_back(inputVector[i*4 + ((i+j+2)  % 4)]);
			}
			for (int e : tmp) {
				inputVector[i*4 + ind] = e;
				ind++;
			}
			ind = 0;
			tmp.clear();
		}
		return FUNC_OK;
	}

	int AESDecryptor::invShiftRows(unsigned char *inputVector, int size) {
		unsigned char tmp[size];
		int i, j;
		for (i = 0; i < sqrt(size); i++) {
			for(j = 0; j < sqrt(size); j++) {
				tmp[int(i*sqrt(size)) + j] = inputVector[int(i*sqrt(size)) + ((i+j+2) % size)];
			}
		}
		for (i = 0; i < size; i++) {
			inputVector[i] = tmp[i];
		}
		return FUNC_OK;
	}

	
	int AESDecryptor::invMixColumnsWord(unsigned char *multiplicator, unsigned char *word) {
		return NOT_IMPLEMENTED;
	}

	int AESDecryptor::invMixColumns(std::array<unsigned char, ARRAY_SIZE> &inputVector) {
		return NOT_IMPLEMENTED;
	}
	


