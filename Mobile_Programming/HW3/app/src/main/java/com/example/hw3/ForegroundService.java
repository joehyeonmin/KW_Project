package com.example.hw3;

import android.app.Notification;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.IBinder;
import android.util.Log;

import androidx.annotation.Nullable;
import androidx.core.app.NotificationCompat;

import java.util.ArrayList;

public class ForegroundService extends Service
{
    public static String MAIN_ACTION = "com.whahn.foregroundservice.action.main";
    public static String PLAY_ACTION = "com.whahn.foregroundservice.action.play";
    public static String NEXTPLAY_ACTION = "com.whahn.foregroundservice.action.nextplay";
    public static String STARTFOREGROUND_ACTION = "com.whahn.foregroundservice.action.startforeground";
    public static String STOPFOREGROUND_ACTION = "com.whahn.foregroundservice.action.stopforeground";

    int position;
    ArrayList<MusicDto> list;

    public int onStartCommand( Intent intent, int flags, int startId )
    {
        super.onStartCommand( intent, flags, startId );

        if (intent.getAction().equals(STARTFOREGROUND_ACTION))
        {
            Log.i("tag", "Received Start Foreground Intent ");

            Intent intent_activity = new Intent(this, PlayMusicActivity.class);
            intent_activity.putExtra("position", position);
            intent_activity.putExtra("playlist", list);

            Intent notificationIntent = new Intent(this, PlayMusicActivity.class);
            notificationIntent.setAction(MAIN_ACTION);
            notificationIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);

            PendingIntent pendingIntent = PendingIntent.getActivity(this, 0, notificationIntent, 0);


            Intent playIntent = new Intent(this, ForegroundService.class);
            playIntent.setAction(PLAY_ACTION);
            PendingIntent playPendingIntent = PendingIntent.getService(this, 0, playIntent, 0);

            //Intent nplayIntent = new Intent(this, ForegroundService.class);
            //playIntent.setAction(NEXTPLAY_ACTION);
            //PendingIntent nplayPendingIntent = PendingIntent.getService(this, 0, nplayIntent, 0);

            Bitmap icon = BitmapFactory.decodeResource(getResources(), R.drawable.play);

            NotificationCompat.Builder notiBuilder = new NotificationCompat.Builder(this, "CHANNEL_ID");
            notiBuilder.setContentTitle("My Music Player");
            notiBuilder.setTicker("My Music Player");
            notiBuilder.setContentText("My Music");
            notiBuilder.setSmallIcon(R.drawable.ic_launcher_foreground);

            notiBuilder.setLargeIcon(Bitmap.createScaledBitmap(icon, 128, 128, false));
            notiBuilder.setContentIntent(pendingIntent);
            notiBuilder.setOngoing(true);
            notiBuilder.addAction(android.R.drawable.ic_media_play, "Play", playPendingIntent);
            notiBuilder.addAction(android.R.drawable.ic_media_play, "Next", null);
            startForeground(1234, notiBuilder.build());

        }
        else if (intent.getAction().equals(PLAY_ACTION))
        {
            Log.i("tag", "Clicked Play");
            // Implement code for playing the current music
            //
        }

        else if (intent.getAction().equals(NEXTPLAY_ACTION)) {
            Log.i("tag", "Clicked Play");
            // Implement code for playing the next music
        }
        else if (intent.getAction().equals(STOPFOREGROUND_ACTION))
        {
            Log.i("tage", "Received Stop Foreground Intent");
            stopForeground(true);
            stopSelf();
        }
        return START_STICKY;
    }

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

}
