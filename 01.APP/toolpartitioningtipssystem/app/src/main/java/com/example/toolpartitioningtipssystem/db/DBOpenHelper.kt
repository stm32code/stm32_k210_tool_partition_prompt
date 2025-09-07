package com.example.toolpartitioningtipssystem.db

import android.content.Context
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteOpenHelper

class DBOpenHelper(context: Context) : SQLiteOpenHelper(context, DB_NAME, null, DB_VERSION) {
    companion object {
        const val DB_NAME = "my.db"
        const val DB_VERSION = 1
    }

    // 创建数据库时触发
    override fun onCreate(p0: SQLiteDatabase?) {
        var sql = "create table `history` (" +
                "`hid` INTEGER primary key autoincrement," +
                "`type` VARCHAR(255)," + //类型
                "`weight` VARCHAR(255)," + //重量
                "`createDateTime` VARCHAR(255))"
        p0?.execSQL(sql) //执行sql语句，
    }

    // 更新数据库时触发
    override fun onUpgrade(p0: SQLiteDatabase?, p1: Int, p2: Int) {

    }
}