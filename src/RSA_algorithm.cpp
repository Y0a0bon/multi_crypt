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
	std::string RSA_algorithm::get_seq() const{
		return m_seq;
	}

	std::string RSA_algorithm::get_cipher() const{
		return m_cipher;
	}

	void RSA_algorithm::set_seq(std::string new_message){
		m_seq = new_message;
	}

	void set_cipher(std::string new_cipher){
		m_cipher = new_cipher;
	}

	
	
	
	
	int RSA_algorithm::fast_exp(int blck){
		int c = 1;
		unsigned long e_sv = m_rKey.get_exponent();
		while(e_sv > 0){
			if(e_sv % 2 == 0)
				e_sv /= 2;
			else{
				c = (c * blck) % m_rKey.get_n();
				e_sv = (e_sv - 1) / 2;
			}
			blck = (blck * blck) % m_rKey.get_n();
		}
		return c;
	}
		