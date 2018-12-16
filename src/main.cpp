#include <iostream>
#include <string>
#include <cmath>

//#include "RSA_algorithm.hpp"
//#include "RSA_key.hpp"
#include "AESEncryptorTest.hpp"
#include "AESDecryptorTest.hpp"
#include "AESTools.hpp"

int test_RSA();

int main()
{
	test_AESEncryption();
	test_AESDecryption();
	return 0;
}

// ********************* RSA Encryption tests *********************

int test_RSA()
{
	/*
	std::string str = "hello";
	unsigned long seq = 41245;
	unsigned long cipher = 0;
	RSA_key rk(70457971, 9891923, 547);
	RSA_algorithm ralg(str, rk);

	cipher = ralg.encode_with_rsa(seq);
	std::cout << "cipher is " << cipher << std::endl; // NOT WORKING
	
	unsigned long res = rk.get_n();
	std::cout <<  "modulo n is " << res << std::endl;
	*/
    	return NOT_IMPLEMENTED;
}
