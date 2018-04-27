package com.panda912.jnidemo;

import android.util.Log;

import com.panda912.jnidemo.exceptions.JniException;

/**
 * Created by panda on 2018/4/27 下午2:04.
 */
public class JniUtils {
    private static final String TAG = "JniUtils";

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public static native String stringFromJNI() throws JniException;

    public static native void nativeCallJavaMethod();

    public static void printLogW() {
        Log.w(TAG, "哈哈哈哈哈哈");
    }
}
