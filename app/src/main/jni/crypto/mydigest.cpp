//
// Created by panda on 6/28/18.
//

#include "mydigest.h"
#include <stdio.h>
#include <openssl/evp.h>
#include <android/log.h>

#define LOG_TAG "digest"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


string decInt2HexStr(long long num) {
    string str;
    long long temp = num / 16;
    int left = num % 16;
    if (temp > 0)
        str += decInt2HexStr(temp);
    if (left < 10)
        str += (left + '0');
    else
        str += ('A' + left - 10);

    return str;
}

string mydigest::calcDigest(char *message, char *type) {
    EVP_MD_CTX *ctx;
    const EVP_MD *md;
    unsigned char *md_value = (unsigned char *) malloc(EVP_MAX_MD_SIZE);
    unsigned int md_len, i;

    if (!type) {
        LOGE("Usage: mdtest digestname");
        exit(1);
    }

    md = EVP_get_digestbyname(type);

    if (!md) {
        LOGE("Unknown message digest %s", type);
        exit(1);
    }

    if (NULL == md_value) {
        LOGE("malloc failed");
        abort();
    }

    ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, md, NULL);
    EVP_DigestUpdate(ctx, message, strlen(message));
    EVP_DigestFinal_ex(ctx, md_value, &md_len);
    EVP_MD_CTX_free(ctx);

    string result;
    for (i = 0; i < md_len; i++) {
        char *temp = new char[1];
//        sprintf(temp, "%02x", md_value[i]);
        snprintf(temp, sizeof(temp), "%02x", md_value[i]);
        string s(temp);
        result += s;
        delete[] temp;
    }
    if (NULL != md_value) {
        free(md_value);
    }
    LOGE("%s", result.c_str());
    return result;
}

string mydigest::calcFileDigest(char *filePath, char *type) {
    EVP_MD_CTX *ctx;
    const EVP_MD *md;
    unsigned char *md_value = (unsigned char *) malloc(EVP_MAX_MD_SIZE);
    unsigned int md_len, i;

    int len = 0;
    unsigned char buffer[1024] = {0};

    FILE *pFile = fopen(filePath, "rb+");
    if (pFile == 0) {
        LOGE("can not read the file : %s", filePath);
        exit(1);
    }


    if (!type) {
        LOGE("Usage: mdtest digestname");
        exit(1);
    }

    md = EVP_get_digestbyname(type);

    if (!md) {
        LOGE("Unknown message digest %s", type);
        exit(1);
    }

    if (NULL == md_value) {
        LOGE("malloc failed");
        abort();
    }

    ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, md, NULL);
    while ((len = fread(buffer, 1, 1024, pFile)) > 0) {
        EVP_DigestUpdate(ctx, buffer, len);
    }
    EVP_DigestFinal_ex(ctx, md_value, &md_len);
    EVP_MD_CTX_free(ctx);

    string result;
    for (i = 0; i < md_len; i++) {
        char *temp = new char[1];
        snprintf(temp, sizeof(temp), "%02x", md_value[i]);
        string s(temp);
        result += s;
        delete[] temp;
    }
    if (NULL != md_value) {
        free(md_value);
    }
    LOGE("%s", result.c_str());
    return result;
}

