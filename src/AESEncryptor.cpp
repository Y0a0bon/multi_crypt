// AESEncryptor.cpp
// See https://kavaliro.com/wp-content/uploads/2014/03/AES.pdf

#include <iostream>
#include <cstring>
#include <cmath>
#include <deque>
#include "AESEncryptor.hpp"
#include "AESTools.hpp"

	// Constructor
	AESEncryptor::AESEncryptor(unsigned char *t_key, unsigned int t_keySize){
		m_key = new unsigned char[t_keySize];
		std::memcpy(m_key, t_key, t_keySize);
		m_keySize = t_keySize;
		m_rounds = 11;
		m_expandedKeyWordSize = 4 * m_rounds;
		m_expandedKey = new unsigned char[4 * m_expandedKeyWordSize];
		std::cout << "Key : " << std::endl;
		printMatrix(m_key, 4, 4);
		keyExpansionComplete();
		std::cout << "Expanded key computing completed :" << std::endl;
		printMatrix(m_expandedKey, m_expandedKeyWordSize, 4);
	}

	// Destructor
	AESEncryptor::~AESEncryptor() {
		delete m_key;
		delete m_expandedKey;
	}

	int AESEncryptor::getExpandedKeySize() {
		return (4*int(m_expandedKeyWordSize));
	}

	void AESEncryptor::getExpandedKey(unsigned char *tmp) {
		for (int i = 0; i < 4*m_expandedKeyWordSize; i++)
			tmp[i] = m_expandedKey[i];
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
		for (i = 0; i < size; i++) {
			tmp[i] = inputVector[(i+1) % size];
		}
		for (i = 0; i < size; i++) {
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

	// FIXME Verify size of both inputs ?
	int AESEncryptor::xorArray(std::array<unsigned char, ARRAY_SIZE> &inputVector, unsigned char *subKey){
		for (int i = 0; i < ARRAY_SIZE; i++) {
			inputVector[i] = inputVector[i] ^ subKey[i];
		}
		return 0;
	}

	// FIXME Verify size of both inputs ?
	int AESEncryptor::xorArray(unsigned char *inputVector, unsigned char *subKey, int size) {
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

	// Dest is a matrix of size <size>*<size>
	int AESEncryptor::copyArrayToColumn(unsigned char *dest, unsigned char *src, int size, int ind) {
		if (size < 1) {
			return 1;
		}
		for (int i = 0; i< size; i++) {
			dest[i*size + ind] = src[i];
		}
		return 0;
	}

	// Src is a matrix of size <size>*<size>
	int AESEncryptor::copyColumnToArray(unsigned char *dest, unsigned char *src, int size, int ind) {
		if (size < 1) {
			return 1;
		}
		for (int i = 0; i< size; i++) {
			dest[i] = src[i*size + ind];
		}
		return 0;
	}

	// Columns is number of columns in the matrix
	// ind is indice of the line to retrieve word from
	int AESEncryptor::getWordFromMatrix(unsigned char *word,unsigned char *matrix, int columns, int ind) {
		for(int i= 0; i < WORD_SIZE; i++) {
			word[i] = matrix[i*columns + ind];
		}
		return 0;
	}

	int AESEncryptor::putWordIntoMatrix(unsigned char *matrix, unsigned char *word, int columns, int ind) {
		for(int i= 0; i < WORD_SIZE; i++) {
			matrix[i*columns + ind] = word[i];
		}
		return 0;
	}

	int AESEncryptor::keyExpansionComplete() {
		int N = m_keySize / 4;
		unsigned char W_i_N[WORD_SIZE], W_i_1[WORD_SIZE];
		unsigned char rc[11] = {0, 1, 2, 4, 8, 16, 32, 64, 128, 27, 54};
		unsigned char rcon[WORD_SIZE] = {0, 0, 0, 0};
		for (int i = 0; i < m_expandedKeyWordSize; i++) {
			// Round 0 is original key
			if (i < N) {
				putWordIntoMatrix(m_expandedKey, m_key, m_expandedKeyWordSize, 0);
			}
			else {
				// Compute W_(i-N) and W_(i-1)
				getWordFromMatrix(W_i_N, m_expandedKey, m_expandedKeyWordSize, i - N);
				getWordFromMatrix(W_i_1, m_expandedKey, m_expandedKeyWordSize, i - 1);
				// Compute rcon_i
				if ((i % N) == 0) {
					subBytes(W_i_1, 4);
					shiftRows(W_i_1, 4);
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
					putWordIntoMatrix(m_expandedKey, W_i_N, m_expandedKeyWordSize, i);
				}
			}
		}
		return 0;
	}

	int AESEncryptor::encryptBlock(std::array<unsigned char, ARRAY_SIZE> &inputVector) {
		if (m_keySize != 16) {
			return 1;
		}
		unsigned char subKey[ARRAY_SIZE];
		std::cout << "Input data :"<< std::endl;
		printVector(inputVector);
		// Initial AddRoundKey
		xorArray(inputVector, m_key);
		std::cout << "After first addRoundKey :"<< std::endl;
		printVector(inputVector);
		// Put m_key into subKey
		copyArray(subKey, m_key, ARRAY_SIZE);
		std::cout << "Key Round 0" << std::endl;
		printVectorLine(subKey, ARRAY_SIZE);
		// Intermediate and final rounds (10 for now, 128-bit key)
		for (int i = 0; i < 10; i++) {
			// FIXME Use m_expandedKey instead of subKey
			std::cout << "Key Round " << i+1 << std::endl;
			printVectorLine(subKey, ARRAY_SIZE);

			subBytes(inputVector);
			shiftRows(inputVector);
			// Intermediate rounds
			if (i <9) {
				mixColumns(inputVector);
			}
			xorArray(inputVector, subKey);
		}
		std::cout << "Ended" << std::endl;
		printVector(inputVector);
		return 0;
	}


