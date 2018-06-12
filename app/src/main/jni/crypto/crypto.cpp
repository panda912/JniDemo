#include "jni.h"
#include <iostream>
#include "crypto/base64.h"
#include "crypto/rsa.h"
#include <android/log.h>


using std::string;

#define LOG_TAG "crypto"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

extern "C"
JNIEXPORT jstring JNICALL
Java_com_panda912_jnidemo_crypto_Crypto_encrypt(JNIEnv *env, jobject thiz, jstring base64PublicKey,
                                                jstring content) {
    //jstring 转 char*
    char *base64PublicKeyChars = (char *) env->GetStringUTFChars(base64PublicKey, NULL);
    //char* 转 string
    string base64PublicKeyString = string(base64PublicKeyChars);
    //生成公钥字符串
    string generatedPublicKey = rsa::generatePublicKey(base64PublicKeyString);
    //释放
    env->ReleaseStringUTFChars(base64PublicKey, base64PublicKeyChars);
    //jstring 转 char*
    char *contentChars = (char *) env->GetStringUTFChars(content, NULL);
    //char* 转 string
    string contentString = string(contentChars);
    //释放
    env->ReleaseStringUTFChars(content, contentChars);
    //调用RSA加密函数加密
    string rsaResult = rsa::encryptRSA(generatedPublicKey, contentString);
    if (rsaResult.empty()) {
        return NULL;
    }
    //将密文进行base64
    string base64RSA = base64::encodestring(rsaResult);
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
    string decodeBase64RSA = base64::decodestring(contentString);
    if (decodeBase64RSA.empty()) {
        return NULL;
    }
    //调用RSA解密函数解密
    string origin = rsa::decryptRSA(base64PrivateKeyString, decodeBase64RSA);
    if (origin.empty()) {
        return NULL;
    }
    //string -> char* -> jstring 返回
    jstring result = env->NewStringUTF(origin.c_str());
    return result;
}