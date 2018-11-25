// AESEncryptor.cpp

#include <iostream>
#include <cstring>
#include <cmath>
#include <deque>
#include "AESEncryptor.hpp"
#include "AESTools.hpp"

	// Constructor
	AESEncryptor::AESEncryptor(unsigned char *t_key, unsigned int t_keySize) : AESManipulator(t_key, t_keySize) {
		keyExpansionComplete();
	}

	// Destructor
	AESEncryptor::~AESEncryptor() {
	}

	int AESEncryptor::getExpandedKeySize() {
		return (4*int(m_expandedKeyWordSize));
	}

	int AESEncryptor::getSubkey(unsigned char *tmp, int ind) {
		if (ind > 11) {
			return INPUT_ERROR;
		}
		getSubMatrix(tmp, m_expandedKey, m_expandedKeyWordSize, ind*4);
		return FUNC_OK;
	}

	// SubBytes
	// Y_i = Sbox(X_i)
	int AESEncryptor::subBytes(std::array<unsigned char, ARRAY_SIZE> &inputVector){
		if (inputVector.empty())
			return INPUT_ERROR;
		for (int i = 0 ; i < inputVector.size(); i++){
			inputVector[i] = sbox[inputVector[i]];
		}
		return FUNC_OK;
	}

	int AESEncryptor::subBytes(unsigned char *inputVector, int size) {
		if (inputVector == nullptr)
			return INPUT_ERROR;
		for (int i = 0 ; i < size; i++){
			inputVector[i] = sbox[inputVector[i]];
		}
		return FUNC_OK;
	}

	int AESEncryptor::shiftRow(unsigned char *inputVector, int size) {
		unsigned char tmp[size];
		int i;
		for (i = 0; i < size; i++) {
			tmp[i] = inputVector[(i+1) % size];
		}
		for (i = 0; i < size; i++) {
			inputVector[i] = tmp[i];
		}
	}

	// Show off use od deque and std::array
	// But is it really necesary ?
	int AESEncryptor::shiftRows(std::array<unsigned char, ARRAY_SIZE> &inputVector){
		std::deque<unsigned char> tmp;
		int ind = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				tmp.push_back(inputVector[i*4 + ((i+j)  % 4)]);
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

	int AESEncryptor::shiftRows(unsigned char *inputVector, int size) {
		unsigned char tmp[size];
		int i, j;
		for (i = 0; i < sqrt(size); i++) {
			for(j = 0; j < sqrt(size); j++) {
				tmp[int(i*sqrt(size)) + j] = inputVector[int(i*sqrt(size)) + ((i+j) % size)];
			}
		}
		for (i = 0; i < size; i++) {
			inputVector[i] = tmp[i];
		}
		return FUNC_OK;
	}

	int AESEncryptor::mixColumnsWord(unsigned char *multiplicator, unsigned char *word) {
		unsigned char buffer1[WORD_SIZE];
		unsigned char buffer2[WORD_SIZE];
		int i, h;
		
		memcpy(buffer1, word, 4);
		
		for (i=0; i < WORD_SIZE; i++) {
			h = (unsigned char)((signed char)(word[i]) >> 7);
			buffer2[i] = word[i] << 1;
			buffer2[i] ^= 0x1B & h;
		}
		
		word[0] = buffer2[0] ^ buffer1[3] ^ buffer1[2] ^ buffer2[1] ^ buffer1[1];
		word[1] = buffer2[1] ^ buffer1[0] ^ buffer1[3] ^ buffer2[2] ^ buffer1[2];
		word[2] = buffer2[2] ^ buffer1[1] ^ buffer1[0] ^ buffer2[3] ^ buffer1[3];
		word[3] = buffer2[3] ^ buffer1[2] ^ buffer1[1] ^ buffer2[0] ^ buffer1[0];
		
		return FUNC_OK;
	}
	
	int AESEncryptor::mixColumns(std::array<unsigned char, ARRAY_SIZE> &inputVector){
		unsigned char word[4];
		unsigned char multiplicator[16];

		memcpy(multiplicator, coef, 16);
		
		for (int i = 0; i < 4; i++) {
			getWordFromMatrix(word, inputVector, i);
			mixColumnsWord(multiplicator, word);
			putWordIntoMatrix(inputVector, word, i);
		}
		return FUNC_OK;
	}

	int AESEncryptor::keyExpansionComplete() {
		int N = m_keySize / 4;
		unsigned char W_i_N[WORD_SIZE], W_i_1[WORD_SIZE], wordBuffer[WORD_SIZE];

		unsigned char rc[11] = {0, 1, 2, 4, 8, 16, 32, 64, 128, 27, 54};
		unsigned char rcon[WORD_SIZE] = {0, 0, 0, 0};
		
		for (int i = 0; i < m_expandedKeyWordSize; i++) {
			// Round 0 is original key
			if (i < N) {
				getWordFromMatrix(wordBuffer, m_key, WORD_SIZE, i);
				putWordIntoMatrix(m_expandedKey, wordBuffer, m_expandedKeyWordSize, i);
			}
			else {
				// Compute W_(i-N) and W_(i-1)
				getWordFromMatrix(W_i_N, m_expandedKey, m_expandedKeyWordSize, i - N);
				getWordFromMatrix(W_i_1, m_expandedKey, m_expandedKeyWordSize, i - 1);
				// Compute rcon_i
				if ((i % N) == 0) {
					subBytes(W_i_1, 4);
					shiftRow(W_i_1, 4);
					xorArray(W_i_N, W_i_1, 4);
					rcon[0] = rc[i/N];
					xorArray(W_i_N, rcon, 4);
				}
				// Only in AES-256 mode
				else if (N > 6 && (i % N) == 4) {
					// TO DO
				}
				else {
					xorArray(W_i_N, W_i_1, 4);
				}
				putWordIntoMatrix(m_expandedKey, W_i_N, m_expandedKeyWordSize, i);
			}
		}
		return FUNC_OK;
	}

	int AESEncryptor::encryptBlock(std::array<unsigned char, ARRAY_SIZE> &inputVector) {
		if (m_keySize != 16) {
			return INPUT_ERROR;
		}
		
		unsigned char subKey[ARRAY_SIZE];
		
		//std::cout << "***** Round 0 *****"<< std::endl;
		//std::cout << "Input data :"<< std::endl;
		//printVector(inputVector);
		
		getSubMatrix(subKey, m_expandedKey, m_expandedKeyWordSize, 0);
		//std::cout << "First subkey :" << std::endl;
		//printVector(subKey, ARRAY_SIZE);

		// Initial AddRoundKey
		xorArray(inputVector, subKey);
		//printVector(inputVector);

		// Intermediate and final rounds (10 for now, 128-bit key)
		for (int i = 1; i <= 10; i++) {
			//std::cout << "***** Round " << int(i) << " *****" << std::endl;
			subBytes(inputVector);
			shiftRows(inputVector);
			if (i < 10) {
				mixColumns(inputVector);
			}

			//std::cout << "State Matrix" << std::endl;
			//printVector(inputVector);
			
			getSubMatrix(subKey, m_expandedKey, m_expandedKeyWordSize, i*4);

			//std::cout <<  "Subkey Round " << int(i) << std::endl;
			//printSubkey(m_expandedKey, m_expandedKeyWordSize, i*4);

			xorArray(inputVector, subKey);

			//std::cout << "Final State Matrix Round " << int(i) << std::endl;
			//printVector(inputVector);
		}

		return FUNC_OK;
	}

