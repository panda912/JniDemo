//
// Created by panda on 2018/6/12.
//

#include "rsa.h"
#include <openssl/armeabi/include/openssl/ossl_typ.h>
#include <openssl/armeabi/include/openssl/bio.h>
#include <openssl/armeabi/include/openssl/rsa.h>
#include <openssl/armeabi/include/openssl/pem.h>
#include <openssl/armeabi/include/openssl/err.h>
#include <iostream>

/**
 * 根据公钥base64字符串（没换行）生成公钥文本内容
 * @param base64EncodedKey
 * @return
 */
std::string rsa::generatePublicKey(std::string base64EncodedKey) {
    std::string publicKey = base64EncodedKey;
    size_t base64Length = 64;//每64个字符一行
    size_t publicKeyLength = base64EncodedKey.size();
    for (size_t i = base64Length; i < publicKeyLength; i += base64Length) {
        //每base64Length个字符，增加一个换行
        if (base64EncodedKey[i] != '\n') {
            publicKey.insert(i, "\n");
        }
        i++;
    }
    //最前面追加公钥begin字符串
    publicKey.insert(0, "-----BEGIN PUBLIC KEY-----\n");
    //最前面追加公钥end字符串
    publicKey.append("\n-----END PUBLIC KEY-----");
    return publicKey;
}

/**
 * 根据私钥base64字符串（没换行）生成私钥文本内容
 * @param base64EncodedKey
 * @return
 */
std::string rsa::generatePrivateKey(std::string base64EncodedKey) {
    std::string privateKey = base64EncodedKey;
    size_t base64Length = 64;//每64个字符一行
    size_t privateKeyLength = base64EncodedKey.size();
    for (size_t i = base64Length; i < privateKeyLength; i += base64Length) {
        //每base64Length个字符，增加一个换行
        if (base64EncodedKey[i] != '\n') {
            privateKey.insert(i, "\n");
        }
        i++;
    }
    //最前面追加私钥begin字符串
    privateKey.insert(0, "-----BEGIN PRIVATE KEY-----\n");
    //最后面追加私钥end字符串
    privateKey.append("\n-----END PRIVATE KEY-----");
    return privateKey;
}

/**
 * 使用公钥对明文加密
 * @param publicKey
 * @param from
 * @return
 */
std::string rsa::encryptRSA(const std::string &publicKey, const std::string &from) {
    BIO *bio = NULL;
    RSA *rsa_public_key = NULL;
    //从字符串读取RSA公钥串
    if ((bio = BIO_new_mem_buf((void *) PUBLIC_KEY, -1)) == NULL) {
        return "";
    }
    //读取公钥
    rsa_public_key = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL);
    //异常处理
    if (rsa_public_key == NULL) {
        //资源释放
        BIO_free_all(bio);
        //清除管理CRYPTO_EX_DATA的全局hash表中的数据，避免内存泄漏
        CRYPTO_cleanup_all_ex_data();
        return "";
    }
    //rsa模的位数
    int rsa_size = RSA_size(rsa_public_key);
    //动态分配内存，用于存储加密后的密文
    char *to = (char *) malloc(rsa_size + 1);
    bzero(to, rsa_size);
    //填充0
//    memset(to, 0, rsa_size + 1);
    // 加密，返回值为加密后的密文长度，-1表示失败
    int status = RSA_public_encrypt(from.length(), (unsigned char *) from.c_str(),
                                    (unsigned char *) to, rsa_public_key, RSA_PKCS1_PADDING);
    //异常处理
    if (status < 0) {
        //资源释放
        free(to);
        BIO_free_all(bio);
        RSA_free(rsa_public_key);
        //清除管理CRYPTO_EX_DATA的全局hash表中的数据，避免内存泄漏
        CRYPTO_cleanup_all_ex_data();
        return "";
    }
    //赋值密文
    std::string result(to, status);
    //资源释放
    free(to);
    BIO_free_all(bio);
    RSA_free(rsa_public_key);
    //清除管理CRYPTO_EX_DATA的全局hash表中的数据，避免内存泄漏
    CRYPTO_cleanup_all_ex_data();
    return result;
}

/**
 * 使用私钥对密文解密
 * @param privateKey
 * @param from
 * @return
 */
std::string rsa::decryptRSA(const std::string &privetaKey, const std::string &from) {
    BIO *bio = NULL;
    RSA *rsa_private_key = NULL;
    //从字符串读取RSA公钥串
    if ((bio = BIO_new_mem_buf((void *) PRIVATE_KEY, -1)) == NULL) {
        std::cout << "BIO_new_mem_buf failed!" << std::endl;
        return "";
    }
    //读取私钥
    rsa_private_key = PEM_read_bio_RSAPrivateKey(bio, NULL, NULL, NULL);
    //异常处理
    if (rsa_private_key == NULL) {
        //资源释放
        BIO_free_all(bio);
        //清除管理CRYPTO_EX_DATA的全局hash表中的数据，避免内存泄漏
        CRYPTO_cleanup_all_ex_data();
        return "";
    }
    //rsa模的位数
    int rsa_size = RSA_size(rsa_private_key);
    //动态分配内存，用于存储解密后的明文
    char *to = (char *) malloc(rsa_size + 1);
    //填充0
    memset(to, 0, rsa_size + 1);
    //密文长度
    int flen = from.length();
    // RSA_NO_PADDING
    // RSA_PKCS1_PADDING
    //解密，返回值为解密后的名文长度，-1表示失败
    int status = RSA_private_decrypt(flen, (unsigned char *) from.c_str(),
                                     (unsigned char *) to, rsa_private_key, RSA_PKCS1_PADDING);
    //异常处理率
    if (status < 0) {
        //释放资源
        free(to);
        BIO_free_all(bio);
        RSA_free(rsa_private_key);
        //清除管理CRYPTO_EX_DATA的全局hash表中的数据，避免内存泄漏
        CRYPTO_cleanup_all_ex_data();
        return "";
    }
    //赋值明文，是否需要指定to的长度？
    std::string result(to, status);
    //释放资源
    free(to);
    BIO_free_all(bio);
    RSA_free(rsa_private_key);
    //清除管理CRYPTO_EX_DATA的全局hash表中的数据，避免内存泄漏
    CRYPTO_cleanup_all_ex_data();
    return result;
}
