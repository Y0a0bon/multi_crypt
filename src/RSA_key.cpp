#include "RSA_key.h"

using namespace std;

	// Constructor
	/*RSA_key::RSA_key(){
	
	}*/
	RSA_key::RSA_key(unsigned long p, unsigned long q, unsigned long exponent) :
	m_p(p), m_q(q), m_exponent(exponent), m_n(p*q), m_d(0)
	{
		
	}

	// Get & Set
	unsigned long get_n() const{
		return m_n;
	}
	
	unsigned long get_exponent() const{
		return m_exponent;
	}
	
	// Phi
	unsigned long RSA_key::get_phi(){
		return (m_p-1) * (m_q-1);
	}