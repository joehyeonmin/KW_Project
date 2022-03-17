package com.example.hw3;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.NotificationCompat;

import android.Manifest;
import android.annotation.SuppressLint;
import android.app.Notification;
import android.app.PendingIntent;
import android.content.ContentResolver;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.media.MediaPlayer;
import android.media.MediaScannerConnection;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.provider.MediaStore;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import java.io.File;
import java.io.FilenameFilter;
import java.lang.Object;
import java.io.IOException;
import java.util.ArrayList;

public class MainActivity extends AppCompatActivity
{
    ListView mListView = null;
    MyAdapter mAdapter = null;
    ArrayList<MusicDto> mData = null;

    public static final int MY_PERMISSIONS_REQUEST_READ_EXTERNAL_STORAGE = 123;

    MediaPlayer mPlayer;
    String mPath;

    MediaScannerConnection mediaScannerConnection = null;
    MediaScannerConnection.MediaScannerConnectionClient mediaScannerConnectionClient = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // mediaplayer에 등록
        // Environment.DIRECTORY_DOWNLOADS
        //

        String getDirectory = Environment.getExternalStorageDirectory() + "/tmp";

        mediaScannerConnectionClient = new MediaScannerConnection.MediaScannerConnectionClient() {
            @Override
            public void onMediaScannerConnected() {
                mediaScannerConnection.scanFile(getDirectory, null );
                System.out.println("미디어 스캔 성공");
            }

            @Override
            public void onScanCompleted(String s, Uri uri) {

            }
        };

        mediaScannerConnection = new MediaScannerConnection(MainActivity.this, mediaScannerConnectionClient);
        mediaScannerConnection.connect();

        //"audio/*"
        //mediaScannerConnection.scanFile(getDirectory, null );

        // 권한허용 부분
        // api 23 이상부터 가능!!
        if (checkSelfPermission(Manifest.permission.READ_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED)
        {
            // Should we show an explanation?
            if (shouldShowRequestPermissionRationale(Manifest.permission.READ_EXTERNAL_STORAGE)) {
                // Explain to the user why we need to read the contacts
            }

            requestPermissions(new String[]{Manifest.permission.READ_EXTERNAL_STORAGE}, MY_PERMISSIONS_REQUEST_READ_EXTERNAL_STORAGE);

            // MY_PERMISSIONS_REQUEST_READ_EXTERNAL_STORAGE is an
            // app-defined int constant that should be quite unique

            return;
        }

        // 어레이리스트에 음악 넣기
        getMusicList();

        mListView = (ListView) findViewById( R.id.list_view );

        // 리스트뷰에 어뎁터 연결 (문제있음 현재)
        mAdapter = new MyAdapter( this, mData );

        mListView.setAdapter( mAdapter );

        // 클릭 시 뮤직액티비티 실행
        mListView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                Intent intent = new Intent(MainActivity.this, PlayMusicActivity.class);

                intent.putExtra("position", position);
                intent.putExtra("playlist", mData);
                startActivity(intent);

            }
        });

    }

    public  void getMusicList(){
        mData = new ArrayList<>();
        //가져오고 싶은 컬럼 명을 나열합니다. 음악의 아이디, 앰블럼 아이디, 제목, 아스티스트 정보를 가져옵니다.
        String[] projection = {MediaStore.Audio.Media._ID,
                MediaStore.Audio.Media.ALBUM_ID,
                MediaStore.Audio.Media.TITLE,
                MediaStore.Audio.Media.ARTIST
        };

        Cursor cursor = getContentResolver().query(MediaStore.Audio.Media.EXTERNAL_CONTENT_URI,
                projection, null, null, null);

        while(cursor.moveToNext()){
            MusicDto musicDto = new MusicDto();
            musicDto.id = cursor.getString(cursor.getColumnIndex(MediaStore.Audio.Media._ID));
            musicDto.albumId = (cursor.getString(cursor.getColumnIndex(MediaStore.Audio.Media.ALBUM_ID)));
            musicDto.title = (cursor.getString(cursor.getColumnIndex(MediaStore.Audio.Media.TITLE)));
            musicDto.artist = (cursor.getString(cursor.getColumnIndex(MediaStore.Audio.Media.ARTIST)));
            mData.add(musicDto);
        }
        cursor.close();
    }
}








