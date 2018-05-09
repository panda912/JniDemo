package com.panda912.jnidemo.string;

/**
 * Created by panda on 2018/5/4 下午5:12.
 */
public class StringUtils {

    static {
        try {
            System.loadLibrary("stringutils");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static native float similarDegree(String source, String target);

    /**
     * byte数组 转 16进制字符串
     *
     * @param bytes byte数组
     * @param size  byte数组 有效长度
     *
     * @return 16进制字符串
     */
    public static String bytesToHexString(byte[] bytes, int size) {
        StringBuffer sb = new StringBuffer();
        for (int i = 0; i < size; i++) {
            String hex = Integer.toHexString(bytes[i] & 0xFF);
            if (hex.length() == 1) {
                hex = '0' + hex;
            }
            sb.append(hex.toUpperCase()).append(" ");
        }

        return sb.toString();
    }


    /**
     * 字符串比较(动态规划)
     *
     * @param source 待比较字符串
     * @param target 目标字符串
     *
     * @return
     */
    public static int compare(String source, String target) {
        char[] s = source.toCharArray();
        char[] t = target.toCharArray();
        int slen = source.length();
        int tlen = target.length();
        int d[][] = new int[slen + 1][tlen + 1];
        for (int i = 0; i <= slen; i++) {
            d[i][0] = i;
        }
        for (int i = 0; i <= tlen; i++) {
            d[0][i] = i;
        }
        for (int i = 1; i <= slen; i++) {
            for (int j = 1; j <= tlen; j++) {
                if (s[i - 1] == t[j - 1]) {
                    d[i][j] = d[i - 1][j - 1];
                } else {
                    int insert = d[i][j - 1] + 1;
                    int del = d[i - 1][j] + 1;
                    int update = d[i - 1][j - 1] + 1;
                    d[i][j] = Math.min(insert, del) > Math.min(del, update) ? Math.min(del, update) : Math.min(insert, del);
                }
            }
        }
        return d[slen][tlen];
    }

    /**
     * 获取两字符串的相似度
     *
     * @param str
     * @param target
     *
     * @return
     */
    public static float getSimilarityRatio(String str, String target) {
        return 1 - (float) compare(str, target) / Math.max(str.length(), target.length());
    }
}
