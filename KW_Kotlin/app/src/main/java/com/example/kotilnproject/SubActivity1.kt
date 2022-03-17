package com.example.kotilnproject

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.ImageView
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView

class SubActivity1 : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_sub1)

        // 불러오기
        val sub_id = findViewById<TextView>(R.id.sub_id)
        val sub_age = findViewById<TextView>(R.id.sub_age)
        val sub_job = findViewById<TextView>(R.id.sub_job)

        val sub_company = findViewById<TextView>(R.id.sub_company)
        val sub_phone = findViewById<TextView>(R.id.sub_phone)
        val sub_site = findViewById<TextView>(R.id.sub_site)

        val imageView = findViewById<ImageView>(R.id.imageView)

        if(intent.hasExtra("msg1"))
        {
            if(intent.getStringExtra("msg1") == "조남자")
            {
                sub_id.text = intent.getStringExtra("msg1")
                imageView.setImageResource(R.drawable.man)
                sub_company.text = "kwangwon university"
                sub_phone.text = "01074550463"
                sub_site.text = "https://github.com/joehyeonmin"
            }
            if(intent.getStringExtra("msg1") == "조여자")
            {
                sub_id.text = intent.getStringExtra("msg1")
                imageView.setImageResource(R.drawable.woman)
                sub_company.text = "MCN"
                sub_phone.text = "01012345678"
                sub_site.text = "https://github.com/joehyeonmin"
            }
            if(intent.getStringExtra("msg1") == "조삼촌")
            {
                sub_id.text = intent.getStringExtra("msg1")
                imageView.setImageResource(R.drawable.uncle)
                sub_company.text = "Seoul National University"
                sub_phone.text = "01098765432"
                sub_site.text = "https://github.com/joehyeonmin"
            }
            if(intent.getStringExtra("msg1") == "조할아버지")
            {
                sub_id.text = intent.getStringExtra("msg1")
                imageView.setImageResource(R.drawable.grandfather)
                sub_company.text = "Seoul National University"
                sub_phone.text = "01001470258"
                sub_site.text = "https://github.com/joehyeonmin"
            }
        }

        if(intent.hasExtra("msg2"))
        {
            sub_age.text = intent.getIntExtra("msg2",0).toString()
            //sub_age.text = intent.getStringExtra("msg2")
        }

        if(intent.hasExtra("msg3"))
        {
            sub_job.text = intent.getStringExtra("msg3")
        }

    }
}