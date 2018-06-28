//
// Created by panda on 2018/6/12.
//

#ifndef JNIDEMO_BASE64_H
#define JNIDEMO_BASE64_H

#include <string>
using namespace std;

class base64 {

public:
    static string encode(const string &decoded_bytes, size_t decoded_length);

    static string decode(const string &encoded_bytes, int *decoded_length);

    static string encode(const string &decoded_bytes);

    static string decode(const string &encoded_bytes);

    static string encodestring(const string &text);

    static string decodestring(const string &text);

    static string encode_hex(const string &src_str);
};

#endif //JNIDEMO_BASE64_H
