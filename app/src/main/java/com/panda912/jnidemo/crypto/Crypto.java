package com.panda912.jnidemo.crypto;

/**
 * Created by panda on 2018/5/7 下午6:29.
 */
public class Crypto {

    public static final String PUB_KEY = "-----BEGIN PUBLIC KEY-----\n" +
            "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQDKvnS8BSWDZ98ZnG6k9czy1a03\n" +
            "+IwKbz+xpBkM5sUNim6KJwekQOw9MuvgsoqOsJjfUhCg8MPnRTMFqcValyjGssvd\n" +
            "e1bXZSFF5B92bvHvhbWMe/lDTdns6P3XU2xs0Ostin1Gsue8TtclAs4y9xlKtt+N\n" +
            "SMqLrVT7Les/9+GiMQIDAQAB\n" +
            "-----END PUBLIC KEY-----\n";

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

    public static final String PRI_KEY1 = "-----BEGIN RSA PRIVATE KEY-----\n" +
            "MIICXAIBAAKBgQDKvnS8BSWDZ98ZnG6k9czy1a03+IwKbz+xpBkM5sUNim6KJwek\n" +
            "QOw9MuvgsoqOsJjfUhCg8MPnRTMFqcValyjGssvde1bXZSFF5B92bvHvhbWMe/lD\n" +
            "Tdns6P3XU2xs0Ostin1Gsue8TtclAs4y9xlKtt+NSMqLrVT7Les/9+GiMQIDAQAB\n" +
            "AoGADaSHQmeuQItqzdRi9aK8qdKLF2sYMVOPG6sJLH8S33hjO9SohPsBapTUnogl\n" +
            "HrjvcIebKtlItXVIm6by6selLKrcC8wGdNli8ZfoxbY7Ph/ezx183xMBF8M3KXRY\n" +
            "iYwTItQEb3HRlhlxZaY1RKNN1LpMAyLOnOQFhitjitknD2ECQQD/FLOt5DxpT69E\n" +
            "dLNkjv5aX3fVAnwPcH1W8Jq//Yy8VwtD6o3vIO75WkfI6rXlXff3bjxaoika7icN\n" +
            "8lXSLC7tAkEAy3l56ECEAUmUItaraf9OzBSLDoaX4d7iYBM8I9yYhwNr0OQF1xr6\n" +
            "q1CRFmzJFNbWSAyTD0LB2lwFLp4cYM8T1QJASUobbiUbrm50v0iAmq3zKugvOAak\n" +
            "upLpkGdFL1CcdSjVVcg4y7I8t2xXH8VASgy7yF3l/WyGPvSaSAmO2vpS6QJBAJN/\n" +
            "19N5ETgtsmke3NvV67UdH0DEaM2f2NJ0nyAQBbG51Sp0YZdxQ0109fgfnBSzOFq6\n" +
            "YtCpQAWet1L34vJ6qpECQBlqf4G7xtZF0x6e4VX78PX1pRusgu2O2oftesbnhkI7\n" +
            "OID1RqBEep/Yy2zreqpEdh2tU4qCZzxZHCEiTnq03Ho=\n" +
            "-----END RSA PRIVATE KEY-----\n";

    public static final String PRI_KEY2 = "MIICdgIBADANBgkqhkiG9w0BAQEFAASCAmAwggJcAgEAAoGBAMq+dLwFJYNn3xmcbqT1zPLVrTf4jApvP7GkGQzmxQ2KboonB6RA7D0y6+Cyio6wmN9SEKDww+dFMwWpxVqXKMayy917VtdlIUXkH3Zu8e+FtYx7+UNN2ezo/ddTbGzQ6y2KfUay57xO1yUCzjL3GUq2341IyoutVPst6z/34aIxAgMBAAECgYANpIdCZ65Ai2rN1GL1oryp0osXaxgxU48bqwksfxLfeGM71KiE+wFqlNSeiCUeuO9wh5sq2Ui1dUibpvLqx6UsqtwLzAZ02WLxl+jFtjs+H97PHXzfEwEXwzcpdFiJjBMi1ARvcdGWGXFlpjVEo03UukwDIs6c5AWGK2OK2ScPYQJBAP8Us63kPGlPr0R0s2SO/lpfd9UCfA9wfVbwmr/9jLxXC0Pqje8g7vlaR8jqteVd9/duPFqiKRruJw3yVdIsLu0CQQDLeXnoQIQBSZQi1qtp/07MFIsOhpfh3uJgEzwj3JiHA2vQ5AXXGvqrUJEWbMkU1tZIDJMPQsHaXAUunhxgzxPVAkBJShtuJRuubnS/SICarfMq6C84BqS6kumQZ0UvUJx1KNVVyDjLsjy3bFcfxUBKDLvIXeX9bIY+9JpICY7a+lLpAkEAk3/X03kROC2yaR7c29XrtR0fQMRozZ/Y0nSfIBAFsbnVKnRhl3FDTXT1+B+cFLM4Wrpi0KlABZ63Uvfi8nqqkQJAGWp/gbvG1kXTHp7hVfvw9fWlG6yC7Y7ah+16xueGQjs4gPVGoER6n9jLbOt6qkR2Ha1TioJnPFkcISJOerTceg==";

    static {
        System.loadLibrary("mycrypto");
    }

    public native static String encrypt(String base64PublicKey, String content);

    public native static String decrypt(String base64PrivateKey, String content);
}
