package com.example.mymemo;

import androidx.appcompat.app.AppCompatActivity;

import android.content.ComponentName;
import android.content.Intent;
import android.os.Bundle;
import android.view.ActionMode;
import android.view.Menu;
import android.view.MenuItem;
import android.view.Window;
import android.widget.EditText;

public class MyMemo extends AppCompatActivity {

    private EditText editText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        editText = findViewById(R.id.editText);

        editText.setCustomSelectionActionModeCallback(new ActionMode.Callback() {
            @Override
            public boolean onCreateActionMode(ActionMode actionMode, Menu menu) {
                return true;
            }

            @Override
            public boolean onPrepareActionMode(ActionMode actionMode, Menu menu) {
                return false;
            }

            @Override
            public boolean onActionItemClicked(ActionMode actionMode, MenuItem menuItem) {
                int start = editText.getSelectionStart();
                int end = editText.getSelectionEnd(); // 선택된 영역의 시작~끝을 가져온다.

                String str = editText.getText().toString();
                str.substring(start,end); //Substring 기능을 통해 해당 문자열을 자른다.

                switch(menuItem.getItemId()){
                    case android.R.id.shareText : // 해당 Icon이 선택되었을 때 기능실행
                        // Share 버튼을 눌렀을때 동작을 작성
                        Intent intent = new Intent();

                        intent.setAction( Intent.ACTION_MAIN );

//                        String sharedText = intent.getStringExtra(Intent.EXTRA_TEXT);
                        String sharedText = editText.getText().toString().substring(editText.getSelectionStart(), editText.getSelectionEnd());
                        if (sharedText != null)
                        {
                            intent.putExtra("TEXT", sharedText );
//                           intent.setType("text/plain");

                            startActivity(intent);
                        }

                }
                   return true;
            }

            @Override
            public void onDestroyActionMode(ActionMode actionMode) {

            }
        });
    }
}