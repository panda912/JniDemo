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
        printf("Usage: mdtest digestname\n");
        exit(1);
    }

    md = EVP_get_digestbyname(type);

    if (!md) {
        printf("Unknown message digest %s\n", type);
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
    return result;
}
