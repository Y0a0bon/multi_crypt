#ifndef DEF_AES_ENCRYPTOR_TEST
#define DEF_AES_ENCRYPTOR_TEST

#include "AESEncryptor.hpp"

int test_AESEncryption();
int test_AES_subBytes(AESEncryptor *aes_enc);
int test_AES_getWordFromMatrix(AESEncryptor *aes_enc);
int test_AES_putWordIntoMatrix(AESEncryptor *aes_enc);
int test_AES_shiftRows(AESEncryptor *aes_enc);
int test_AES_mixColumns(AESEncryptor *aes_enc);
int test_AES_keyExpansionComplete(AESEncryptor *aes_enc);
int test_AES_encryptBlock(AESEncryptor *aes_enc);

#endif 
