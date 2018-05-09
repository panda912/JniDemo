#include <jni.h>
#include <string>
#include <android/log.h>

static const char *TAG = "JNIDemo";
#define LOGI(fmt, args...) __android_log_print(ANDROID_LOG_INFO,  TAG, fmt, ##args)
#define LOGD(fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, TAG, fmt, ##args)
#define LOGW(fmt, args...) __android_log_print(ANDROID_LOG_WARN, TAG, fmt, ##args)
#define LOGE(fmt, args...) __android_log_print(ANDROID_LOG_ERROR, TAG, fmt, ##args)

#define JNI_EXCEPTION "com/panda912/jnidemo/exceptions/JniException"
#define JNI_UTILS_CLASS "com/panda912/jnidemo/JniUtils"

JavaVM *gJvm = NULL;
static jobject gClassLoader;
static jmethodID gFindClassMethod;

JNIEnv *getEnv() {
    JNIEnv *env;
    int status = gJvm->GetEnv((void **) &env, JNI_VERSION_1_6);
    if (status < 0) {
        status = gJvm->AttachCurrentThread(&env, NULL);
        if (status < 0) {
            return NULL;
        }
    }
    return env;
}

// handle multi-thread
jclass findClass(const char *name) {
    return static_cast<jclass>(getEnv()->CallObjectMethod(gClassLoader, gFindClassMethod,
                                                          getEnv()->NewStringUTF(name)));
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_panda912_jnidemo_JniUtils_stringFromJNI(JNIEnv *env, jobject /* this */) {
    std::string hello = "Hello from C++";
    std::string error = "error";
    std::string jni_ok = "jni_ok";

    // 检查异常，如果有异常发生，则清除异常，程序会继续运行不会崩溃
    if (env->ExceptionCheck()) {
        jthrowable exception = env->ExceptionOccurred();
        env->ExceptionClear();

        if (exception != NULL) {
            LOGW("Discarding pending exception (%s) to throw", JNI_EXCEPTION);
            env->DeleteLocalRef(exception);
        }
    }

    // 抛出异常
    jclass exceptionClass = env->FindClass(JNI_EXCEPTION);
//    jclass exceptionClass = findClass(JNI_EXCEPTION);
    if (exceptionClass == NULL) {
        LOGE("Unable to find exception class %s", JNI_EXCEPTION);
        return env->NewStringUTF(error.c_str());
    }

    if (env->ThrowNew(exceptionClass, "from panda") != JNI_OK) {
        LOGE("Failed throwing '%s' '%s'", JNI_EXCEPTION, "panda");
        return env->NewStringUTF(jni_ok.c_str());
    }

    return env->NewStringUTF(hello.c_str());
}

/**
 * https://www.cnblogs.com/xitang/p/4174619.html
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_panda912_jnidemo_JniUtils_nativeCallJavaMethod(JNIEnv *env, jobject obj /* this */) {
    jclass targetClass = env->FindClass(JNI_UTILS_CLASS);
//    jclass targetClass = findClass(JNI_UTILS_CLASS);
    if(targetClass == NULL) {
        LOGE("Unable to find class %s", JNI_UTILS_CLASS);
        return;
    }

    jmethodID method = env->GetStaticMethodID(targetClass, "printLogW", "()V");
//    jmethodID method = env->GetMethodID(targetClass, "printLogW", "()V");
    if(method == NULL) {
        LOGE("Unable to find method %s", "printLogW()");
        return;
    }

    env->CallStaticVoidMethod(targetClass, method);
//    env->CallVoidMethod(obj, method);
}

// https://stackoverflow.com/questions/13263340/findclass-from-any-thread-in-android-jni/16302771#16302771
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *pjvm, void *reserved) {
    gJvm = pjvm; // cache the JavaVM pointer
    JNIEnv *env = getEnv();
    //replace with one of your classes in the line below
    jclass randomClass = env->FindClass(JNI_EXCEPTION);
    jclass classClass = env->GetObjectClass(randomClass);
    jclass classLoaderClass = env->FindClass("java/lang/ClassLoader");
    jmethodID getClassLoaderMethod = env->GetMethodID(classClass, "getClassLoader",
                                                      "()Ljava/lang/ClassLoader;");
    // why temp：https://www.cnblogs.com/beautiful-scenery/p/3589857.html?utm_source=tuicool
    jobject tempClassLoader = env->CallObjectMethod(randomClass, getClassLoaderMethod);
    gClassLoader = env->NewGlobalRef(tempClassLoader);
    gFindClassMethod = env->GetMethodID(classLoaderClass, "findClass",
                                        "(Ljava/lang/String;)Ljava/lang/Class;");

    return JNI_VERSION_1_6;
}