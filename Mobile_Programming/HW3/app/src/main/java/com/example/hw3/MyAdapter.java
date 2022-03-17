package com.example.hw3;


import android.app.Activity;
import android.content.ContentResolver;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.MediaMetadataRetriever;
import android.net.Uri;
import android.os.ParcelFileDescriptor;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;


public class MyAdapter extends BaseAdapter
{
    Context             mContext        = null;
    ArrayList<MusicDto>  mData           = null;
    LayoutInflater      mLayoutInflater = null;
    //Activity activity;

    public MyAdapter( Context context, ArrayList<MusicDto> data )
    {
        mContext        = context;
        mData           = data;
        mLayoutInflater = LayoutInflater.from(mContext);
        //this.activity = activity;
    }

    public int getCount()
    {
        return mData.size();
    }

    public long getItemId( int position )
    {
        return position;
    }

    public MusicDto getItem( int position )
    {
        return mData.get( position );
    }

    @Override
    public View getView( int position, View convertView, ViewGroup parent )
    {
        View itemLayout = mLayoutInflater.inflate( R.layout.list_view_item_layout, null);

        ImageView imageView = (ImageView) itemLayout.findViewById( R.id.album );
        TextView music_title = (TextView) itemLayout.findViewById( R.id.title );

        //image를 어떻게 저장?
        Bitmap albumImage = getAlbumImage(mContext, Integer.parseInt((mData.get(position)).albumId), 170);
        imageView.setImageBitmap(albumImage);


        //노래제목 저장장
       music_title.setText( mData.get( position ).title );

        return itemLayout;

    }

    // 비트맵 이미지 넣는 함수
    // 구글링 참조...
    private static final BitmapFactory.Options options = new BitmapFactory.Options();

    private static Bitmap getAlbumImage(Context context, int album_id, int MAX_IMAGE_SIZE) {
        // NOTE: There is in fact a 1 pixel frame in the ImageView used to
        // display this drawable. Take it into account now, so we don't have to
        // scale later.
        ContentResolver res = context.getContentResolver();
        Uri uri = Uri.parse("content://media/external/audio/albumart/" + album_id);
        if (uri != null) {
            ParcelFileDescriptor fd = null;
            try {
                fd = res.openFileDescriptor(uri, "r");


                // Compute the closest power-of-two scale factor
                // and pass that to sBitmapOptionsCache.inSampleSize, which will
                // result in faster decoding and better quality

                //크기를 얻어오기 위한옵션 ,
                //inJustDecodeBounds값이 true로 설정되면 decoder가 bitmap object에 대해 메모리를 할당하지 않고, 따라서 bitmap을 반환하지도 않는다.
                // 다만 options fields는 값이 채워지기 때문에 Load 하려는 이미지의 크기를 포함한 정보들을 얻어올 수 있다.
                options.inJustDecodeBounds = true;
                BitmapFactory.decodeFileDescriptor(
                        fd.getFileDescriptor(), null, options);
                int scale = 0;
                if (options.outHeight > MAX_IMAGE_SIZE || options.outWidth > MAX_IMAGE_SIZE) {
                    scale = (int) Math.pow(2, (int) Math.round(Math.log(MAX_IMAGE_SIZE / (double) Math.max(options.outHeight, options.outWidth)) / Math.log(0.5)));
                }
                options.inJustDecodeBounds = false;
                options.inSampleSize = scale;



                Bitmap b = BitmapFactory.decodeFileDescriptor(
                        fd.getFileDescriptor(), null, options);

                if (b != null) {
                    // finally rescale to exactly the size we need
                    if (options.outWidth != MAX_IMAGE_SIZE || options.outHeight != MAX_IMAGE_SIZE) {
                        Bitmap tmp = Bitmap.createScaledBitmap(b, MAX_IMAGE_SIZE, MAX_IMAGE_SIZE, true);
                        b.recycle();
                        b = tmp;
                    }
                }

                return b;
            } catch (FileNotFoundException e) {
            } finally {
                try {
                    if (fd != null)
                        fd.close();
                } catch (IOException e) {
                }
            }
        }
        return null;
    }

}