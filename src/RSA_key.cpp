#include "RSA_algorithm.h"

using namespace std;


	// Constructor
	/*RSA_algorithm(std::string i_seq){
		
		
	}*/
	
	
	RSA_algorithm::RSA_algorithm(std::string i_seq, unsigned long p, unsigned long q, unsigned long exponent): 
	m_seq(seq), m_rKey(p, q, exponent)
	{
		
		
	}


	// Encode and decode one block with RSA
	unsigned long RSA_algorithm::encode_with_rsa(int message){
		
		
		return 0;
	}
	unsigned long RSA_algorithm::decode_with_rsa(int cipher){
		
		return 0;
	}

	// Encode and decode an entire string and put it in message/cipher
	void RSA_algorithm::encode_rsa_multiple(std::string message){}
	void RSA_algorithm::decode_rsa_multiple(std::string cipher){}

	// Get() and Set()
	std::string RSA_algorithm::get_message() const{
		return message;
	}

	std::string RSA_algorithm::get_cipher() const{
		return cipher;
	}

	void RSA_algorithm::set_message(std::string new_message){
		message = new_message;
	}

	void set_cipher(std::string new_cipher){
		cipher = new_cipher;
	}
