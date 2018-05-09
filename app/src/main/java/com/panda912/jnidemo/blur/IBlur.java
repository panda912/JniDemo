package com.panda912.jnidemo.blur;

import android.graphics.Bitmap;
import android.support.annotation.DrawableRes;
import android.support.annotation.FloatRange;

/**
 * Created by panda on 2018/5/2 下午6:37.
 */
public interface IBlur {

    Bitmap blur(Bitmap bitmap, float radius);

    Bitmap blur(@DrawableRes int resId, float radius);

    /**
     * @param resId  drawable resource id
     * @param radius blur intensity
     *
     * @return bitmap
     */
    Bitmap fastBlur(@DrawableRes int resId, @FloatRange(from = 25) float radius);
}
