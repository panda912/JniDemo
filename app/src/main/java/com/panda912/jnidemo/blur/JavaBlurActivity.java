package com.panda912.jnidemo.blur;

import android.graphics.Bitmap;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.ImageView;

import com.panda912.jnidemo.R;

public class JavaBlurActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_blur);

        ImageView iv = findViewById(R.id.iv);

        long curTime = System.currentTimeMillis();
        JavaBlur blur = new JavaBlur();
        Bitmap bitmapOut = blur.fastBlur(R.drawable.bg_tiny, 25);
        Log.e("BlurActivity", String.valueOf(System.currentTimeMillis() - curTime));
        iv.setImageBitmap(bitmapOut);
    }
}
