package com.example.libcurl4java;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import static android.Manifest.permission.READ_EXTERNAL_STORAGE;
import static android.Manifest.permission.WRITE_EXTERNAL_STORAGE;

public class MainActivity extends AppCompatActivity {
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    public native String testHttpFromCurl();

    public native String testFtpFromCurl();

    public native String testCallJava();

    public native String testThread();

    private TextView tv;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        tv = findViewById(R.id.sample_text);
        ActivityCompat.requestPermissions(this, new String[]{READ_EXTERNAL_STORAGE, WRITE_EXTERNAL_STORAGE}, 1);
    }

    public void onClickTestHttpFromCurl(View view) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                final String text = testHttpFromCurl();
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        tv.setText(text);
                    }
                });
            }
        }).start();
    }

    public void onClickTestFtpFromCurl(View view) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                final String text = testFtpFromCurl();
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        tv.setText(text);
                    }
                });
            }
        }).start();
    }

    public void onClickTestJNI(View view) {
        tv.setText(testCallJava());
        tv.append("\n" + testThread());
        tv.append("\n currentThreadIdFromJava = " + Thread.currentThread().getId());
    }
}
