#include <iostream>
#include <string>
#include <cmath>

#include "RSA_algorithm.hpp"
#include "RSA_key.hpp"
#include "AESEncryptor.hpp"
#include "AESTools.hpp"

int test_AES();
int test_AES_shiftRows(AESEncryptor *aes_enc);
int test_AES_mixColumns(AESEncryptor *aes_enc);
int test_AES_getWordFromMatrix(AESEncryptor *aes_enc);
int test_AES_putWordIntoMatrix(AESEncryptor *aes_enc);
int test_AES_keyExpansion(AESEncryptor *aes_enc);
int test_AES_encryptBlock(AESEncryptor *aes_enc);
int test_RSA();

int main()
{
	
	test_AES();
	return 0;
}

int test_AES()
{
	unsigned char key[16] = {84, 115, 32, 103, 104, 32, 75, 32, 97, 109, 117, 70, 116, 121, 110, 117};
	AESEncryptor *aes_enc = new AESEncryptor(key, 16);
	test_AES_shiftRows(aes_enc);
	test_AES_mixColumns(aes_enc);
	test_AES_getWordFromMatrix(aes_enc);
	test_AES_putWordIntoMatrix(aes_enc);
	//test_AES_keyExpansion(aes_enc);
	//test_AES_encryptBlock(aes_enc);
	return 0;
}

int test_AES_subBytes(AESEncryptor *aes_enc)
{
	// TODO
}

int test_AES_shiftRows(AESEncryptor *aes_enc)
{
	std::array<unsigned char, 16> input = {0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3};
	std::array<unsigned char, 16> output = {0,1,2,3,3,0,1,2,2,3,0,1,1,2,3,0};
	aes_enc->shiftRows(input);
	if (input == output) {
		std::cout << "Test passed : shiftRows" << std::endl;
		return 0;
	}
	else {
		std::cout << "Test failed : shiftRows" << std::endl;
		return 1;
	}
}

int test_AES_mixColumns(AESEncryptor *aes_enc) {
	std::array<unsigned char, 16> input = {5,4,1,2,5,3,6,1,4,5,1,2,2,0,3,1};
	std::array<unsigned char, 16> output = {31,22,24,10,29,25,19,11,24,17,18,10,28,20,16,11};
	aes_enc->mixColumns(input);
	if (input == output) {
		std::cout << "Test passed : mixColumns" << std::endl;
		return 0;
	}
	else {
		std::cout << "Test failed : mixColumns" << std::endl;
		return 1;
	}
	return 0;
}

bool compareArray(unsigned char *input, unsigned char *output, int size) {
	bool same = true;
	int i = 0;
	do {
		if (input[i] != output[i]) {
			same = false;
		}
		i++;
	} while(same && i < size);
	return same;
}

int test_AES_getWordFromMatrix(AESEncryptor *aes_enc) {
	unsigned char input[WORD_SIZE];
	unsigned char key[16] = {84, 115, 32, 103, 104, 32, 75, 32, 97, 109, 117, 70, 116, 121, 110, 117};
	unsigned char output[WORD_SIZE] = {84, 104, 97, 116};

	aes_enc->getWordFromMatrix(output, key, WORD_SIZE, 0);
	
	if(compareArray(input, output, 4)) {
		std::cout << "Test passed : getWordFromMatrix" << std::endl;
		return 0;
	}
	else {
		std::cout << "Test failed : getWordFromMatrix" << std::endl;
		return 1;
	}
	return 0;
}

int test_AES_putWordIntoMatrix(AESEncryptor *aes_enc) {
	unsigned char input[WORD_SIZE] = {0, 0, 0, 0};
	unsigned char key[16] = {84, 115, 32, 103, 104, 32, 75, 32, 97, 109, 117, 70, 116, 121, 110, 117};
	unsigned char output[16] = {84, 115, 32, 0, 104, 32, 75, 0, 97, 109, 117, 0, 116, 121, 110, 0};

	aes_enc->putWordIntoMatrix(key, input, WORD_SIZE, 3);
	
	if(compareArray(key, output, 16)) {
		std::cout << "Test passed : putWordIntoMatrix" << std::endl;
		return 0;
	}
	else {
		std::cout << "Test failed : putWordIntoMatrix" << std::endl;
		return 1;
	}
	return 0;
}

int test_AES_keyExpansion(AESEncryptor *aes_enc) {
	//unsigned char expandedKey[aes_enc->getExpandedKeySize];
	unsigned char expandedKey[44];
	unsigned char output[16] = {226, 145, 177, 214, 50, 18, 89, 121, 252, 145, 228, 162, 241, 136, 230, 147};
	if(compareArray(expandedKey, output, 16)) {
		std::cout << "Test passed : keyExpansion" << std::endl;
		//return 0;
	}
	else {
		std::cout << "Test failed : keyExpansion" << std::endl;
		//return 1;
	}
	//aes_enc->keyExpansion(output);
	return 1;
}

int test_AES_encryptBlock(AESEncryptor *aes_enc) {
	//std::array<unsigned char, 16> input = {84, 119, 111, 32, 79, 110, 101, 32, 78, 105, 110, 101, 32, 84, 119, 111};
	std::array<unsigned char, 16> input = {84, 79, 78, 32, 119, 110, 105, 84, 111, 101, 110, 119, 32, 32, 101, 111};
	aes_enc->encryptBlock(input);
	return 0;
}

int test_RSA()
{
	std::string str = "hello";
	unsigned long seq = 41245;
	unsigned long cipher = 0;
	RSA_key rk(70457971, 9891923, 547);
	RSA_algorithm ralg(str, rk);

	cipher = ralg.encode_with_rsa(seq);
	std::cout << "cipher is " << cipher << std::endl; // NOT WORKING
	
	unsigned long res = rk.get_n();
	std::cout <<  "modulo n is " << res << std::endl;
	
    	return 0;
}
