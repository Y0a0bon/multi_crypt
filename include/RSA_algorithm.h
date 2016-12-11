#ifndef DEF_RSA_algorithm
#define DEF_RSA_algorithm

#include <string>

class RSA_algorithm{
	
	public :
	
	// Constructor
	//RSA_algorithm(std::string i_seq);
	RSA_algorithm(std::string i_seq, RSA_key rKey);
	
	// Encode and decode one block with RSA
	unsigned long encode_with_rsa(int seq);
	unsigned long decode_with_rsa(int cipher);
	
	// Encode and decode an entire string
	void encode_rsa_multiple(std::string seq);
	void decode_rsa_multiple(std::string cipher);
	
	// Get() and Set()
	std::string get_seq() const;
	std::string get_cipher() const;
	void set_seq(std::string seq);
	void set_cipher(std::string cipher);
	RSA_key get_pk() const;
	
	private :
	
	RSA_key m_rKey;
	std::string m_seq;
	std::string m_cipher;
	
	
}

#endif