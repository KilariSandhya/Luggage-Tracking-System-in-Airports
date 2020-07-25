#define SS_PIN 15  //D8
#define RST_PIN 5 //D1

#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define FIREBASE_HOST "firebase-host-id"
#define FIREBASE_AUTH "firebase-authentication-id"
#define WIFI_SSID "wifi-name"
#define WIFI_PASSWORD "wifi-password"

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int statuss = 0;
int count=0;

int out = 0;
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  // connect to wifi.
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.println();
  Serial.print("UIDtag:");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();
  if (content.substring(1) == "06 A8 48 1B") //change UID of the card that you want to give access
  {count++;
  if(count%2!=0){
      Serial.println(" Boarded to correct flight ");
      Firebase.setString("rfid","Boarded to correct flight(AIR707)");
      String str = Firebase.getString("rfid");
      Serial.println(str);
  }
  else {
      Serial.println(" Deboarded from correct flight ");
      Firebase.setString("rfid","Deboarded from correct flight(AIR707)");
      String str = Firebase.getString("rfid");
      Serial.println(str);
  }
  }
  
  else   {
    Serial.println(" Access Denied ");
    Firebase.setString("rfid","Luggage in wrong flight(AIR707)");
    String str = Firebase.getString("rfid");
    Serial.println(str);
  }
} 
