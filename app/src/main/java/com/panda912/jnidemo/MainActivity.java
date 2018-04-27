package com.panda912.jnidemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.panda912.jnidemo.exceptions.JniException;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = findViewById(R.id.sample_text);

        JniUtils.nativeCallJavaMethod();

        try {
            tv.setText(JniUtils.stringFromJNI());
        } catch (JniException e) {
            e.printStackTrace();
        }
    }
}
