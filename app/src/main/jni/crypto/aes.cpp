//
// Created by panda on 2018/6/12.
//

#include <string>
#include "aes.h"
#include <openssl/armeabi/include/openssl/aes.h>
#include <openssl/armeabi/include/openssl/evp.h>
#include <android/log.h>

#include <openssl/armeabi/include/openssl/conf.h>
#include <openssl/err.h>
#include <string.h>

using std::string;

#define LOG_TAG "crypto"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

/**
 * https://www.cnblogs.com/cocoajin/p/6121706.html
 * https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption#Encrypting_the_message
 * @param key
 * @param iv
 * @param ptext
 * @param ctext
 */
void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

Cipher aes::encrypt(unsigned char *plaintext, unsigned char *key, unsigned char *iv) {
    EVP_CIPHER_CTX *ctx;

    int len;
    int ciphertext_len;

    // AES算法的块（block）的长度固定为16字节(128bit)，cipherLen = (clearLen / 16 + 1) * 16
    int plaintext_len = strlen((char *) plaintext);
    int size = (plaintext_len / AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE;
    unsigned char ciphertext[size];

    if (!(ctx = EVP_CIPHER_CTX_new())) {
        EVP_CIPHER_CTX_cleanup(ctx);
        handleErrors();
    }
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
        EVP_CIPHER_CTX_cleanup(ctx);
        handleErrors();
    }
    EVP_CIPHER_CTX_set_padding(ctx, 1);
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len)) {
        EVP_CIPHER_CTX_cleanup(ctx);
        handleErrors();
    }
    ciphertext_len = len;
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) {
        EVP_CIPHER_CTX_cleanup(ctx);
        handleErrors();
    }
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);
    std::string result((char *) ciphertext, ciphertext_len);

    Cipher cipher_struct;
    cipher_struct.cipher_text = result;
    cipher_struct.cipher_text_len = ciphertext_len;
    return cipher_struct;
}

string aes::decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv) {
    EVP_CIPHER_CTX *ctx;

    int len;
    int plaintext_len;
    unsigned char plaintext[ciphertext_len];

    /* Create and initialise the context */
    if (!(ctx = EVP_CIPHER_CTX_new())) {
        EVP_CIPHER_CTX_cleanup(ctx);
        handleErrors();
    }
    /* Initialise the decryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits */
    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
        EVP_CIPHER_CTX_cleanup(ctx);
        handleErrors();
    }
    EVP_CIPHER_CTX_set_padding(ctx, 1);
    /* Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary
     */
    if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len)) {
        EVP_CIPHER_CTX_cleanup(ctx);
        handleErrors();
    }
    plaintext_len = len;
    /* Finalise the decryption. Further plaintext bytes may be written at
     * this stage.
     */
    if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) {
        EVP_CIPHER_CTX_cleanup(ctx);
        handleErrors();
    }
    plaintext_len += len;

    plaintext[plaintext_len] = '\0';

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);
    std::string result((char *) plaintext, plaintext_len);
    return result;
}
