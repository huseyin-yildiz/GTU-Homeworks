package com.huseyin.hexgame;

import android.Manifest;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.res.Resources;
import android.os.Bundle;
import android.util.TypedValue;
import android.view.View;
import android.widget.Button;
import android.widget.NumberPicker;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import HexEngine.Hex;

public class SettingsActivity extends AppCompatActivity {

    RadioGroup colorGroup1, colorGroup2, matchGroup, startGroup;
    TextView tvUser2;                                                       // required views and fields
    NumberPicker np;
    Button startBtn;

    Hex hex;
    String color1 = "Blue", color2="Red";
    int boardSize = 7;
    boolean withComputer;
    boolean isOneStart;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        getSupportActionBar().hide();

        setContentView(R.layout.activity_settings);
        colorGroup1 = findViewById(R.id.settings_color1);
        colorGroup2 = findViewById(R.id.settings_color2);
        matchGroup = findViewById(R.id.radioBtn1);                                            // gets all views by id and
        startGroup = findViewById(R.id.radioStart);
        tvUser2 = findViewById(R.id.textUser2);
        np = findViewById(R.id.number_picker);
        startBtn = findViewById(R.id.startBtn);

        np.setMinValue(7);
        np.setMaxValue(18);
        np.setOnValueChangedListener(new NumberPicker.OnValueChangeListener() {
            @Override
            public void onValueChange(NumberPicker picker, int oldVal, int newVal) {                    // taking boardSize
                boardSize = newVal;
            }
        });

        matchGroup.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                if(checkedId == R.id.rb_one) {                                                          // taking if Computer - One or not
                    colorGroup2.setVisibility(View.VISIBLE);
                    tvUser2.setVisibility(View.VISIBLE);
                    withComputer = false;
                }
                else {

                    colorGroup2.setVisibility(View.INVISIBLE);                                                  // makes invisible colors when cllick comp - one
                    tvUser2.setVisibility(View.INVISIBLE);
                    withComputer = true;
                }
            }
        });

        startGroup.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {                        // gets radio button settings
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                if(checkedId == R.id.user1Start)
                    isOneStart = false;
                else
                    isOneStart = true;
            }
        });

        RadioGroup.OnCheckedChangeListener listener = new RadioGroup.OnCheckedChangeListener() {                // listener for color radio groups
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                RadioButton rb = findViewById(checkedId);

                for(int i=0; i<group.getChildCount(); i++)
                    ((RadioButton)group.getChildAt(i) ).setText("");

                if(rb.isChecked()) {
                    rb.setTextAlignment(View.TEXT_ALIGNMENT_CENTER);
                    rb.setText("X");

                    if(group == colorGroup1 )
                        color1 = rb.getTag().toString();

                    else
                        color2 = rb.getTag().toString();

                }
            }
        };

        colorGroup1.setOnCheckedChangeListener(listener);
        colorGroup2.setOnCheckedChangeListener(listener);

        System.out.println("-------------Test-----------");                                                         // starting test
        Driver driver = new Driver();
        driver.test();
        System.out.println("-------------Exception Test-----------");
        driver.exceptionTest();
    }




    public void colorOnClick(View view) {
        RadioButton rb = (RadioButton) view;                                            // color radio button on click

    }

    public int dpToPx(float dp){
        Resources r = getResources();
        int px = (int) TypedValue.applyDimension(
                TypedValue.COMPLEX_UNIT_DIP,
                dp,
                r.getDisplayMetrics()
        );
        return px;
    }

    public void start(View view) {                                                  // makes an intent puts the hex game to in intent and starts the main activity (board representation)

        if(requestWritePerm()) {

            try {
                hex = new Hex(boardSize, color1, color2);

                if (withComputer)
                    color2 = "Computer";
                else if (isOneStart) {
                    hex.changePlayerTurn();
                }
            } catch (Exception e) {
                Toast.makeText(this, e.getMessage(), Toast.LENGTH_LONG).show();
            }

            Intent intent = new Intent(this, MainActivity.class);
            hex.setIsOneStart(isOneStart);
            intent.putExtra("hex", hex);
            finish();
            startActivity(intent);


        }

    }


    private boolean requestWritePerm(){                                                                                        //  requests the write permission from user
        if(ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED)
        {
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 1);
            return false;
        }
        return true;
    }

}