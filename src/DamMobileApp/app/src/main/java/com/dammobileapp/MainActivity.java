package com.dammobileapp;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.dammobileapp.netutils.Http;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.net.HttpURLConnection;
import java.util.Random;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initUI();
    }

    private void initUI() {
        tryHttpGet();

        /*findViewById(R.id.postBtn).setOnClickListener(v -> {
            try {
                tryHttpPost();
            } catch (JSONException e) {
                e.printStackTrace();
            }
        });*/
    }

    private void tryHttpGet(){
        final String url = "http://dummy.restapiexample.com/api/v1/employee/1";

        Http.get(url, response -> {
            if(response.code() == HttpURLConnection.HTTP_OK){
                try {
                    ((TextView)findViewById(R.id.level)).setText(response.contentAsJson().getString("level"));
                    ((TextView)findViewById(R.id.state)).setText(response.contentAsJson().getString("state"));
                    ((TextView)findViewById(R.id.opening)).setText(response.contentAsJson().getString("opening"));

                    if(response.contentAsJson().getString("state") == "alarm"){
                        findViewById(R.id.state).setEnabled(true);
                    }

                } catch (IOException | JSONException e) {
                    e.printStackTrace();
                }
            }
        });
    }


    private void tryHttpPost() throws JSONException {

        final String url = "http://dummy.restapiexample.com/api/v1/employee/1";
        final String content = new JSONObject()
                .put("mode","manual").toString();

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
