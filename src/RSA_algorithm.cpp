#include "RSA_algorithm.h"

using namespace std;


	// Constructor
	/*RSA_algorithm(std::string i_seq){
		
		
	}*/
	
	
	RSA_algorithm::RSA_algorithm(std::string seq, RSA_key rKey): 
	m_seq(seq), m_rKey(rKey)
	{
		
		
	}

	
	// Encode and decode one block with RSA
	unsigned long RSA_algorithm::encode_with_rsa(unsigned long seq){
		
		unsigned long c = 0;
		c = RSA_algorithm::fast_exp(seq);
		
		return c;
	}
	unsigned long RSA_algorithm::decode_with_rsa(unsigned long cipher){
		// TODO
		return 0;
	}

	// Encode and decode an entire string and put it in message/cipher
	void RSA_algorithm::encode_rsa_multiple(std::string message){
		// TODO
	}
	void RSA_algorithm::decode_rsa_multiple(std::string cipher){
		// TODO
	}

	// Get() and Set()
	std::string RSA_algorithm::get_seq() const{
		return m_seq;
	}

	std::string RSA_algorithm::get_cipher() const{
		return m_cipher;
	}

	void RSA_algorithm::set_seq(std::string seq){
		m_seq = seq;
	}

	void RSA_algorithm::set_cipher(std::string cipher){
		m_cipher = cipher;
	}

	/**
	 * Function fast_exp()
	 * Fast exponentiation
	 **/
	unsigned long RSA_algorithm::fast_exp(unsigned long blck){
		unsigned long c = 1;
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
		