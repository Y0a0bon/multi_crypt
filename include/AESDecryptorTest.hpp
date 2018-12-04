#ifndef DEF_AES_DECRYPTOR_TEST
#define DEF_AES_DECRYPTOR_TEST

#include "AESDecryptor.hpp"

int test_AESDecryption();
int test_AES_invSubBytes(AESDecryptor *aes_dec);
int test_AES_invShiftRows(AESDecryptor *aes_dec);
int test_AES_invMixColumns(AESDecryptor *aes_dec);
int test_AES_keyExpansionComplete(AESDecryptor *aes_dec);
int test_AES_decryptBlock(AESDecryptor *aes_dec);

#endif
