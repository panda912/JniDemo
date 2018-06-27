package com.panda912.jnidemo.crypto;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Base64;
import android.util.Log;
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

    Crypto.Cipher reuslt;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_crypto);

        et = findViewById(R.id.et);
        tv1 = findViewById(R.id.tv1);
        tv2 = findViewById(R.id.tv2);
        tv_count = findViewById(R.id.tv_count);
    }

    public void onEncrypt(View view) {
        String origin = et.getText().toString();
        String s = Crypto.encryptRSA(Crypto.PUB_KEY, origin);
        tv1.setText(s);
        tv_count.setText(s.length() + "");
    }

    public void onDecrypt(View view) {
        String origin = tv1.getText().toString();
        String ss = Crypto.decryptRSA(Crypto.PRI_KEY, origin);
        tv2.setText(ss);
    }

    public void onBase64EncodeViaOpenssl(View view) {
        String origin = et.getText().toString();
        tv1.setText(Crypto.base64Encode(origin));
    }

    public void onBase64DecodeViaOpenssl(View view) {
        String origin = tv1.getText().toString();
        tv2.setText(Crypto.base64Decode(origin));
    }

    public void onBase64EncodeViaJava(View view) {
        String origin = et.getText().toString();
        byte[] result = Base64.encode(origin.getBytes(), Base64.DEFAULT);
        tv1.setText(new String(result));
    }

    public void onBase64DecodeViaJava(View view) {
        String origin = tv1.getText().toString();
        byte[] result = Base64.decode(origin, Base64.DEFAULT);
        tv2.setText(new String(result));
    }

    public void onEncryptAES(View view) {
        String origin = et.getText().toString();
        reuslt = Crypto.encryptAES(origin, "01234567890123456789012345678901", "5012345678901234");
        tv1.setText(reuslt.cipherText);
    }

    public void onDecryptAES(View view) {
        String origin = tv1.getText().toString();
        Crypto.Cipher cipher = new Crypto().new Cipher();
        cipher.cipherText = origin;
        cipher.cipherTextLength = reuslt.cipherTextLength;

        tv2.setText(Crypto.decryptAES(cipher, "01234567890123456789012345678901", "5012345678901234"));
    }

    public void digest(View view) {
        tv1.setText(Crypto.digest(et.getText().toString(), "sha512"));
    }
}
