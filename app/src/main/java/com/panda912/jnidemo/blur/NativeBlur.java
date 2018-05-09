package com.panda912.jnidemo.blur;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.annotation.FloatRange;

import com.panda912.jnidemo.App;

import java.util.ArrayList;
import java.util.concurrent.Callable;

/**
 * Created by panda on 2018/5/2 下午3:17.
 */
public class NativeBlur implements IBlur {

    static {
        System.loadLibrary("bitmapblur");
    }

    public static native void blur(Bitmap bitmapOut, int radius, int threadCount, int threadIndex, int round);

    /**
     * @param bitmap
     * @param radius
     */
    @Override
    public Bitmap blur(Bitmap bitmap, float radius) {
        Bitmap bitmapOut = bitmap.copy(Bitmap.Config.ARGB_8888, true);

        int cores = BlurManager.EXECUTOR_THREADS;

        ArrayList<NativeTask> horizontal = new ArrayList<>(cores);
        ArrayList<NativeTask> vertical = new ArrayList<>(cores);
        for (int i = 0; i < cores; i++) {
            horizontal.add(new NativeTask(bitmapOut, (int) radius, cores, i, 1));
            vertical.add(new NativeTask(bitmapOut, (int) radius, cores, i, 2));
        }

        try {
            BlurManager.EXECUTOR.invokeAll(horizontal);
        } catch (InterruptedException e) {
            return bitmapOut;
        }

        try {
            BlurManager.EXECUTOR.invokeAll(vertical);
        } catch (InterruptedException e) {
            return bitmapOut;
        }

        return bitmapOut;
    }

    @Override
    public Bitmap blur(int resId, float radius) {
        return blur(BitmapFactory.decodeResource(App.getInstance().getResources(), resId), radius);
    }

    @Override
    public Bitmap fastBlur(int resId, @FloatRange(from = 25) float radius) {
        int reslut = (int) Math.sqrt(radius);

        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inSampleSize = reslut;
        options.inJustDecodeBounds = false;
        Bitmap bitmap = BitmapFactory.decodeResource(App.getInstance().getResources(), resId, options);

        return blur(bitmap, reslut);
    }

    private static class NativeTask implements Callable<Void> {
        private final Bitmap bitmapOut;
        private final int radius;
        private final int totalCores;
        private final int coreIndex;
        private final int round;

        public NativeTask(Bitmap bitmapOut, int radius, int totalCores, int coreIndex, int round) {
            this.bitmapOut = bitmapOut;
            this.radius = radius;
            this.totalCores = totalCores;
            this.coreIndex = coreIndex;
            this.round = round;
        }

        @Override
        public Void call() throws Exception {
            blur(bitmapOut, radius, totalCores, coreIndex, round);
            return null;
        }
    }

}
