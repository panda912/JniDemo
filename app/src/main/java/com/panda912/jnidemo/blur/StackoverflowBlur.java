package com.panda912.jnidemo.blur;

import android.graphics.Bitmap;

/**
 * Created by panda on 2018/5/2 下午6:35.
 * <p>
 * StackoverflowBlur
 */
public class StackoverflowBlur {
    static {
        System.loadLibrary("blur_sof");
    }

    public static native void fastBlur(Bitmap bitmapIn, Bitmap bitmapOut, int radius);
}
