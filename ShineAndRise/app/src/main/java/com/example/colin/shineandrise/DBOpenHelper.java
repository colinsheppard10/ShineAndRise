package com.example.colin.shineandrise;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class DBOpenHelper extends SQLiteOpenHelper {

    //Constants for db name and version
    private static final String DATABASE_NAME = "alarms.db";
    private static final int DATABASE_VERSION = 1;

    //Constants for identifying table and columns
    public static final String TABLE_ALARMS = "alarms";
    public static final String ALARM_ID = "_id";
    public static final String ALARM_TEXT = "alarmText";
    public static final String ALARM_CREATED = "alarmCreated";

    public static final String[] ALL_COLUMNS = {ALARM_ID, ALARM_TEXT,ALARM_CREATED};

    //SQL to create table
    private static final String TABLE_CREATE =
            "CREATE TABLE " + TABLE_ALARMS + " (" +
                    ALARM_ID + " INTEGER PRIMARY KEY AUTOINCREMENT, " +
                    ALARM_TEXT + " TEXT, " +
                    ALARM_CREATED + " TEXT default CURRENT_TIMESTAMP" +
                    ")";

    public DBOpenHelper(Context context) {
        super(context,DATABASE_NAME, null, DATABASE_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL(TABLE_CREATE);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL("DROP TABLE IF EXISTS " + TABLE_ALARMS);
        onCreate(db);
    }
}
