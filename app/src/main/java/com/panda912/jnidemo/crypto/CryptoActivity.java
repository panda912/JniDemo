package com.panda912.jnidemo.crypto;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.panda912.jnidemo.R;

public class CryptoActivity extends AppCompatActivity {
    private static final String TAG = "CryptoActivity";

    private EditText et;
    private TextView tv1;
    private TextView tv2;
    private TextView tv_count;
    private Button btn1;
    private Button btn2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_crypto);

        et = findViewById(R.id.et);
        tv1 = findViewById(R.id.tv1);
        tv2 = findViewById(R.id.tv2);
        tv_count = findViewById(R.id.tv_count);
        btn1 = findViewById(R.id.btn1);
        btn2 = findViewById(R.id.btn2);
    }

    public void onEncrypt(View view) {
        String origin = et.getText().toString();
        String s = Crypto.encrypt(Crypto.PUB_KEY, origin);
        tv1.setText(s);
        tv_count.setText(s.length() + "");
    }

    public void onDecrypt(View view) {
        String origin = tv1.getText().toString();
        String ss = Crypto.decrypt(Crypto.PRI_KEY, origin);
        tv2.setText(ss);
    }
}
