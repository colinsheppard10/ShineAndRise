package com.example.colin.shinerise;

import android.content.ContentValues;
import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.RadioButton;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.TimePicker;

import java.io.IOException;
import java.text.DecimalFormat;

public class MainActivity extends AppCompatActivity {
    public TimePicker myTime;
    private Button setAlarm;
    private Button viewSchedule;
    private TextView error;
    private Switch mySwitch;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        myTime = (TimePicker) findViewById(R.id.timePicker);
        setAlarm = (Button) findViewById(R.id.button);
        viewSchedule = (Button) findViewById(R.id.button2);
        error = (TextView) findViewById(R.id.textView);
        mySwitch = (Switch) findViewById(R.id.switch1);

        setAlarm.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (isOnline()) {
                    requestData("10.0.0.6", finishedEditing());
                } else {
                    error.append("network connection failed");
                }

                insertAlarm(finishedEditing());
                openEditorForSchedule(v);
            }
        });

        viewSchedule.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                openEditorForSchedule(v);
            }
        });

        mySwitch.setChecked(false);
        mySwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener(){

            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked){
                    if (isOnline()) {
                        requestData("10.0.0.6", "2N OVERID");
                    } else {
                        error.append("network connection failed");
                    }
                }else{
                    if (isOnline()) {
                        requestData("10.0.0.6", "3F OVERID");
                    } else {
                        error.append("network connection failed");
                    }
                }
            }
        });

    }

    public String finishedEditing(){
        int hour = myTime.getCurrentHour();
        int minute = myTime.getCurrentMinute();
        String newAlarm;
        DecimalFormat df = new DecimalFormat("00");

        newAlarm = getDayOfWeek()+ " " + (df.format(hour))+":"+(df.format(minute));
        return newAlarm;
    }

    private String getDayOfWeek() {

        RadioButton Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday;
        Monday = (RadioButton) findViewById(R.id.radioButton);
        Tuesday = (RadioButton) findViewById(R.id.radioButton2);
        Wednesday = (RadioButton) findViewById(R.id.radioButton3);
        Thursday = (RadioButton) findViewById(R.id.radioButton4);
        Friday = (RadioButton) findViewById(R.id.radioButton5);
        Saturday = (RadioButton) findViewById(R.id.radioButton6);
        Sunday = (RadioButton) findViewById(R.id.radioButton7);

        if (Monday.isChecked())
            return "Mon";
        else if (Tuesday.isChecked())
            return "Tue";
        else if (Wednesday.isChecked())
            return "Wed";
        else if (Thursday.isChecked())
            return "Thu";
        else if (Friday.isChecked())
            return "Fri";
        else if (Saturday.isChecked())
            return "Sat";
        else if (Sunday.isChecked())
            return "Sun";
        else
            return "NDS";
    }

    private void insertAlarm(String newAlarm) {

        // inserting into database
        ContentValues values = new ContentValues();
        values.put(DBOpenHelper.ALARM_TEXT, newAlarm);
        getContentResolver().insert(AlarmsProvider.CONTENT_URI, values);
        setResult(RESULT_OK);
    }

    public void openEditorForSchedule(View view) {
        // opening EditorAcivity
        Intent intent = new Intent(this, EditorActivity.class);
        startActivityForResult(intent, 1001);
    }

    protected boolean isOnline() {

        ConnectivityManager cm = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo netInfo = cm.getActiveNetworkInfo();
        if (netInfo != null && netInfo.isConnectedOrConnecting()) {
            return true;
        } else {
            return false;
        }

    }

    private void requestData(String uri,String message) {
        MyTask task = new MyTask();
        task.execute(uri, message);
    }

    private class MyTask extends AsyncTask<String, String, String> {

        @Override
        protected String doInBackground(String... params) {

            String content = null;

            try {
                content = TCPManager.GetDate(params[0],params[1]);
            } catch (IOException e) {
                e.printStackTrace();
            }
            return content;
        }
    }
}
