package surfer.example.surfer.gpsfinal;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
EditText emailId,passId;
Button loginId;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        emailId = findViewById(R.id.email);
        passId = findViewById(R.id.password);
        loginId = findViewById(R.id.login);

        loginId.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                loginId();
            }
        });
    }
    public void loginId(){
        String user=emailId.getText().toString().trim();
        String pswd=passId.getText().toString().trim();
        if((user.equals("brunda@gmail.com") && pswd.equals("bru123"))||(user.equals("hrijusha@gmail.com") && pswd.equals("123456"))||(user.equals("sandhya@gmail.com") && pswd.equals("ksandy12"))){
            Toast.makeText(this,"Login Successful!",Toast.LENGTH_LONG).show();
            startActivity(new Intent(getApplicationContext(), Firebase.class));
        }
        else
        {
            Toast.makeText(this, "Please enter valid inputs",Toast.LENGTH_LONG).show();
        }
    }
}
