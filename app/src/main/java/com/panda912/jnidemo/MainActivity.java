package com.panda912.jnidemo;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.TextView;

import com.panda912.jnidemo.blur.JavaBlurActivity;
import com.panda912.jnidemo.blur.NativeBlurActivity;
import com.panda912.jnidemo.blur.StackOverflowBlurActivity;
import com.panda912.jnidemo.crypto.CryptoActivity;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = findViewById(R.id.sample_text);

//        JniUtils.nativeCallJavaMethod();

//        Log.e("MainActivity", "" + StringUtils.similarDegree("aaaaaaaq", "aaaaaaaq"));

//        try {
//            tv.setText(JniUtils.stringFromJNI());
//        } catch (JniException e) {
//            e.printStackTrace();
//        }

    }


    public void blurClick(View view) {
        startActivity(new Intent(this, NativeBlurActivity.class));
    }

    public void javaBlur(View view) {
        startActivity(new Intent(this, JavaBlurActivity.class));
    }

    public void blurStackOverflowClick(View view) {
        startActivity(new Intent(this, StackOverflowBlurActivity.class));
    }

    public void encryptRSA(View view) {
        startActivity(new Intent(this, CryptoActivity.class));
    }

}
