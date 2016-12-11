#include <iostream>

#include "../include/RSA_algorithm.h"
#include "../include/RSA_key.h"


int main()
{
	
	std::string str = "hello";
	RSA_key rk(44654654, 4564785, 4561);
	RSA_algorithm ralg(str, rk);
    return 0;
}