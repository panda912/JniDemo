package com.panda912.jnidemo.crypto;

/**
 * Created by panda on 2018/5/7 下午6:29.
 */
public class Crypto {

    public static final String PUB_KEY = "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDKvnS8BSWDZ98ZnG6k9czy1a03+IwKbz+xpBkM5sUNim6KJwekQOw9MuvgsoqOsJjfUhCg8MPnRTMFqcValyjGssvde1bXZSFF5B92bvHvhbWMe/lDTdns6P3XU2xs0Ostin1Gsue8TtclAs4y9xlKtt+NSMqLrVT7Les/9+GiMQIDAQAB";

    public static final String PRI_KEY = "-----BEGIN PRIVATE KEY-----\n" +
            "MIICdgIBADANBgkqhkiG9w0BAQEFAASCAmAwggJcAgEAAoGBAMq+dLwFJYNn3xmc\n" +
            "bqT1zPLVrTf4jApvP7GkGQzmxQ2KboonB6RA7D0y6+Cyio6wmN9SEKDww+dFMwWp\n" +
            "xVqXKMayy917VtdlIUXkH3Zu8e+FtYx7+UNN2ezo/ddTbGzQ6y2KfUay57xO1yUC\n" +
            "zjL3GUq2341IyoutVPst6z/34aIxAgMBAAECgYANpIdCZ65Ai2rN1GL1oryp0osX\n" +
            "axgxU48bqwksfxLfeGM71KiE+wFqlNSeiCUeuO9wh5sq2Ui1dUibpvLqx6UsqtwL\n" +
            "zAZ02WLxl+jFtjs+H97PHXzfEwEXwzcpdFiJjBMi1ARvcdGWGXFlpjVEo03UukwD\n" +
            "Is6c5AWGK2OK2ScPYQJBAP8Us63kPGlPr0R0s2SO/lpfd9UCfA9wfVbwmr/9jLxX\n" +
            "C0Pqje8g7vlaR8jqteVd9/duPFqiKRruJw3yVdIsLu0CQQDLeXnoQIQBSZQi1qtp\n" +
            "/07MFIsOhpfh3uJgEzwj3JiHA2vQ5AXXGvqrUJEWbMkU1tZIDJMPQsHaXAUunhxg\n" +
            "zxPVAkBJShtuJRuubnS/SICarfMq6C84BqS6kumQZ0UvUJx1KNVVyDjLsjy3bFcf\n" +
            "xUBKDLvIXeX9bIY+9JpICY7a+lLpAkEAk3/X03kROC2yaR7c29XrtR0fQMRozZ/Y\n" +
            "0nSfIBAFsbnVKnRhl3FDTXT1+B+cFLM4Wrpi0KlABZ63Uvfi8nqqkQJAGWp/gbvG\n" +
            "1kXTHp7hVfvw9fWlG6yC7Y7ah+16xueGQjs4gPVGoER6n9jLbOt6qkR2Ha1TioJn\n" +
            "PFkcISJOerTceg==\n" +
            "-----END PRIVATE KEY-----\n";

    static {
        System.loadLibrary("mycrypto");
    }

    public class Cipher {
        String cipherText;
        int cipherTextLength;
    }

    public native static String encryptRSA(String base64PublicKey, String content);

    public native static String decryptRSA(String base64PrivateKey, String content);

    public native static String base64Encode(String content);

    public native static String base64Decode(String content);

    public native static Cipher encryptAES(String plainText, String key, String iv);

    public native static String decryptAES(Cipher cipher, String key, String iv);
}
