//
// Created by panda on 2018/6/12.
//

#ifndef JNIDEMO_BASE64_H
#define JNIDEMO_BASE64_H

#include <string>

class base64 {

public:
    static std::string encode(const std::string &decoded_bytes, size_t decoded_length);

    static std::string decode(const std::string &encoded_bytes, int *decoded_length);

    static std::string encode(const std::string &decoded_bytes);

    static std::string decode(const std::string &encoded_bytes);

    static std::string encodestring(const std::string &text);

    static std::string decodestring(const std::string &text);

    static std::string encode_hex(const std::string &src_str);
};

#endif //JNIDEMO_BASE64_H
