// AESDecryptor.cpp

#include <deque>
#include <cstring>
#include "AESDecryptor.hpp"
#include "AESTools.hpp"

	AESDecryptor::AESDecryptor(unsigned char *t_key, unsigned int t_keySize) {
		m_key = new unsigned char[t_keySize];
		memcpy(m_key, t_key, t_keySize);
		m_keySize = t_keySize;
		m_rounds = 11;
		m_expandedKeyWordSize = 4 * m_rounds;
		m_expandedKey = new unsigned char[4 * m_expandedKeyWordSize];
		keyExpansionComplete();
	}

	AESDecryptor::~AESDecryptor() {
		delete m_key;
		delete m_expandedKey;
	}

	int AESDecryptor::getExpandedKeySize() {
		return (4*int(m_expandedKeyWordSize));
	}

	int AESDecryptor::getSubkey(unsigned char *tmp, int ind) {
		if (ind > 11) {
			return INPUT_ERROR;
		}
		getSubMatrix(tmp, m_expandedKey, m_expandedKeyWordSize, ind*4);
		return FUNC_OK;
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
			tmp[i] = inputVector[(i+1) % size];
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
				tmp.push_back(inputVector[i*4 + ((4-i+j)  % 4)]);
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
				tmp[int(i*sqrt(size)) + j] = inputVector[int(i*sqrt(size)) + ((4-i+j) % size)];
			}
		}
		for (i = 0; i < size; i++) {
			inputVector[i] = tmp[i];
		}
		return FUNC_OK;
	}

	
	int AESDecryptor::invMixColumnsWord(unsigned char *multiplicator, unsigned char *word) {
		unsigned char buffer[WORD_SIZE];
		unsigned char buffer_2x[WORD_SIZE];
		unsigned char buffer_4x[WORD_SIZE];
		unsigned char buffer_8x[WORD_SIZE];
		int i, h, h_2, h_4;
		
		memcpy(buffer, word, 4);
		
		for (i=0; i < WORD_SIZE; i++) {
			h = (unsigned char)((signed char)(word[i]) >> 7);
			// Compute {02}x
			buffer_2x[i] = word[i] << 1;
			buffer_2x[i] ^= 0x1B & h;
			// Compute {04}x
			h_2 = (unsigned char)((signed char)(buffer_2x[i]) >> 7);
			buffer_4x[i] = buffer_2x[i] << 1;
			buffer_4x[i] ^= 0x1B & h_2;
			// Compute {08}x
			h_4 = (unsigned char)((signed char)(buffer_4x[i]) >> 7);
			buffer_8x[i] = buffer_4x[i] << 1;
			buffer_8x[i] ^= 0x1B & h_4;
		}

		word[0] = buffer_8x[0] ^ buffer_4x[0] ^ buffer_2x[0] ^ buffer_8x[1] ^ buffer_2x[1] ^ buffer[1] ^ buffer_8x[2] ^ buffer_4x[2] ^ buffer[2] ^ buffer_8x[3] ^ buffer[3];
		word[1] = buffer_8x[0] ^ buffer[0] ^ buffer_8x[1] ^ buffer_4x[1] ^ buffer_2x[1] ^ buffer_8x[2] ^ buffer_2x[2] ^ buffer[2] ^ buffer_8x[3] ^ buffer_4x[3] ^ buffer[3];
		word[2] = buffer_8x[0] ^ buffer_4x[0] ^ buffer[0] ^ buffer_8x[1] ^ buffer[1] ^ buffer_8x[2] ^ buffer_4x[2] ^ buffer_2x[2] ^ buffer_8x[3] ^ buffer_2x[3] ^ buffer[3];
		word[3] = buffer_8x[0] ^ buffer_2x[0] ^ buffer[0] ^ buffer_8x[1] ^ buffer_4x[1] ^ buffer[1] ^ buffer_8x[2] ^ buffer[2] ^ buffer_8x[3] ^ buffer_4x[3] ^ buffer_2x[3];
		
		return FUNC_OK;
	}

	int AESDecryptor::invMixColumns(std::array<unsigned char, ARRAY_SIZE> &inputVector) {
		unsigned char word[4];
		unsigned char multiplicator[16];

		memcpy(multiplicator, coef, 16);
		
		for (int i = 0; i < 4; i++) {
			getWordFromMatrix(word, inputVector, i);
			invMixColumnsWord(multiplicator, word);
			putWordIntoMatrix(inputVector, word, i);
		}
		return FUNC_OK;
	}
	
	int AESDecryptor::subBytes(unsigned char *inputVector, int size) {
		if (inputVector == nullptr)
			return INPUT_ERROR;
		for (int i = 0 ; i < size; i++){
			inputVector[i] = sbox[inputVector[i]];
		}
		return FUNC_OK;
	}

	int AESDecryptor::shiftRow(unsigned char *inputVector, int size) {
		unsigned char tmp[size];
		int i;
		for (i = 0; i < size; i++) {
			tmp[i] = inputVector[(i+1) % size];
		}
		for (i = 0; i < size; i++) {
			inputVector[i] = tmp[i];
		}
	}

	// FIXME
	int AESDecryptor::keyExpansionComplete() {
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

	// FIXME
	int AESDecryptor::equivalentCipherExpansion() {
		for(int i = 0; i < m_expandedKeyWordSize; i++) {
			//invMixColumns();
		}
		return NOT_IMPLEMENTED;	
	}

	int AESDecryptor::decryptBlock(std::array<unsigned char, ARRAY_SIZE> &inputVector) {
		if (m_keySize != 16) {
			return INPUT_ERROR;
		}
		
		unsigned char subKey[ARRAY_SIZE];
		
		//std::cout << "***** Round 0 *****"<< std::endl;
		//std::cout << "Input data :"<< std::endl;
		//printVector(inputVector);
		
		getSubMatrix(subKey, m_expandedKey, m_expandedKeyWordSize, 40);
		//std::cout << "First subkey :" << std::endl;
		//printVector(subKey, ARRAY_SIZE);

		// Initial AddRoundKey
		xorArray(inputVector, subKey);
		//printVector(inputVector);

		// Intermediate and final rounds (10 for now, 128-bit key)
		for (int i = 9; i >= 0; i--) {
			//std::cout << "***** Round " << int(i) << " *****" << std::endl;
			invShiftRows(inputVector);
			invSubBytes(inputVector);

			//std::cout << "State Matrix" << std::endl;
			//printVector(inputVector);
			
			getSubMatrix(subKey, m_expandedKey, m_expandedKeyWordSize, i*4);

			//std::cout <<  "Subkey Round " << int(i) << std::endl;
			//printSubkey(m_expandedKey, m_expandedKeyWordSize, i*4);

			xorArray(inputVector, subKey);

			if (i > 0) {
				invMixColumns(inputVector);
			}

			//std::cout << "Final State Matrix Round " << int(i) << std::endl;
			//printVector(inputVector);
		}

		return FUNC_OK;
	}

	// FIXME Verify size of both inputs ?
	int AESDecryptor::xorArray(std::array<unsigned char, ARRAY_SIZE> &inputVector, unsigned char *subKey){
		for (int i = 0; i < ARRAY_SIZE; i++) {
			inputVector[i] = inputVector[i] ^ subKey[i];
		}
		return FUNC_OK;
	}

	// FIXME Verify size of both inputs ?
	int AESDecryptor::xorArray(unsigned char *inputVector, unsigned char *subKey, int size) {
		if (size < 1) {
			return INPUT_ERROR;
		}
		for (int i = 0; i < size; i++) {
			inputVector[i] = inputVector[i] ^ subKey[i];
		}
		return FUNC_OK;
	}

	// FIXME Use memcpy ?!
	int AESDecryptor::copyArray(unsigned char *dest, unsigned char *src, int size) {
		if (size < 1) {
			return INPUT_ERROR;
		}
		for (int i = 0; i< size; i++) {
			dest[i] = src[i];
		}
		return FUNC_OK;
	}

	// Dest is a matrix of size <size>*<size>
	int AESDecryptor::copyArrayToColumn(unsigned char *dest, unsigned char *src, int size, int ind) {
		if (size < 1) {
			return INPUT_ERROR;
		}
		for (int i = 0; i< size; i++) {
			dest[i*size + ind] = src[i];
		}
		return FUNC_OK;
	}

	// Src is a matrix of size <size>*<size>
	int AESDecryptor::copyColumnToArray(unsigned char *dest, unsigned char *src, int size, int ind) {
		if (size < 1) {
			return INPUT_ERROR;
		}
		for (int i = 0; i< size; i++) {
			dest[i] = src[i*size + ind];
		}
		return FUNC_OK;
	}

	// Columns is number of columns in the matrix
	// ind is indice of the line to retrieve word from
	int AESDecryptor::getWordFromMatrix(unsigned char *word, unsigned char *matrix, int columns, int ind) {
		for(int i= 0; i < WORD_SIZE; i++) {
			word[i] = matrix[i*columns + ind];
		}
		return FUNC_OK;
	}

	int AESDecryptor::getWordFromMatrix(unsigned char *word, std::array<unsigned char, ARRAY_SIZE> &matrix, int ind) {
		for(int i= 0; i < WORD_SIZE; i++) {
			word[i] = matrix[i*WORD_SIZE + ind];
		}
		return FUNC_OK;
	}

	int AESDecryptor::putWordIntoMatrix(unsigned char *matrix, unsigned char *word, int columns, int ind) {
		for(int i= 0; i < WORD_SIZE; i++) {
			matrix[i*columns + ind] = word[i];
		}
		return FUNC_OK;
	}

	int AESDecryptor::putWordIntoMatrix(std::array<unsigned char, ARRAY_SIZE> &matrix, unsigned char *word, int ind) {
		for(int i= 0; i < WORD_SIZE; i++) {
			matrix[i*WORD_SIZE + ind] = word[i];
		}
		return FUNC_OK;
	}

	int AESDecryptor::getSubMatrix(unsigned char *dest, unsigned char *src, int columns, int ind) {
		for (int i = 0; i < WORD_SIZE; i++) {
			for( int j = 0; j < WORD_SIZE; j++) {
				dest[i*WORD_SIZE + j] = src[i*columns + ind + j];
			}
		}
		return FUNC_OK;
	}



