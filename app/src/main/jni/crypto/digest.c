//
// Created by panda on 2018/6/26.
// https://www.openssl.org/docs/man1.1.0/crypto/EVP_DigestInit.html
//

#include "digest.h"
#include <stdio.h>
#include <openssl/evp.h>
#include <android/log.h>
#include <string.h>

#define LOG_TAG "digest"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

char *digest(char *message, char *type) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    unsigned char *md_value = malloc(EVP_MAX_MD_SIZE);
    unsigned char *result = malloc(EVP_MAX_MD_SIZE);
    memset(result, 0, EVP_MAX_MD_SIZE);
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

    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, message, strlen(message));
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    EVP_MD_CTX_free(mdctx);

    char *c = malloc(1);
    for (i = 0; i < md_len; i++) {
        sprintf(c, "%02x", md_value[i]);
        strcat(result, c);
    }

    return (char *) result;
}
