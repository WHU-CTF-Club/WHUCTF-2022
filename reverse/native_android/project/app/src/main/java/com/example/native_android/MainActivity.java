package com.example.native_android;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.*;

import com.example.native_android.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    Button button;
    EditText editText;

    // Used to load the 'native_android' library on application startup.
    static {
        System.loadLibrary("native_android");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        button = findViewById(R.id.button);
        editText = findViewById(R.id.editText);

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                switch (view.getId()) {
                    case R.id.button:
                        String flag = editText.getText().toString();
                        AlertDialog.Builder ab = new AlertDialog.Builder(view.getContext());
                        ab.setTitle(checkFlagNative(flag));
                        ab.setPositiveButton("OK",null);
                        ab.show();
                        break;
                }
            }
        });
    }

    /**
     * A native method that is implemented by the 'native_android' native library,
     * which is packaged with this application.
     */
    public native String checkFlagNative(String str);
}