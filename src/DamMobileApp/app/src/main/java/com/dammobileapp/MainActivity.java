package com.dammobileapp;
import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
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

        btChannel.close();
    }


    private void initUI() {
       try {
            connectToBTServer();
        } catch (BluetoothDeviceNotFound bluetoothDeviceNotFound) {
            bluetoothDeviceNotFound.printStackTrace();
        }

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
                        toSend = "P=20F";
                    case R.id.button40:
                        toSend = "P=40F";
                    case R.id.button60:
                        toSend = "P=60F";
                    case R.id.button80:
                        toSend = "P=80F";
                    case R.id.button100:
                        toSend = "P=100F";
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
        final String url = "http://042c464fe0ae.ngrok.io/api/data";
        Http.get(url, response -> {
            if(response.code() == HttpURLConnection.HTTP_OK) {
                try {
                    JSONObject content = response.contentAsJson();
                    ((TextView) findViewById(R.id.level)).setText(content.getString("value"));
                    ((TextView) findViewById(R.id.state)).setText(content.getString("state"));
                    //((TextView) findViewById(R.id.opening)).setText(content.getString("opening"));

                    if (content.has("state")) {
                        if (content.getString("state").equals("ALARM")) {
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

        final String url = "http://042c464fe0ae.ngrok.io/api/data";
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

    private void connectToBTServer() throws BluetoothDeviceNotFound {
        final BluetoothDevice serverDevice = BluetoothUtils.getPairedDeviceByName(C.bluetooth.BT_DEVICE_ACTING_AS_SERVER_NAME);

        final UUID uuid = BluetoothUtils.getEmbeddedDeviceDefaultUuid();
        //final UUID uuid = BluetoothUtils.generateUuidFromString(C.bluetooth.BT_SERVER_UUID);

        new ConnectToBluetoothServerTask(serverDevice, uuid, new ConnectionTask.EventListener() {
            @Override
            public void onConnectionActive(final BluetoothChannel channel) {

                /*((TextView) findViewById(R.id.statusLabel)).setText(String.format("Status : connected to server on device %s",
                        serverDevice.getName()));

                findViewById(R.id.connectBtn).setEnabled(false);*/

                btChannel = channel;
                btChannel.registerListener(new RealBluetoothChannel.Listener() {
                    @Override
                    public void onMessageReceived(String receivedMessage) {
                        /*((TextView) findViewById(R.id.chatLabel)).append(String.format("> [RECEIVED from %s] %s\n",
                                btChannel.getRemoteDeviceName(),
                                receivedMessage));*/
                    }

                    @Override
                    public void onMessageSent(String sentMessage) {
                        /*((TextView) findViewById(R.id.chatLabel)).append(String.format("> [SENT to %s] %s\n",
                                btChannel.getRemoteDeviceName(),
                                sentMessage));*/
                    }
                });
            }

            @Override
            public void onConnectionCanceled() {
                /*((TextView) findViewById(R.id.statusLabel)).setText(String.format("Status : unable to connect, device %s not found!",
                        C.bluetooth.BT_DEVICE_ACTING_AS_SERVER_NAME));*/
            }
        }).execute();
    }
}
