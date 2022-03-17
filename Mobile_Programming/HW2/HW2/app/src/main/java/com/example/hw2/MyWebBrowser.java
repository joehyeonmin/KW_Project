package com.example.hw2;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.graphics.Bitmap;
import android.net.http.SslError;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.view.inputmethod.EditorInfo;
import android.webkit.SslErrorHandler;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MyWebBrowser extends AppCompatActivity {

    private Button btn_move1;
    private Button front;
    private Button back;

    private WebView wView;

    private WebSettings wSetting;

    private EditText urlEt;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_my_web_browser);

        btn_move1 = findViewById(R.id.btn_move1);
        btn_move1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v){
                Intent intent = new Intent(MyWebBrowser.this, MyCalculator.class);
                startActivity(intent); //액티비티 이동
            }

        });

        wView = findViewById(R.id.wView);
        wView.setWebViewClient(new WebViewClient());

        wSetting = wView.getSettings();
        wSetting.setJavaScriptEnabled(true);
        wSetting.setAllowFileAccess(true);
        wSetting.setAllowContentAccess(true);

        Intent intent = getIntent();

        String get_url = intent.getStringExtra("TEXT" );


        wView.loadUrl(get_url);
        //urlEt.setText(get_url);

        //wView.loadUrl("https://naver.com");

        urlEt = findViewById(R.id.urlEt);
        urlEt.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView textView, int actionId, KeyEvent keyEvent) {
                if(actionId == EditorInfo.IME_ACTION_DONE){                  // 키보드의 엔터키를 눌러서
                    wView.loadUrl("https://"+urlEt.getText().toString()); // 입력한 주소 접속
                }
                return false;
            }
        });

        urlEt.setOnKeyListener(new View.OnKeyListener(){
            @Override
            public  boolean onKey(View v, int keyCode, KeyEvent event){
                if(keyCode == KeyEvent.KEYCODE_ENTER)
                {
                    String urlString = urlEt.getText().toString();

                    if(urlString.startsWith("http")!=true)
                        urlString = "http://" + urlString;

                    wView.loadUrl(urlString);
                    return true;
                }
                return false;
            }
        });

        back = findViewById(R.id.back);
        back.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v){
                wView.goBack();

                //String forward_url = "https://" + wView.getUrl();
                //urlEt.setText(forward_url);
                //forward_url = "";
            }
        });

        front = findViewById(R.id.front);
        front.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v){
                wView.goForward();
                //String back_url = "https://"+ wView.getUrl();
                //urlEt.setText(back_url);
                //back_url = "";
            }
        });

        wView.setWebViewClient(new WebViewClient(){
            @Override
            public void onPageFinished(WebView view, String url){
                String current_url =  wView.getUrl();
                urlEt.setText(current_url);
                current_url = "";
            }
        });



    }
}