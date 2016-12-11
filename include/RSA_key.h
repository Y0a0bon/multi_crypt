#ifndef DEF_RSA_key
#define DEF_RSA_key

#include <string>

class RSA_key{
	
	public :
	
	// Constructor
	//RSA_key();
	RSA_key(unsigned long p, unsigned long q, unsigned long exponent);
	
	// Get & Set
	unsigned long get_n() const;
	unsigned long get_exponent() const;
	
	private :
	
	unsigned long get_d() const;
	
	unsigned long m_p;
	unsigned long m_q;
	unsigned long m_n;
	unsigned long m_exponent;
	unsigned long m_d;
	
}

#endif