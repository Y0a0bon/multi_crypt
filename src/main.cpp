#include <iostream>
#include <string>
#include <cmath>

#include "RSA_algorithm.hpp"
#include "RSA_key.hpp"
#include "AESEncryptor.hpp"
#include "AESDecryptor.hpp"
#include "AESTools.hpp"

bool compareArray(unsigned char *input, unsigned char *output, int size);
int test_AESEncryption();
int test_AES_subBytes(AESEncryptor *aes_enc);
int test_AES_shiftRows(AESEncryptor *aes_enc);
int test_AES_mixColumns(AESEncryptor *aes_enc);
int test_AES_getWordFromMatrix(AESEncryptor *aes_enc);
int test_AES_putWordIntoMatrix(AESEncryptor *aes_enc);
int test_AES_keyExpansionComplete(AESEncryptor *aes_enc);
int test_AES_encryptBlock(AESEncryptor *aes_enc);
int test_AESDecryption();
int test_AES_invSubBytes(AESDecryptor *aes_dec);
int test_AES_invShiftRows(AESDecryptor *aes_dec);
int test_AES_invMixColumns(AESDecryptor *aes_dec);
int test_AES_keyExpansionComplete(AESDecryptor *aes_dec);
int test_AES_decryptBlock(AESDecryptor *aes_dec);
int test_RSA();

int main()
{
	
	test_AESEncryption();
	test_AESDecryption();
	return 0;
}

// ********************* AES Encryption tests *********************

int test_AESEncryption()
{
	std::cout << "Testing AES encryption ..." << std::endl;
	unsigned char key[16] = {84, 115, 32, 103, 104, 32, 75, 32, 97, 109, 117, 70, 116, 121, 110, 117};
	AESEncryptor *aes_enc = new AESEncryptor(key, 16);
	
	test_AES_subBytes(aes_enc);

	test_AES_shiftRows(aes_enc);
	test_AES_mixColumns(aes_enc);

	test_AES_getWordFromMatrix(aes_enc);
	test_AES_putWordIntoMatrix(aes_enc);
	
	test_AES_keyExpansionComplete(aes_enc);
	test_AES_encryptBlock(aes_enc);
	
	return 0;
}

int test_AES_subBytes(AESEncryptor *aes_enc)
{
	unsigned char input[16] = {0x00, 0x3C, 0x6E, 0x47, 0x1F, 0x4E, 0x22, 0x74, 0x0E, 0x08, 0x1B, 0x31, 0x54, 0x59, 0x0B, 0x1A};
	unsigned char output[16] = {0x63, 0xEB, 0x9F, 0xA0, 0xC0, 0x2F, 0x93, 0x92, 0xAB, 0x30, 0xAF, 0xC7, 0x20, 0xCB, 0x2B, 0xA2};
	
	aes_enc->subBytes(input, 16);
	
	if (compareArray(input, output, 16)) {
		std::cout << "Test passed : subBytes" << std::endl;
		return 0;
	}
	else {
		std::cout << "Test failed : subBytes" << std::endl;
		return 1;
	}
}

int test_AES_shiftRows(AESEncryptor *aes_enc)
{
	std::array<unsigned char, 16> input = {0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3};
	std::array<unsigned char, 16> output = {0,1,2,3,1,2,3,0,2,3,0,1,3,0,1,2};
	unsigned char input_v[16] = {0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3};
	unsigned char output_v[16] = {0,1,2,3,1,2,3,0,2,3,0,1,3,0,1,2};

	aes_enc->shiftRows(input);
	aes_enc->shiftRows(input_v, 16);

	if ((input == output) && compareArray(input_v, output_v, 16)) {
		std::cout << "Test passed : shiftRows" << std::endl;
		return 0;
	}
	else {
		std::cout << "Test failed : shiftRows" << std::endl;
		return 1;
	}
}

int test_AES_mixColumns(AESEncryptor *aes_enc) {
	std::array<unsigned char, 16> input = {0x63, 0xEB, 0x9F, 0xA0, 0x2F, 0x93, 0x92, 0xC0, 0xAF, 0xC7, 0xAB, 0x30, 0xA2, 0x20, 0xCB, 0x2B};
	std::array<unsigned char, 16> output = {0xBA, 0x84, 0xE8, 0x1B, 0x75, 0xA4, 0x8D, 0x40, 0xF4, 0x8D, 0x06, 0x7D, 0x7A, 0x32, 0x0E, 0x5D};
	
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
	
	aes_enc->getWordFromMatrix(input, key, WORD_SIZE, 0);
	
	if(compareArray(input, output, 4)) {
		std::cout << "Test passed : getWordFromMatrix" << std::endl;
		return 0;
	}
	else {
		std::cout << "Test failed : getWordFromMatrix" << std::endl;
		return 1;
	}
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
}

int test_AES_keyExpansionComplete(AESEncryptor *aes_enc) {
	unsigned char expandedKey[16];
	unsigned char output[16] = {0x28, 0x6D, 0xCC, 0x3B, 0xFD, 0xA4, 0xC0, 0x31, 0xDE, 0x24, 0xA4, 0x6F, 0xF8, 0x4A, 0xFE, 0x26};
	
	aes_enc->getSubkey(expandedKey, 10); // 11th key, so last subkey
	
	if(compareArray(expandedKey, output, 16)) {
		std::cout << "Test passed : keyExpansion" << std::endl;
		return 0;
	}
	else {
		std::cout << "Test failed : keyExpansion" << std::endl;
		return 1;
	}
}

int test_AES_encryptBlock(AESEncryptor *aes_enc) {
	std::array<unsigned char, 16> input = {0x54, 0x4F, 0x4E, 0x20, 0x77, 0x6E, 0x69, 0x54, 0x6F, 0x65, 0x6E, 0x77, 0x20, 0x20, 0x65, 0x6F};
	std::array<unsigned char, 16> output = {0x29, 0x57, 0x40, 0x1A, 0xC3, 0x14, 0x22, 0x02, 0x50, 0x20, 0x99, 0xD7, 0x5F, 0xF6, 0xB3, 0x3A};
	
	aes_enc->encryptBlock(input);
	
	if(input == output) {
		std::cout << "Test passed : encryptBlock" << std::endl;
		return 0;
	}
	else {
		std::cout << "Test failed : encryptBlock" << std::endl;
		return 1;
	}
}

// ********************* AES Decryption tests *********************

int test_AESDecryption()
{
	std::cout << std::endl;
	std::cout << "Testing AES decryption ..." << std::endl;
	
	unsigned char key[16] = {84, 115, 32, 103, 104, 32, 75, 32, 97, 109, 117, 70, 116, 121, 110, 117};
	AESDecryptor *aes_dec = new AESDecryptor(key, 16);
	
	test_AES_invSubBytes(aes_dec);

	test_AES_invShiftRows(aes_dec);
	test_AES_invMixColumns(aes_dec);

	test_AES_keyExpansionComplete(aes_dec);
	test_AES_decryptBlock(aes_dec);
	
	return 0;
}

// FIXME
int test_AES_invSubBytes(AESDecryptor *aes_dec)
{
	unsigned char output[16] = {0x00, 0x3C, 0x6E, 0x47, 0x1F, 0x4E, 0x22, 0x74, 0x0E, 0x08, 0x1B, 0x31, 0x54, 0x59, 0x0B, 0x1A};
	unsigned char input[16] = {0x63, 0xEB, 0x9F, 0xA0, 0xC0, 0x2F, 0x93, 0x92, 0xAB, 0x30, 0xAF, 0xC7, 0x20, 0xCB, 0x2B, 0xA2};
	
	aes_dec->invSubBytes(input, 16);
	
	if ( compareArray(input, output, 16)) {
		std::cout << "Test passed : invSubBytes" << std::endl;
		return 0;
	}
	else {
		std::cout << "Test failed : invSubBytes" << std::endl;
		return 1;
	}
}

int test_AES_invShiftRows(AESDecryptor *aes_dec)
{
	std::array<unsigned char, 16> input = {0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3};
	std::array<unsigned char, 16> output = {0,1,2,3,3,0,1,2,2,3,0,1,1,2,3,0};
	unsigned char input_v[16] = {0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3};
	unsigned char output_v[16] = {0,1,2,3,3,0,1,2,2,3,0,1,1,2,3,0};

	aes_dec->invShiftRows(input);
	aes_dec->invShiftRows(input_v, 16);

	if ((input == output) && compareArray(input_v, output_v, 16)) {
		std::cout << "Test passed : invShiftRows" << std::endl;
		return 0;
	}
	else {
		std::cout << "Test failed : invShiftRows" << std::endl;
		return 1;
	}
}

int test_AES_invMixColumns(AESDecryptor *aes_dec) {
	std::array<unsigned char, 16> input = {0xBA, 0x84, 0xE8, 0x1B, 0x75, 0xA4, 0x8D, 0x40, 0xF4, 0x8D, 0x06, 0x7D, 0x7A, 0x32, 0x0E, 0x5D};
	std::array<unsigned char, 16> output = {0x63, 0xEB, 0x9F, 0xA0, 0x2F, 0x93, 0x92, 0xC0, 0xAF, 0xC7, 0xAB, 0x30, 0xA2, 0x20, 0xCB, 0x2B};

	aes_dec->invMixColumns(input);
	
	if (input == output) {
		std::cout << "Test passed : invMixColumns" << std::endl;
		return 0;
	}
	else {
		std::cout << "Test failed : invMixColumns" << std::endl;
		return 1;
	}
	return 0;
}

int test_AES_keyExpansionComplete(AESDecryptor *aes_dec) {
	unsigned char expandedKey[16];
	unsigned char output[16] = {0x28, 0x6D, 0xCC, 0x3B, 0xFD, 0xA4, 0xC0, 0x31, 0xDE, 0x24, 0xA4, 0x6F, 0xF8, 0x4A, 0xFE, 0x26};
	
	aes_dec->getSubkey(expandedKey, 10); // 11th key, so last subkey
	
	if(compareArray(expandedKey, output, 16)) {
		std::cout << "Test passed : keyExpansion" << std::endl;
		return 0;
	}
	else {
		std::cout << "Test failed : keyExpansion" << std::endl;
		return 1;
	}
}

int test_AES_decryptBlock(AESDecryptor *aes_dec) {
	std::array<unsigned char, 16> input = {0x29, 0x57, 0x40, 0x1A, 0xC3, 0x14, 0x22, 0x02, 0x50, 0x20, 0x99, 0xD7, 0x5F, 0xF6, 0xB3, 0x3A};
	std::array<unsigned char, 16> output = {0x54, 0x4F, 0x4E, 0x20, 0x77, 0x6E, 0x69, 0x54, 0x6F, 0x65, 0x6E, 0x77, 0x20, 0x20, 0x65, 0x6F};
	
	aes_dec->decryptBlock(input);
	
	if(input == output) {
		std::cout << "Test passed : decryptBlock" << std::endl;
		return 0;
	}
	else {
		std::cout << "Test failed : decryptBlock" << std::endl;
		return 1;
	}
}

// ********************* RSA Encryption tests *********************

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
