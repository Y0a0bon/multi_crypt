// AESManipulator.cpp

#include "AESManipulator.hpp"
#include "AESTools.hpp"


	// Constructor
	AESManipulator::AESManipulator(unsigned char *t_key, unsigned int t_keySize) {
		m_key = new unsigned char[t_keySize];
		memcpy(m_key, t_key, t_keySize);
		m_keySize = t_keySize;
		m_rounds = 11;
		m_expandedKeyWordSize = 4 * m_rounds;
		m_expandedKey = new unsigned char[4 * m_expandedKeyWordSize];
	}

	// Destructor
	AESManipulator::~AESManipulator() {
		delete m_key;
		delete m_expandedKey;
	}

	// Methods

	// FIXME Verify size of both inputs ?
	int AESManipulator::xorArray(std::array<unsigned char, ARRAY_SIZE> &inputVector, unsigned char *subKey) {
		for (int i = 0; i < ARRAY_SIZE; i++) {
			inputVector[i] = inputVector[i] ^ subKey[i];
		}
		return FUNC_OK;
	}

	// FIXME Verify size of both inputs ?
	int AESManipulator::xorArray(unsigned char *inputVector, unsigned char *subKey, int size) {
		if (size < 1) {
			return INPUT_ERROR;
		}
		for (int i = 0; i < size; i++) {
			inputVector[i] = inputVector[i] ^ subKey[i];
		}
		return FUNC_OK;
	}

	// FIXME Use memcpy ?!
	int AESManipulator::copyArray(unsigned char *dest, unsigned char *src, int size) {
		if (size < 1) {
			return INPUT_ERROR;
		}
		for (int i = 0; i< size; i++) {
			dest[i] = src[i];
		}
		return FUNC_OK;
	}

	// Dest is a matrix of size <size>*<size>
	int AESManipulator::copyArrayToColumn(unsigned char *dest, unsigned char *src, int size, int ind) {
		if (size < 1) {
			return INPUT_ERROR;
		}
		for (int i = 0; i< size; i++) {
			dest[i*size + ind] = src[i];
		}
		return FUNC_OK;
	}

	// Src is a matrix of size <size>*<size>
	int AESManipulator::copyColumnToArray(unsigned char *dest, unsigned char *src, int size, int ind) {
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
	int AESManipulator::getWordFromMatrix(unsigned char *word, unsigned char *matrix, int columns, int ind) {
		for(int i= 0; i < WORD_SIZE; i++) {
			word[i] = matrix[i*columns + ind];
		}
		return FUNC_OK;
	}

	int AESManipulator::getWordFromMatrix(unsigned char *word, std::array<unsigned char, ARRAY_SIZE> &matrix, int ind) {
		for(int i= 0; i < WORD_SIZE; i++) {
			word[i] = matrix[i*WORD_SIZE + ind];
		}
		return FUNC_OK;
	}

	int AESManipulator::putWordIntoMatrix(unsigned char *matrix, unsigned char *word, int columns, int ind) {
		for(int i= 0; i < WORD_SIZE; i++) {
			matrix[i*columns + ind] = word[i];
		}
		return FUNC_OK;
	}

	int AESManipulator::putWordIntoMatrix(std::array<unsigned char, ARRAY_SIZE> &matrix, unsigned char *word, int ind) {
		for(int i= 0; i < WORD_SIZE; i++) {
			matrix[i*WORD_SIZE + ind] = word[i];
		}
		return FUNC_OK;
	}

	int AESManipulator::getSubMatrix(unsigned char *dest, unsigned char *src, int columns, int ind) {
		for (int i = 0; i < WORD_SIZE; i++) {
			for( int j = 0; j < WORD_SIZE; j++) {
				dest[i*WORD_SIZE + j] = src[i*columns + ind + j];
			}
		}
		return FUNC_OK;
	}


