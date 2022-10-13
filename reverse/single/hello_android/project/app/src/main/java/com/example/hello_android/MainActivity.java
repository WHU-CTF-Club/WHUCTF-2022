package com.example.hello_android;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.*;

public class MainActivity extends AppCompatActivity{

    Button button;
    EditText editText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        button = findViewById(R.id.button);
        editText = findViewById(R.id.editText);

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                switch (view.getId()){
                    case R.id.button:
                        String flag = editText.getText().toString();

                        // mayctf{My_Easy_Android_Reverse!}
                        if (flag.length() == 32) {
                            int[] answers = {
                                    109, 96, 123, 96, 112, 99, 125, 74,
                                    113, 86, 79, 106, 127, 116, 81, 78,
                                    126, 117, 96, 124, 125, 113, 73, 69,
                                    125, 111, 127, 105, 111, 120, 63, 98,
                            };
                            boolean FLAG = false;
                            for (int i = 0; i < flag.length(); ++i) {
                                if ((flag.charAt(i) ^ i) != answers[i])
                                    FLAG = true;
                            }
                            if (FLAG == false) {
                                AlertDialog.Builder ab = new AlertDialog.Builder(view.getContext());
                                ab.setTitle("Congratulations!");
                                ab.setPositiveButton("OK",null);
                                ab.show();
                            }
                            else {
                                AlertDialog.Builder ab = new AlertDialog.Builder(view.getContext());
                                ab.setTitle("Try again!");
                                ab.setPositiveButton("OK",null);
                                ab.show();
                            }
                        }
                        else {
                            AlertDialog.Builder ab = new AlertDialog.Builder(view.getContext());
                            ab.setTitle("Oops! That's not quite good!");
                            ab.setPositiveButton("OK",null);
                            ab.show();
                        }

                        break;
                }
            }
        });
    }

}