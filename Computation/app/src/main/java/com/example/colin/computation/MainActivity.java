package com.example.colin.computation;

import android.content.Context;
import android.content.Intent;
import android.os.Vibrator;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    public TextView testText;
    public Vibrator vibrator;
    public Button postpone;
    public Button start;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        vibrator = (Vibrator) getSystemService(Context.VIBRATOR_SERVICE);
        long[] pattern = { 0, 200, 500 };
        vibrator.vibrate(pattern,0);

        start = (Button) findViewById(R.id.button2);
        postpone = (Button) findViewById(R.id.button);

    }

    public void startComp(View view) {
        vibrator.cancel();
        BootReceiver.completedComp();
    }
}