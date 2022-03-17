package com.example.hw1;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;

public class RelativeLayout extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_relative_layout);
    }

    @Override
    public boolean onTouchEvent(MotionEvent ev) {

        Log.d("hw1", "onTouchEvent() >> " + ev.getAction());

        if (ev.getAction() == MotionEvent.ACTION_DOWN) {
            Intent intent = new Intent(this, TableLayout.class);
            startActivity(intent);
        }
        return super.onTouchEvent(ev);
    }
}
