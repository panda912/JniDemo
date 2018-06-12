#include "base64.h"
#include <iostream>
#include <openssl/armeabi/include/openssl/ossl_typ.h>
#include <openssl/armeabi/include/openssl/evp.h>
#include <openssl/armeabi/include/openssl/bio.h>
#include <openssl/armeabi/include/openssl/buffer.h>
#include <openssl/armeabi/include/openssl/err.h>

std::string base64::encodestring(const std::string &text) {
    EVP_ENCODE_CTX* ectx = EVP_ENCODE_CTX_new();
    int size = text.size() * 2;
    size = size > 64 ? size : 64;
    unsigned char *out = (unsigned char *) malloc(size);
    int outlen = 0;
    int tlen = 0;
    EVP_EncodeInit(ectx);
    EVP_EncodeUpdate(ectx, out, &outlen, (const unsigned char *) text.c_str(), text.size());
    tlen += outlen;
    EVP_EncodeFinal(ectx, out + tlen, &outlen);
    tlen += outlen;

    std::string str((char *) out, tlen);
    free(out);
    EVP_ENCODE_CTX_free(ectx);
    return str;
}

std::string base64::decodestring(const std::string &text) {
    EVP_ENCODE_CTX* ectx = EVP_ENCODE_CTX_new();
    unsigned char *out = (unsigned char *) malloc(text.size());
    int outlen = 0;
    int tlen = 0;

    EVP_DecodeInit(ectx);
    EVP_DecodeUpdate(ectx, out, &outlen, (const unsigned char *) text.c_str(), text.size());
    tlen += outlen;
    EVP_DecodeFinal(ectx, out + tlen, &outlen);
    tlen += outlen;

    std::string data((char *) out, tlen);
    free(out);
    EVP_ENCODE_CTX_free(ectx);
    return data;
}

/**
 * base64 encode
 * @param decoded_bytes
 * @return
 */
std::string base64::encode(const std::string &decoded_bytes) {
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
std::string base64::decode(const std::string &encoded_bytes) {
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
    BIO_read(bioMem, (void *) decode, (int) buffer_length);
    std::string decoded_bytes(decode);
    BIO_free_all(bioMem);
    return decoded_bytes;
}

/**
 * string to hex string
 * @param src_str
 * @return
 */
std::string base64::encode_hex(const std::string &src_str) {
    const static char hex2[] = "0123456789ABCDEF";
    const char *hexp = hex2;
    std::string dst;
    dst.assign(src_str.size() * 2, ' ');
    for (size_t i = 0; i < src_str.size(); ++i) {
        unsigned char c = (unsigned char) src_str[i];
        dst[i * 2 + 1] = hexp[c & 0xF];
        dst[i * 2] = hexp[(c >> 4) & 0xF];
    }
    return dst;
}