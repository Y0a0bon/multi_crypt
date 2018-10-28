#include <iostream>
#include <string>

#include "RSA_algorithm.hpp"
#include "RSA_key.hpp"
#include "AESEncryptor.hpp"

int test_AES();
int test_RSA();

int main()
{
	
	test_AES();

	return 0;
}

int test_AES()
{
	unsigned char *test = new unsigned char[3];
	AESEncryptor *aes_enc = new AESEncryptor(test, 3);
	int three = aes_enc->getThree();
	std::cout << "Three : " << three << std::endl;
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
