#ifndef DEF_RSA_algorithm
#define DEF_RSA_algorithm

#include <string>
#include "RSA_key.h"

class RSA_algorithm{
	
	public :
	
	// Constructor
	//RSA_algorithm(std::string i_seq);
	RSA_algorithm(std::string i_seq, RSA_key rKey);
	
	// Encode and decode one block with RSA
	unsigned long encode_with_rsa(unsigned long seq);
	unsigned long decode_with_rsa(unsigned long cipher);
	
	// Encode and decode an entire string
	void encode_rsa_multiple(std::string seq);
	void decode_rsa_multiple(std::string cipher);
	
	// Get() and Set()
	std::string get_seq() const;
	std::string get_cipher() const;
	void set_seq(std::string seq);
	void set_cipher(std::string cipher);
	RSA_key get_pk() const;
	
	unsigned long fast_exp(unsigned long blck);
	
	private :
	
	RSA_key m_rKey;
	std::string m_seq;
	std::string m_cipher;
	
	
};

#endif