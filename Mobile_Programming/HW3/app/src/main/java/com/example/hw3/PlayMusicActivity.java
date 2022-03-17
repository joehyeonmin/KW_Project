package com.example.hw3;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.NotificationCompat;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.ContentResolver;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.provider.MediaStore;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import java.io.File;
import java.io.FilenameFilter;
import java.io.IOException;
import java.util.ArrayList;

public class PlayMusicActivity extends AppCompatActivity implements View.OnClickListener{
    ArrayList<MusicDto> list;
    MediaPlayer mediaPlayer;
    TextView title;

    ImageView album,previous,play,pause,next;
    ImageView logo;
    TextView time;

    SeekBar seekBar;
    boolean isPlaying = true;
    ContentResolver res;
    ProgressUpdate progressUpdate;

    int position;

    // 알림창
    public static String MAIN_ACTION = "com.whahn.foregroundservice.action.main";
    public static String PLAY_ACTION = "com.whahn.foregroundservice.action.play";
    public static String NEXTPLAY_ACTION = "com.whahn.foregroundservice.action.nextplay";
    public static String STARTFOREGROUND_ACTION = "com.whahn.foregroundservice.action.startforeground";
    public static String STOPFOREGROUND_ACTION = "com.whahn.foregroundservice.action.stopforeground";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_play_music);

        //알림오류해결
        createNotificationChannel();

        // get intent
        Intent intent = getIntent();

        mediaPlayer = new MediaPlayer();
        title = (TextView)findViewById(R.id.title);
        album = (ImageView)findViewById(R.id.album);
        seekBar = (SeekBar)findViewById(R.id.seekbar);
        time = (TextView)findViewById(R.id.time);

        position = intent.getIntExtra("position",0);

        // 가져온 intent 담기기
        list = (ArrayList<MusicDto>)getIntent().getSerializableExtra("playlist");
        res = getContentResolver();

        logo = (ImageButton)findViewById(R.id.logo);

        previous = (ImageButton)findViewById(R.id.pre);
        play = (ImageButton)findViewById(R.id.play);
        pause = (ImageButton)findViewById(R.id.pause);
        next = (ImageButton)findViewById(R.id.next);

        previous.setOnClickListener(this);
        play.setOnClickListener(this);
        pause.setOnClickListener(this);
        next.setOnClickListener(this);

        //MediaPlayer 사용
        playMusic(list.get(position));

        // seekbar 사용
        progressUpdate = new ProgressUpdate();
        progressUpdate.start();

        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {

            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                mediaPlayer.pause();
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                mediaPlayer.seekTo(seekBar.getProgress());
                if(seekBar.getProgress()>0 && play.getVisibility()==View.GONE){
                    mediaPlayer.start();
                }
            }
        });

        //playMusic(list.get(position));

        // 노래재생
        mediaPlayer.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
            @Override
            public void onCompletion(MediaPlayer mp) {
                if(position+1 < list.size()) {
                    position++;
                    playMusic(list.get(position));
                }
            }
        });

    }

    public void playMusic(MusicDto musicDto) {
        try {
            seekBar.setProgress(0);

            // 알림창 설정을 위해 보내기
            // 여긴 뭘해도 안된다...
            // serviceIntent = new Intent(this, ForegroundService.class);
            //serviceIntent.putExtra("position", position);
            //serviceIntent.putExtra("playlist", list);
            //startService(serviceIntent);

            // title 출력
            title.setText(musicDto.title);

            Uri musicURI = Uri.withAppendedPath(MediaStore.Audio.Media.EXTERNAL_CONTENT_URI, ""+musicDto.id);
            mediaPlayer.reset();
            mediaPlayer.setDataSource(this, musicURI);
            mediaPlayer.prepare();
            mediaPlayer.start();

            // seekBar
            seekBar.setMax(mediaPlayer.getDuration());

            time.setText(mediaPlayer.getCurrentPosition() + " / " + mediaPlayer.getDuration()/1000/60 + " : " + (mediaPlayer.getDuration()/1000 - (mediaPlayer.getDuration()/1000/60) * 60 ));

            //
            if(mediaPlayer.isPlaying()){
                play.setVisibility(View.GONE);
                pause.setVisibility(View.VISIBLE);
                logo.setImageResource(R.drawable.play);
            }else{
                play.setVisibility(View.VISIBLE);
                pause.setVisibility(View.GONE);
                logo.setImageResource(R.drawable.pause);
            }

            // 앨범 이미지 넣기
            // 어떻게 해야할지 모르겠다
            // 구글링...
            Bitmap bitmap = BitmapFactory.decodeFile(getCoverArtPath(Long.parseLong(musicDto.albumId),getApplication()));
            album.setImageBitmap(bitmap);

            // 이걸로 해보자
            /*Notification notification = new NotificationCompat.Builder(PlayMusicActivity.this, "셑이이잉")
                    // Show controls on lock screen even when user hides sensitive content.
                    .setVisibility(NotificationCompat.VISIBILITY_PUBLIC)
                    .setSmallIcon(R.drawable.play)
                    // Add media control buttons that invoke intents in your media service
                    .addAction(R.drawable.previous, "Previous", null) // #0
                    .addAction(R.drawable.pause, "Pause", null)  // #1
                    .addAction(R.drawable.next, "Next", null)     // #2
                    // Apply the media style template
                    .setContentTitle("Wonderful music")
                    .setContentText("My Awesome Band")
                    .setLargeIcon(bitmap)
                    .build();*/

            // 이걸로는 될까
            // 보내기
            // 가능
            Intent startIntent = new Intent(PlayMusicActivity.this, ForegroundService.class);
            startIntent.setAction(STARTFOREGROUND_ACTION);
            startService(startIntent);

        }
        catch (Exception e) {
            Log.e("SimplePlayer", e.getMessage());
        }
    }

    //앨범이 저장되어 있는 경로를 리턴한다

    // 구글링 참조
    private static String getCoverArtPath(long albumId, Context context) {
        Cursor albumCursor = context.getContentResolver().query(MediaStore.Audio.Albums.EXTERNAL_CONTENT_URI,
                new String[]{MediaStore.Audio.Albums.ALBUM_ART},
                MediaStore.Audio.Albums._ID + " = ?",
                new String[]{Long.toString(albumId)},
                null
        );
        boolean queryResult = albumCursor.moveToFirst();
        String result = null;
        if (queryResult) {
            result = albumCursor.getString(0);
        }
        albumCursor.close();
        return result;
    }

    // 버튼 구현
    // pre와 next는 구현x
    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.play:
                pause.setVisibility(View.VISIBLE);
                play.setVisibility(View.GONE);

                // change logo
                // 반대로
                logo.setImageResource(R.drawable.play);

                mediaPlayer.seekTo(mediaPlayer.getCurrentPosition());
                mediaPlayer.start();

                break;
            case R.id.pause:
                pause.setVisibility(View.GONE);
                play.setVisibility(View.VISIBLE);

                // change logo
                // 반대로
                logo.setImageResource(R.drawable.pause);

                mediaPlayer.pause();
                break;
            case R.id.pre:
                break;
            case R.id.next:

                break;
            case R.id.logo:

                break;

        }
    }

    // seekbar 구현을 위한 클래스스
   class ProgressUpdate extends Thread{
        @Override
        public void run() {
            while(isPlaying){
                try {
                    Thread.sleep(500);
                    if(mediaPlayer!=null){
                        seekBar.setProgress(mediaPlayer.getCurrentPosition());
                        time.setText(mediaPlayer.getCurrentPosition()/1000/60 + " : " + (mediaPlayer.getCurrentPosition()/1000 - (mediaPlayer.getCurrentPosition()/1000/60) * 60 ) +
                                " / " +
                                mediaPlayer.getDuration()/1000/60 + " : " + (mediaPlayer.getDuration()/1000 - (mediaPlayer.getDuration()/1000/60) * 60 ));
                    }
                } catch (Exception e) {
                    Log.e("ProgressUpdate",e.getMessage());
                }

            }
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        isPlaying = false;
        if(mediaPlayer!=null){
            mediaPlayer.release();
            mediaPlayer = null;
        }
    }

    // 채널 만들기
    // 메뉴얼보고 작성
    public void createNotificationChannel()
    {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            CharSequence name = getString(R.string.channel_name);
            String description = getString(R.string.channel_description);
            int importance = NotificationManager.IMPORTANCE_DEFAULT;

            NotificationChannel channel = new NotificationChannel("CHANNEL_ID", name, importance);
            channel.setDescription(description);
            // Register the channel with the system; you can't change the importance
            // or other notification behaviors after this
            NotificationManager notificationManager = getSystemService(NotificationManager.class);
            notificationManager.createNotificationChannel(channel);
        }



    }


}