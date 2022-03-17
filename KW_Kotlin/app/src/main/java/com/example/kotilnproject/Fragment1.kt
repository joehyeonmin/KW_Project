package com.example.kotilnproject

import android.net.Uri
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.MediaController
import androidx.fragment.app.Fragment
import com.example.kotilnproject.databinding.Frag1Binding

class Fragment1 : Fragment() {

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View?
    {
        val binding = Frag1Binding.inflate(inflater,container,false)
        binding.webView.loadUrl("https://www.google.com")
        //val uri: Uri = Uri.parse("http://commondatastorage.googleapis.com/gtv-videos-bucket/sample/BigBuckBunny.mp4")

        //binding.vv.setVideoURI(uri)
        //binding.vv.start()
        //binding.vv.setMediaController(MediaController(this))
        return binding.root

        //val view = inflater.inflate(R.layout.frag1, container, false)
        //return view
    }
}