package com.blogspot.rajbtc.robotcontrol;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.webkit.WebView;

public class MainActivity extends AppCompatActivity {

    WebView webView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        webView=findViewById(R.id.webView);

    }

    public void upClick(View view) {
        webView.loadUrl("HTTP://192.168.4.1/11");
        Log.e("==========","HI");
    }

    public void downClick(View view) {
        webView.loadUrl("HTTP://192.168.4.1/12");
    }

    public void leftClick(View view) {
        webView.loadUrl("HTTP://192.168.4.1/13");
    }

    public void offClick(View view) {
        webView.loadUrl("HTTP://192.168.4.1/15");
    }

    public void rightClick(View view) {
        webView.loadUrl("HTTP://192.168.4.1/14");
    }
}