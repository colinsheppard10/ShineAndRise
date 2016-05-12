package com.example.colin.computation;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.widget.Toast;

import static android.support.v4.app.ActivityCompat.startActivityForResult;
import static android.support.v4.content.ContextCompat.startActivities;

/**
 * Created by Colin on 5/10/16.
 */
public class AlarmReciever extends BroadcastReceiver {

    public static int flag;

    @Override
    public void onReceive(Context context, Intent intent) {
                startActivity(context);
    }

    public void startActivity(Context context){

        Intent newIntent = new Intent();
        newIntent.setClassName("com.example.colin.computation", "com.example.colin.computation.MainActivity");
        newIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        context.startActivity(newIntent);
    }

    public static void setFlag(){
        flag = 1;
    }
}
