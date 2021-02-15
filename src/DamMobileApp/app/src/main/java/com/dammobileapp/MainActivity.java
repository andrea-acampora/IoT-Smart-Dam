package com.dammobileapp;
import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
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
import java.util.UUID;

import unibo.btlib.BluetoothChannel;
import unibo.btlib.BluetoothUtils;
import unibo.btlib.ConnectToBluetoothServerTask;
import unibo.btlib.ConnectionTask;
import unibo.btlib.RealBluetoothChannel;
import unibo.btlib.exceptions.BluetoothDeviceNotFound;


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

    @Override
    protected void onStop() {
        super.onStop();
        try {
            sendModalityToServer("AUTOMATIC");
        } catch (JSONException e) {
            e.printStackTrace();
        }
        btChannel.close();
    }


    private void initUI() {
        findViewById(R.id.buttonbt).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    connectToBTServer();
                } catch (BluetoothDeviceNotFound bluetoothDeviceNotFound) {
                    bluetoothDeviceNotFound.printStackTrace();
                }
            }
        });

        tryHttpGet();

        RadioGroup radioGroup = (RadioGroup) findViewById(R.id.radioGroup);
        radioGroup.setOnCheckedChangeListener((group, checkedId) -> {
            String toSend = "20";
            String toSendBt="";
            switch (checkedId){
                case R.id.button20:
                    toSendBt = "P=20F";
                    toSend="20";
                    break;
                case R.id.button40:
                    toSendBt = "P=40F";
                    toSend="40";
                    break;
                case R.id.button60:
                    toSendBt = "P=60F";
                    toSend="60";
                    break;
                case R.id.button80:
                    toSendBt = "P=80F";
                    toSend="80";
                    break;
                case R.id.button100:
                    toSendBt = "P=100F";
                    toSend="100";
                    break;
            }
            btChannel.sendMessage(toSendBt);
            try {
                sendOpeningLevelToServer(toSend);
            } catch (JSONException e) {
                e.printStackTrace();
            }
        });


        Button mode = (Button)findViewById(R.id.modeButton);
        mode.setOnClickListener(v -> {
           String modeText = (String) ((Button) findViewById(R.id.modeButton)).getText();
            try {
                sendModalityToServer(modeText);
            } catch (JSONException e) {
                e.printStackTrace();
            }
        });
    }

    private void tryHttpGet(){
        final String url = "http://f6ab7aa9c1c8.ngrok.io/api/data";
        Http.get(url, response -> {

            Thread thread = new Thread(new Runnable() {

                @Override
                public void run() {
                    try  {
            if (response.code() == HttpURLConnection.HTTP_OK) {
                try {
                    JSONObject content = response.contentAsJson();

                    if (content.has("state")) {
                        MainActivity.this.runOnUiThread(() -> {
                            try {
                                ((TextView) findViewById(R.id.state)).setText(content.getString("state"));
                            } catch (JSONException e) {
                                e.printStackTrace();
                            }
                        });

                        if (content.getString("state").equals("ALARM")) {
                            MainActivity.this.runOnUiThread(() -> findViewById(R.id.modeButton).setEnabled(true));
                        } else {
                            MainActivity.this.runOnUiThread(() -> findViewById(R.id.modeButton).setEnabled(false));
                            MainActivity.this.runOnUiThread(() -> findViewById(R.id.radioGroup).setVisibility(View.GONE));
                        }
                    }

                    if (content.has("value")) {
                        MainActivity.this.runOnUiThread(() -> {
                            try {
                                ((TextView) findViewById(R.id.level)).setText(content.getString("value"));
                            } catch (JSONException e) {
                                e.printStackTrace();
                            }
                        });
                    }


                    if (content.has("opening")) {
                        MainActivity.this.runOnUiThread(() -> {
                            try {
                                ((TextView) findViewById(R.id.opening)).setText(content.getString("opening"));
                            } catch (JSONException e) {
                                e.printStackTrace();
                            }
                        });
                    }

                } catch (IOException | JSONException e) {
                    e.printStackTrace();
                }
            }
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            });

            thread.start();
        });

}

    private void sendModalityToServer(String mode) throws JSONException {

        final String url = "http://f6ab7aa9c1c8.ngrok.io/api/mode";
        final String content = new JSONObject()
                .put("mode",mode).toString();

        Http.post(url, content.getBytes(), response -> {
            if(response.code() == HttpURLConnection.HTTP_OK){

                Button button = (Button)findViewById(R.id.modeButton);

                if(mode.equals("manual")){
                    findViewById(R.id.radioGroup).setVisibility(View.VISIBLE);
                    String modeText = "automatic";
                    button.setText(modeText);

                }else if(mode.equals("automatic")){
                    findViewById(R.id.radioGroup).setVisibility(View.GONE);
                    String modeText = "manual";
                    button.setText(modeText);
                }

            }
        });
    }

    private void sendOpeningLevelToServer(String value) throws JSONException {
        Log.d("post","here");
        final String url = "http://f6ab7aa9c1c8.ngrok.io/api/openingDam";
        final String content = new JSONObject()
                .put("opening",value).toString();

        Http.post(url, content.getBytes(), response -> {
            if(response.code() == HttpURLConnection.HTTP_OK) {
            }

        });
    }

    private void connectToBTServer() throws BluetoothDeviceNotFound {
        final BluetoothDevice serverDevice = BluetoothUtils.getPairedDeviceByName(C.bluetooth.BT_DEVICE_ACTING_AS_SERVER_NAME);

        final UUID uuid = BluetoothUtils.getEmbeddedDeviceDefaultUuid();
        //final UUID uuid = BluetoothUtils.generateUuidFromString(C.bluetooth.BT_SERVER_UUID);

        new ConnectToBluetoothServerTask(serverDevice, uuid, new ConnectionTask.EventListener() {
            @Override
            public void onConnectionActive(final BluetoothChannel channel) {


                findViewById(R.id.buttonbt).setEnabled(false);
                ((Button)findViewById(R.id.buttonbt)).setText("CONNECTED");

                btChannel = channel;
            }

            @Override
            public void onConnectionCanceled() {
                ((Button)findViewById(R.id.buttonbt)).setText("TRY AGAIN");
            }
        }).execute();
    }
}
