#include <iostream>
#include <string>

#include "RSA_algorithm.hpp"
#include "RSA_key.hpp"
#include "AESEncryptor.hpp"

int test_AES();
int test_AES_shiftRows(AESEncryptor *aes_enc);
int test_RSA();
int printVector(void *vector, int size);

int main()
{
	
	test_AES();

	return 0;
}

int printVector(unsigned char *vector, int size){
	if (vector == nullptr || size < 0) {
		return 1;
	}
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
	int three = aes_enc->getThree();
	std::cout << "Three : " << three << std::endl;
	test_AES_shiftRows(aes_enc);
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
	// FIXME Use array instead for easier comparison
	if (input == output) {
		std::cout << "Test passed : shiftRows" << std::endl;
		return 0;
	}
	else {
		std::cout << "Test failed : shiftRows" << std::endl;
		return 1;
	}
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
