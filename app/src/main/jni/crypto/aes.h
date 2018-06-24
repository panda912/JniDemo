//
// Created by panda on 2018/6/12.
//

#ifndef JNIDEMO_AES_H
#define JNIDEMO_AES_H

#include <string>

class aes {
public:

    static std::string encrypt(unsigned char *plaintext, unsigned char *key, unsigned char *iv);

    static std::string decrypt(unsigned char *plaintext, unsigned char *key, unsigned char *iv);
};

#endif //JNIDEMO_AES_H
