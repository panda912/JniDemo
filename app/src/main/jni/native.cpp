#include "jni.h"
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include<openssl/err.h>
#include <iostream>
#include <android/log.h>

using std::string;

#define LOG_TAG "crypto"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


/**
 * 根据公钥base64字符串（没换行）生成公钥文本内容
 * @param base64EncodedKey
 * @return
 */
std::string generatePublicKey(std::string base64EncodedKey) {
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
std::string generatePrivateKey(std::string base64EncodedKey) {
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
 * base64 encode
 * @param decoded_bytes
 * @return
 */
std::string base64_encode(const std::string &decoded_bytes) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;
    b64 = BIO_new(BIO_f_base64());
    //不换行
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);
    //encode
    BIO_write(bio, decoded_bytes.c_str(), (int) decoded_bytes.length());
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);
    //这里的第二个参数很重要，必须赋值！否则base64后的字符串长度会出现异常，导致decode的时候末尾会出现一大堆的乱码，
    std::string result(bufferPtr->data, bufferPtr->length);
    BIO_free_all(bio);
    return result;
}

/**
 * base64 decode
 * @param encoded_bytes
 * @return
 */
std::string base64_decode(const std::string &encoded_bytes) {
    BIO *bioMem, *b64;
    b64 = BIO_new(BIO_f_base64());
    bioMem = BIO_new_mem_buf((void *) encoded_bytes.c_str(), -1);
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bioMem = BIO_push(b64, bioMem);
    //获得解码长度
    size_t buffer_length = BIO_get_mem_data(bioMem, NULL);
    char *decode = (char *) malloc(buffer_length + 1);
    //填充0
    memset(decode, 0, buffer_length + 1);
    LOGE("----->%d", strlen(decode));
    BIO_read(bioMem, (void *) decode, (int) buffer_length);
    std::string decoded_bytes(decode);
    BIO_free_all(bioMem);
    LOGE("base64_decode decoded_bytes: %d, decode_length: %d, buffer_length: %d, decode: %s, decoded_bytes: %s",
         decoded_bytes.length(), strlen(decode), buffer_length, decode, decoded_bytes.c_str());
    return decoded_bytes;
}

/**
 * 使用公钥对明文加密
 * @param publicKey
 * @param from
 * @return
 */
std::string encryptRSA(const std::string &publicKey, const std::string &from) {
    BIO *bio = NULL;
    RSA *rsa_public_key = NULL;
    //从字符串读取RSA公钥串
    if ((bio = BIO_new_mem_buf((void *) publicKey.c_str(), -1)) == NULL) {
        std::cout << "BIO_new_mem_buf failed!" << std::endl;
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
    //RSA_PKCS1_PADDING 最大加密长度 为 128 -11
    //RSA_NO_PADDING 最大加密长度为  128
    //rsa_size = rsa_size - RSA_PKCS1_PADDING_SIZE;
    //动态分配内存，用于存储加密后的密文
    unsigned char *to = (unsigned char *) malloc(rsa_size + 1);
    //填充0
    memset(to, 0, rsa_size + 1);
    LOGE("--->%s", to);
    //明文长度
    int flen = from.length();
    // 加密，返回值为加密后的密文长度，-1表示失败
    int status = RSA_public_encrypt(flen, (const unsigned char *) from.c_str(), to, rsa_public_key,
                                    RSA_PKCS1_PADDING);
    //异常处理
    if (status < 0) {
        //资源释放
        free(to);
        BIO_free_all(bio);
        RSA_free(rsa_public_key);
        //清除管理CRYPTO_EX_DATA的全局hash表中的数据，避免内存泄漏
        CRYPTO_cleanup_all_ex_data();
        LOGE("encryptRSA status: %d", status);
        return "";
    }
    //赋值密文
    std::string result((char *) to, status);
    std::string temp((char *) to);
    //资源释放
    free(to);
    BIO_free_all(bio);
    RSA_free(rsa_public_key);
    //清除管理CRYPTO_EX_DATA的全局hash表中的数据，避免内存泄漏
    CRYPTO_cleanup_all_ex_data();
    LOGE("encryptRSA:%s, to.len: %d, rsa_size: %d", result.c_str(), temp.length(), rsa_size);
    return result;
}

/**
 * 使用私钥对密文解密
 * @param privetaKey
 * @param from
 * @return
 */
std::string decryptRSA(const std::string &privetaKey, const std::string &from) {
    BIO *bio = NULL;
    RSA *rsa_private_key = NULL;
    //从字符串读取RSA公钥串
    if ((bio = BIO_new_mem_buf((void *) privetaKey.c_str(), -1)) == NULL) {
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
    unsigned char *to = (unsigned char *) malloc(rsa_size + 1);
    //填充0
    memset(to, 0, rsa_size + 1);
    //密文长度
    int flen = from.length();
    // RSA_NO_PADDING
    // RSA_PKCS1_PADDING
    //解密，返回值为解密后的名文长度，-1表示失败
    int status = RSA_private_decrypt(flen, (const unsigned char *) from.c_str(), to,
                                     rsa_private_key, RSA_PKCS1_PADDING);
    LOGE("RSA_private_decrypt status: %d, flen: %d, rsa_size: %d", status, flen, rsa_size);
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
    std::string result((char *) to, status);
    //释放资源
    free(to);
    BIO_free_all(bio);
    RSA_free(rsa_private_key);
    //清除管理CRYPTO_EX_DATA的全局hash表中的数据，避免内存泄漏
    CRYPTO_cleanup_all_ex_data();
    return result;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_panda912_jnidemo_crypto_Crypto_encrypt(JNIEnv *env, jobject thiz, jstring base64PublicKey,
                                                jstring content) {
    //jstring 转 char*
    char *base64PublicKeyChars = (char *) env->GetStringUTFChars(base64PublicKey, NULL);
    //char* 转 string
    string base64PublicKeyString = string(base64PublicKeyChars);
    //生成公钥字符串
//    string generatedPublicKey = generatePublicKey(base64PublicKeyString);
    //释放
    env->ReleaseStringUTFChars(base64PublicKey, base64PublicKeyChars);
    //jstring 转 char*
    char *contentChars = (char *) env->GetStringUTFChars(content, NULL);
    //char* 转 string
    string contentString = string(contentChars);
    //释放
    env->ReleaseStringUTFChars(content, contentChars);
    //调用RSA加密函数加密
    string rsaResult = encryptRSA(base64PublicKeyString, contentString);
    if (rsaResult.empty()) {
        return NULL;
    }
    //将密文进行base64
    string base64RSA = base64_encode(rsaResult);
    if (base64RSA.empty()) {
        return NULL;
    }
    //string -> char* -> jstring 返回
    jstring result = env->NewStringUTF(base64RSA.c_str());
    return result;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_panda912_jnidemo_crypto_Crypto_decrypt(JNIEnv *env, jobject thiz, jstring base64PrivateKey,
                                                jstring content) {
    //jstring 转 char*
    char *base64PrivateKeyChars = (char *) env->GetStringUTFChars(base64PrivateKey, NULL);
    //char* 转 string
    string base64PrivateKeyString = string(base64PrivateKeyChars);
    //生成密钥字符串
//    string generatedPrivateKey = generatePrivateKey(base64PrivateKeyString);
    //释放
    env->ReleaseStringUTFChars(base64PrivateKey, base64PrivateKeyChars);
    //jstring 转 char*
    char *contentChars = (char *) env->GetStringUTFChars(content, NULL);
    //char* 转 string
    string contentString = string(contentChars);
    //释放
    env->ReleaseStringUTFChars(content, contentChars);
    //将密文进行base64
    string decodeBase64RSA = base64_decode(contentString);
    if (decodeBase64RSA.empty()) {
        return NULL;
    }
    //调用RSA解密函数解密
    string origin = decryptRSA(base64PrivateKeyString, decodeBase64RSA);
    if (origin.empty()) {
        return NULL;
    }
    //string -> char* -> jstring 返回
    jstring result = env->NewStringUTF(origin.c_str());
    return result;
}