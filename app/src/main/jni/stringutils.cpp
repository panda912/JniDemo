#include <jni.h>
#include <string.h>
#include <stdio.h>
#include <android/log.h>

#define LOG_TAG "stringutils"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int min(int a, int b, int c) {
    if (a <= b && a <= c)
        return a;
    if (b <= a && b <= c)
        return b;
    return c;
}

int calChineseCount(char *str) {
    int count = 0;
    char c;
    int temp = 0;
    while ((c = *str++)) {
        temp++;
        //如果字符高位为1且下一字符高位也是1则有中文字符
        if ((c & 0x80) && (*str & 0x80)) {
            count++;
            LOGE("====》%d", temp);
        }
    }
    LOGE("-->%d", count);
    return (count + 1) / 3;
}



/**
 * 字符串比较(动态规划)
 *
 * @param source 待比较字符串
 * @param target 目标字符串
 *
 * @return 相似度
 */
extern "C"
JNIEXPORT jfloat JNICALL
Java_com_panda912_jnidemo_string_StringUtils_similarDegree(JNIEnv *env, jclass, jstring source,
                                                           jstring target) {
    const char *s = env->GetStringUTFChars(source, JNI_FALSE);
    const char *t = env->GetStringUTFChars(target, JNI_FALSE);
    int sStrLen = env->GetStringLength(source);
    int tStrLen = env->GetStringLength(target);
    // utf-8编码，中文字符占3个字节，+1是为了让字符结尾的'\0'拷贝过来，否则会出现乱码
    int sSize = sStrLen + 1;
    int tSize = tStrLen + 1;
//    int sChineseCount = calChineseCount(const_cast<char *>(s));
//    int tChineseCount = calChineseCount(const_cast<char *>(t));
//    int sSize = sChineseCount * 3 + (sStrLen - sChineseCount) + 1;
//    int tSize = tChineseCount * 3 + (tStrLen - tChineseCount) + 1;

    char sArray[sSize], tArray[tSize];

    memcpy(sArray, s, sizeof(sArray));
    memcpy(tArray, t, sizeof(tArray));

    env->ReleaseStringUTFChars(source, s);
    env->ReleaseStringUTFChars(target, t);

    int d[sSize + 1][tSize + 1];

    for (int i = 0; i <= sSize; i++) {
        d[i][0] = i;
    }
    for (int i = 0; i <= tSize; i++) {
        d[0][i] = i;
    }
    for (int i = 1; i <= sSize; i++) {
        for (int j = 1; j <= tSize; j++) {
            if (sArray[i - 1] == tArray[j - 1]) {
                d[i][j] = d[i - 1][j - 1];
            } else {
                int insert = d[i][j - 1] + 1;
                int del = d[i - 1][j] + 1;
                int update = d[i - 1][j - 1] + 1;
                d[i][j] = min(insert, del, update);
            }
        }
    }

    return 1 - (float) d[sSize][tSize] / max(sSize, tSize);
}