package surfer.example.surfer.gpsfinal;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class Firebase extends AppCompatActivity {
    Button gps,rfid;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_firebase);

        gps=findViewById(R.id.gps);
        rfid=findViewById(R.id.rfid);

        gps.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent gps= new Intent (Firebase.this,Gps_id.class);
                startActivity(gps);
            }
        });
        rfid.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent gps= new Intent (Firebase.this,Rfid.class);
                startActivity(gps);
            }
        });
    }
}
