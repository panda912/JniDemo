package com.panda912.jnidemo.blur;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.ImageView;

import com.panda912.jnidemo.R;

public class StackOverflowBlurActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_blur_stack_overflow);

        ImageView iv = findViewById(R.id.iv);

        long curTime2 = System.currentTimeMillis();
        Bitmap bitmapIn = BitmapFactory.decodeResource(getResources(), R.drawable.bg_tiny);
        Bitmap bitmapOut = bitmapIn.copy(Bitmap.Config.ARGB_8888, true);
        StackoverflowBlur.fastBlur(bitmapIn, bitmapOut, 25);
        Log.e("MainActivity", String.valueOf(System.currentTimeMillis() - curTime2));
        iv.setImageBitmap(bitmapOut);
    }
}
