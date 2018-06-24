//
// Created by panda on 2018/6/12.
//

#ifndef JNIDEMO_AES_H
#define JNIDEMO_AES_H

#include <string>

struct Cipher {
    std::string cipher_text;
    int cipher_text_len;
};

class aes {
public:
    static Cipher encrypt(unsigned char *plaintext, unsigned char *key, unsigned char *iv);

    static std::string decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv);
};

#endif //JNIDEMO_AES_H
