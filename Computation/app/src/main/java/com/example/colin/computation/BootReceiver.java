package com.example.colin.computation;

import android.app.AlarmManager;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.widget.Toast;

import java.util.Calendar;

/**
 * Created by Colin on 5/10/16.
 */

public class BootReceiver extends BroadcastReceiver {

    public AlarmManager alarmMgr;
    public PendingIntent alarmIntent;

    @Override
    public void onReceive(Context context, Intent intent) {
        if (intent.getAction().equals("android.intent.action.BOOT_COMPLETED")){
            Toast.makeText(context, "booooootedddddd", Toast.LENGTH_LONG).show();

            alarmMgr = (AlarmManager)context.getSystemService(Context.ALARM_SERVICE);
            Intent newIntent = new Intent(context, AlarmReciever.class);
            alarmIntent = PendingIntent.getBroadcast(context, 0, newIntent, 0);

            // Set the alarm to start at 8:30 a.m.
            Calendar calendar = Calendar.getInstance();
            calendar.setTimeInMillis(System.currentTimeMillis());
            calendar.set(Calendar.HOUR_OF_DAY, 11);
            calendar.set(Calendar.MINUTE, 37);

            alarmMgr.setRepeating(AlarmManager.RTC_WAKEUP, calendar.getTimeInMillis(), 1000 * 60 * 2, alarmIntent);

        }
    }

}