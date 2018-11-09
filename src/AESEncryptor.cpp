// AESEncryptor.cpp

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
		m_rounds = 10;
		printVectorLine(m_key, m_keySize);
	}

	// Destructor
	AESEncryptor::~AESEncryptor() {
		delete m_key;
	}

	int AESEncryptor::printVector(std::array<unsigned char, 16> vector){
		for(int i = 0; i < sqrt(vector.size()); i++){
			for(int j = 0; j < sqrt(vector.size()); j++){
				std::cout << std::hex << int(vector[i*int(sqrt(vector.size())) + j]) << "  ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		return 0;
	}

	int AESEncryptor::printVector(unsigned char *vector, int size){
		for(int i = 0; i < sqrt(size); i++){
			for(int j = 0; j < sqrt(size); j++){
				std::cout << std::hex << int(vector[i*int(sqrt(size)) + j]) << "  ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		return 0;
	}

	int AESEncryptor::printVectorLine(unsigned char *vector, int size){
		for(int i = 0; i < sqrt(size); i++){
			for(int j = 0; j < sqrt(size); j++){
				std::cout << std::hex << int(vector[i*int(sqrt(size)) + j]) << "  ";
			}
		}
		std::cout << std::endl;
		return 0;
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

	void AESEncryptor::printHex(unsigned char *vector, int size) {
		for (int i = 0; i < 4; i++) {
			std::cout << std::hex << int(vector[i]) << "  ";
		}
		std::cout << std::endl;
	}

	int AESEncryptor::keyExpansion(unsigned char *subKey) {
		// g_w_3 is g(w[3]), w[3] 4th word of the key
		unsigned char g_w_3[4];
		int i;
		// Put last word of key into g_w_3
		for (i = 0; i < 4; i++) {
			g_w_3[i] = subKey[12 + i];
		}
		
		// Compute w[4] ( = g(w[3]))
		shiftRows(g_w_3, 4);
		subBytes(g_w_3, 4);
		g_w_3[0] = int(g_w_3[0]) - 1;
		addRoundKey(g_w_3, subKey, 4);

		copyArray(subKey, g_w_3, 4);
		// Compute next subkey words
		for (i = 1; i < 4; i++){
			addRoundKey(&subKey[i*4], &subKey[(i-1)*4], 4);
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
		addRoundKey(inputVector, m_key);
		std::cout << "After first addRoundKey :"<< std::endl;
		printVector(inputVector);
		// Put m_key into subKey
		copyArray(subKey, m_key, ARRAY_SIZE);
		std::cout << "Key Round 0" << std::endl;
		printVectorLine(subKey, ARRAY_SIZE);
		// Intermediate and final rounds (10 for now, 128-bit key)
		for (int i = 0; i < 10; i++) {
			subBytes(inputVector);
			shiftRows(inputVector);
			// Intermediate rounds
			if (i <9) {
				mixColumns(inputVector);
			}
			keyExpansion(subKey);
			addRoundKey(inputVector, subKey);
			std::cout << "Key Round " << i+1 << std::endl;
			printVectorLine(subKey, ARRAY_SIZE);
		}
		std::cout << "Ended" << std::endl;
		printVector(inputVector);
		return 0;
	}


