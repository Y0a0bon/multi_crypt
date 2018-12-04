// AESDecryptorTest.cpp

#include <iostream>

#include "AESDecryptor.hpp"
#include "AESDecryptorTest.hpp"

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

