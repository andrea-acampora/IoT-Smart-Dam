package com.dammobileapp;
import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioGroup;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.dammobileapp.netutils.Http;
import com.dammobileapp.netutils.C;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.net.HttpURLConnection;
import java.nio.BufferUnderflowException;

import unibo.btlib.BluetoothChannel;


public class MainActivity extends AppCompatActivity {

    private BluetoothChannel btChannel;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final BluetoothAdapter btAdapter = BluetoothAdapter.getDefaultAdapter();

        if(btAdapter != null && !btAdapter.isEnabled()){
            startActivityForResult(new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE), C.bluetooth.ENABLE_BT_REQUEST);
        }


        initUI();
    }

    private void initUI() {
        tryHttpGet();

        RadioGroup radioGroup = (RadioGroup) findViewById(R.id.radioGroup);
        radioGroup.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener()
        {
            @SuppressLint("NonConstantResourceId")
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                String toSend = "20";
                switch (checkedId){
                    case R.id.button20:
                        toSend = "20";
                    case R.id.button40:
                        toSend = "40";
                    case R.id.button60:
                        toSend = "60";
                    case R.id.button80:
                        toSend = "80";
                    case R.id.button100:
                        toSend = "100";
                }
                btChannel.sendMessage(toSend);
            }
        });

        Button mode = (Button)findViewById(R.id.modeButton);
        mode.setOnClickListener(v -> {
           String modeText = (String) ((Button) findViewById(R.id.modeButton)).getText();
           try {
                mode.setText(modeText == "MANUAL"? "AUTOMATIC" : "MANUAL");
                tryHttpPost(modeText == "MANUAL"? "AUTOMATIC" : "MANUAL");
            } catch (JSONException e) {
                e.printStackTrace();
            }

        });
    }

    private void tryHttpGet(){
        final String url = "http://dummy.restapiexample.com/api/v1/employee/1";
        Http.get(url, response -> {
            if(response.code() == HttpURLConnection.HTTP_OK) {
                try {
                    JSONObject content = response.contentAsJson();
                   // ((TextView) findViewById(R.id.level)).setText(content.getString("level"));
                    ((TextView) findViewById(R.id.state)).setText(content.getString("status"));
                  //  ((TextView) findViewById(R.id.opening)).setText(content.getString("opening"));

                    if (content.has("status")) {
                        if (content.getString("status").equals("success")) {
                            findViewById(R.id.modeButton).setEnabled(true);
                            findViewById(R.id.radioGroup).setVisibility(View.VISIBLE);
                        } else {
                            findViewById(R.id.modeButton).setEnabled(false);
                            findViewById(R.id.radioGroup).setVisibility(View.GONE);
                        }
                    }
                    } catch(IOException | JSONException e){
                        e.printStackTrace();
                    }
            }
        });

}

    private void tryHttpPost(String mode) throws JSONException {

        final String url = "http://dummy.restapiexample.com/api/v1/employee/1";
        final String content = new JSONObject()
                .put("mode",mode).toString();

        Http.post(url, content.getBytes(), response -> {
            if(response.code() == HttpURLConnection.HTTP_OK){
                try {
                    ((TextView)findViewById(R.id.modeButton)).setText(response.contentAsString());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });
    }
}
