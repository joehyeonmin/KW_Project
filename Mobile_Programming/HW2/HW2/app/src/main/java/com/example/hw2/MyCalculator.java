package com.example.hw2;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import org.w3c.dom.Text;

public class MyCalculator extends AppCompatActivity {

    private Button btn_move;

    private TextView text;

    private TextView ptResult;
    private Button btn[] = new Button[16];

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_my_calculator);

        text = findViewById(R.id.caltext);

        init();
        initListener();

        Intent intent = getIntent();

        String get_text = intent.getStringExtra("TEXT" );

        ptResult.setText(Eval.cal(get_text));


        btn_move = findViewById(R.id.btn_move);
        btn_move.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v){
                Intent intent = new Intent(MyCalculator.this, MyWebBrowser.class);
                startActivity(intent); //액티비티 이동
            }

        });
    }

    private void initListener() {
        for (int i=0; i<14; i++){
            btn[i].setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    Button btn = (Button)v;
                    ptResult.append(btn.getText().toString());
                }
            });
        }

        btn[14].setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String result = ptResult.getText().toString();
                ptResult.setText(Eval.cal(result));

            }
        });
    }

    private void init() {
        btn[0] = findViewById(R.id.button0);
        btn[1] = findViewById(R.id.button1);
        btn[2] = findViewById(R.id.button2);
        btn[3] = findViewById(R.id.button3);
        btn[4] = findViewById(R.id.button4);
        btn[5] = findViewById(R.id.button5);
        btn[6] = findViewById(R.id.button6);
        btn[7] = findViewById(R.id.button7);
        btn[8] = findViewById(R.id.button8);
        btn[9] = findViewById(R.id.button9);
        btn[10] = findViewById(R.id.btn_add);
        btn[11] = findViewById(R.id.btn_sub);
        btn[12] = findViewById(R.id.btn_mul);
        btn[13] = findViewById(R.id.btn_div);
        btn[14] = findViewById(R.id.btn_result);
        ptResult = findViewById(R.id.caltext);
    }
}