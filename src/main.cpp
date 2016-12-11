#include <iostream>

#include "../include/RSA_algorithm.h"
#include "../include/RSA_key.h"


int main()
{
	
	std::string s = "hello";
	RSA_key rk(44654654, 4564785, 4561);
	RSA_algorithm ralg(s, rk);
    return 0;
}