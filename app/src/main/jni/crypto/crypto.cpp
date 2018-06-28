#include "jni.h"
#include <iostream>
#include "crypto/rsa.h"
#include "crypto/aes.h"
#include "crypto/base64.h"
#include "crypto/mydigest.h"
#include <android/log.h>

using std::string;

#define LOG_TAG "crypto"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

extern "C"
JNIEXPORT jstring JNICALL
Java_com_panda912_jnidemo_crypto_Crypto_encryptRSA(JNIEnv *env, jobject thiz, jstring publicKey,
                                                   jstring content) {
    //jstring 转 char*
    char *base64PublicKeyChars = (char *) env->GetStringUTFChars(publicKey, NULL);
    //char* 转 string
    string base64PublicKeyString = string(base64PublicKeyChars);
    //生成公钥字符串
    string generatedPublicKey = rsa::generatePublicKey(base64PublicKeyString);
    //释放
    env->ReleaseStringUTFChars(publicKey, base64PublicKeyChars);
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
Java_com_panda912_jnidemo_crypto_Crypto_decryptRSA(JNIEnv *env, jobject thiz, jstring privateKey,
                                                   jstring content) {
    //jstring 转 char*
    char *base64PrivateKeyChars = (char *) env->GetStringUTFChars(privateKey, NULL);
    //char* 转 string
    string base64PrivateKeyString = string(base64PrivateKeyChars);
    //生成密钥字符串
//    string generatedPrivateKey = generatePrivateKey(base64PrivateKeyString);
    //释放
    env->ReleaseStringUTFChars(privateKey, base64PrivateKeyChars);
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

extern "C"
JNIEXPORT jobject JNICALL
Java_com_panda912_jnidemo_crypto_Crypto_encryptAES(JNIEnv *env, jobject thiz, jstring plainText,
                                                   jstring key, jstring iv) {
    // jstring 转 char*
    char *plainTextChars = (char *) env->GetStringUTFChars(plainText, NULL);
    char *keyChars = (char *) env->GetStringUTFChars(key, NULL);
    char *ivChars = (char *) env->GetStringUTFChars(iv, NULL);
    // encrypt
    Cipher cipher = aes::encrypt(reinterpret_cast<unsigned char *>(plainTextChars),
                                 reinterpret_cast<unsigned char *>(keyChars),
                                 reinterpret_cast<unsigned char *>(ivChars));
    // 释放
    env->ReleaseStringUTFChars(plainText, plainTextChars);
    env->ReleaseStringUTFChars(key, keyChars);
    env->ReleaseStringUTFChars(iv, ivChars);
    // base64
    string cipherText = base64::encodestring(cipher.cipher_text);

    jclass jClassCipher = env->FindClass("com/panda912/jnidemo/crypto/Crypto$Cipher");
    jfieldID jFieldCipherText = env->GetFieldID(jClassCipher, "cipherText", "Ljava/lang/String;");
    jfieldID jFieldCipherTextLength = env->GetFieldID(jClassCipher, "cipherTextLength", "I");
    jobject jCipher = env->AllocObject(jClassCipher);
    env->SetObjectField(jCipher, jFieldCipherText, env->NewStringUTF(cipherText.c_str()));
    env->SetIntField(jCipher, jFieldCipherTextLength, cipher.cipher_text_len);
    return jCipher;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_panda912_jnidemo_crypto_Crypto_decryptAES(JNIEnv *env, jobject thiz, jobject cipher,
                                                   jstring key, jstring iv) {
    jclass jClassCipher = env->FindClass("com/panda912/jnidemo/crypto/Crypto$Cipher");
    jfieldID jFieldCipherText = env->GetFieldID(jClassCipher, "cipherText", "Ljava/lang/String;");
    jfieldID jFieldCipherTextLength = env->GetFieldID(jClassCipher, "cipherTextLength", "I");
    jstring cipherText = (jstring) env->GetObjectField(cipher, jFieldCipherText);
    jint cipherTextLength = env->GetIntField(cipher, jFieldCipherTextLength);

    char *cipherTextChars = (char *) env->GetStringUTFChars(cipherText, NULL);
    char *keyChars = (char *) env->GetStringUTFChars(key, NULL);
    char *ivChars = (char *) env->GetStringUTFChars(iv, NULL);
    string cipherTextString = string(cipherTextChars);
    string decodeString = base64::decodestring(cipherTextString);
    // decrypt
    string plainText = aes::decrypt((unsigned char *) decodeString.c_str(), cipherTextLength,
                                    reinterpret_cast<unsigned char *>(keyChars),
                                    reinterpret_cast<unsigned char *>(ivChars));
    // 释放
    env->ReleaseStringUTFChars(cipherText, cipherTextChars);
    env->ReleaseStringUTFChars(key, keyChars);
    env->ReleaseStringUTFChars(iv, ivChars);
    return env->NewStringUTF(plainText.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_panda912_jnidemo_crypto_Crypto_base64Encode(JNIEnv *env, jobject thiz, jstring content) {
    char *contentChar = (char *) env->GetStringUTFChars(content, NULL);
    string contentString = string(contentChar);
    env->ReleaseStringUTFChars(content, contentChar);
    string resultString = base64::encodestring(contentString);
    return env->NewStringUTF(resultString.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_panda912_jnidemo_crypto_Crypto_base64Decode(JNIEnv *env, jobject thiz, jstring content) {
    char *contentChar = (char *) env->GetStringUTFChars(content, NULL);
    string contentString = string(contentChar);
    env->ReleaseStringUTFChars(content, contentChar);
    string resultString = base64::decodestring(contentString);
    return env->NewStringUTF(resultString.c_str());
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_panda912_jnidemo_crypto_Crypto_digest(JNIEnv *env, jobject thiz, jstring message,
                                               jstring type) {
    char *msgChar = (char *) env->GetStringUTFChars(message, NULL);
    char *typeChar = (char *) env->GetStringUTFChars(type, NULL);
    string result = mydigest::calcDigest(msgChar, typeChar);
    env->ReleaseStringUTFChars(message, msgChar);
    env->ReleaseStringUTFChars(type, typeChar);
    return env->NewStringUTF(result.c_str());
}