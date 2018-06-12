//
// Created by panda on 2018/6/12.
//

#ifndef JNIDEMO_RSA_H
#define JNIDEMO_RSA_H

#include <string>

#define PRIVATE_KEY "-----BEGIN PRIVATE KEY-----\nMIICdgIBADANBgkqhkiG9w0BAQEFAASCAmAwggJcAgEAAoGBAMq+dLwFJYNn3xmc\nbqT1zPLVrTf4jApvP7GkGQzmxQ2KboonB6RA7D0y6+Cyio6wmN9SEKDww+dFMwWp\nxVqXKMayy917VtdlIUXkH3Zu8e+FtYx7+UNN2ezo/ddTbGzQ6y2KfUay57xO1yUC\nzjL3GUq2341IyoutVPst6z/34aIxAgMBAAECgYANpIdCZ65Ai2rN1GL1oryp0osX\naxgxU48bqwksfxLfeGM71KiE+wFqlNSeiCUeuO9wh5sq2Ui1dUibpvLqx6UsqtwL\nzAZ02WLxl+jFtjs+H97PHXzfEwEXwzcpdFiJjBMi1ARvcdGWGXFlpjVEo03UukwD\nIs6c5AWGK2OK2ScPYQJBAP8Us63kPGlPr0R0s2SO/lpfd9UCfA9wfVbwmr/9jLxX\nC0Pqje8g7vlaR8jqteVd9/duPFqiKRruJw3yVdIsLu0CQQDLeXnoQIQBSZQi1qtp\n/07MFIsOhpfh3uJgEzwj3JiHA2vQ5AXXGvqrUJEWbMkU1tZIDJMPQsHaXAUunhxg\nzxPVAkBJShtuJRuubnS/SICarfMq6C84BqS6kumQZ0UvUJx1KNVVyDjLsjy3bFcf\nxUBKDLvIXeX9bIY+9JpICY7a+lLpAkEAk3/X03kROC2yaR7c29XrtR0fQMRozZ/Y\n0nSfIBAFsbnVKnRhl3FDTXT1+B+cFLM4Wrpi0KlABZ63Uvfi8nqqkQJAGWp/gbvG\n1kXTHp7hVfvw9fWlG6yC7Y7ah+16xueGQjs4gPVGoER6n9jLbOt6qkR2Ha1TioJn\nPFkcISJOerTceg==\n-----END PRIVATE KEY-----"
#define PUBLIC_KEY "-----BEGIN PUBLIC KEY-----\nMIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDKvnS8BSWDZ98ZnG6k9czy1a03\n+IwKbz+xpBkM5sUNim6KJwekQOw9MuvgsoqOsJjfUhCg8MPnRTMFqcValyjGssvd\ne1bXZSFF5B92bvHvhbWMe/lDTdns6P3XU2xs0Ostin1Gsue8TtclAs4y9xlKtt+N\nSMqLrVT7Les/9+GiMQIDAQAB\n-----END PUBLIC KEY-----"


class rsa {
public:
    static std::string generatePublicKey(std::string base64EncodedKey);

    static std::string generatePrivateKey(std::string base64EncodedKey);

    static std::string encryptRSA(const std::string &publicKey, const std::string &from);

    static std::string decryptRSA(const std::string &privetaKey, const std::string &from);
};


#endif //JNIDEMO_RSA_H
