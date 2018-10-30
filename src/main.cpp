#include <iostream>
#include <string>

#include "RSA_algorithm.hpp"
#include "RSA_key.hpp"
#include "AESEncryptor.hpp"

int test_AES();
int test_AES_shiftRows(AESEncryptor *aes_enc);
int test_AES_mixColumns(AESEncryptor *aes_enc);
int test_RSA();
int printVector(void *vector, int size);

int main()
{
	
	test_AES();

	return 0;
}

int printVector(std::array<unsigned char, 16> vector, int size){
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			std::cout << int(vector[i*size + j]) << "  ";
		}
		std::cout << std::endl;
	}
	return 0;
}

int test_AES()
{
	unsigned char *test = new unsigned char[3];
	AESEncryptor *aes_enc = new AESEncryptor(test, 3);
	test_AES_shiftRows(aes_enc);
	test_AES_mixColumns(aes_enc);
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
