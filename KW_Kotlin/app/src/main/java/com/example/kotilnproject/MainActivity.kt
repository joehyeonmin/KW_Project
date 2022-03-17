package com.example.kotilnproject

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.webkit.WebView
import android.widget.Button
import android.widget.EditText
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.kotilnproject.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        //setContentView(R.layout.activity_main)


        val activityMainBinding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(activityMainBinding.root)

        val profileList = arrayListOf(
            Profiles(R.drawable.man, "조남자", 26, "Student"),
            Profiles(R.drawable.woman, "조여자", 20, "Youtuber"),
            Profiles(R.drawable.uncle, "조삼촌", 30, "Teacher"),
            Profiles(R.drawable.grandfather, "조할아버지", 60, "Principal")
        )

        val rv_profile = findViewById<RecyclerView>(R.id.rv_profile)
        rv_profile.layoutManager = LinearLayoutManager(this, LinearLayoutManager.VERTICAL, false)
        rv_profile.setHasFixedSize(true)
        rv_profile.adapter = ProfileAdapter(profileList)

        val btn_fragment1 = findViewById<Button>(R.id.btn_fragment1)
        val btn_fragment2 = findViewById<Button>(R.id.btn_fragment2)
        val btn_fragment3 = findViewById<Button>(R.id.btn_fragment3)

        val mwebview = findViewById<WebView>(R.id.webView)
        btn_fragment1.setOnClickListener{
            setFrag(0)
        }

        btn_fragment2.setOnClickListener{
            setFrag(1)
        }

        btn_fragment3.setOnClickListener{
            setFrag(2)
        }

        loadData()
   }

    private fun loadData(){
        val et_hello = findViewById<EditText>(R.id.et_hello)
        val pref = getSharedPreferences("pref",0)
        et_hello.setText(pref.getString("name", "")) // key값, 키 값에 데이터가 없으면 대체값

    }

    private fun saveData(){
        val et_hello = findViewById<EditText>(R.id.et_hello)
        val pref = getSharedPreferences("pref",0)
        val edit = pref.edit()
        edit.putString("name", et_hello.text.toString())
        edit.apply()

    }

    override fun onDestroy() {
        super.onDestroy()

        saveData()
    }

    fun setFrag(fragNum : Int) {
        val ft = supportFragmentManager.beginTransaction()
        when(fragNum)
        {
            0 -> {
                ft.replace(R.id.main_frame, Fragment1()).commit()
            }

            1 -> {
                ft.replace(R.id.main_frame, Fragment2()).commit()
            }

            2 -> {
                ft.replace(R.id.main_frame, Fragment3()).commit()
            }

        }
    }
}