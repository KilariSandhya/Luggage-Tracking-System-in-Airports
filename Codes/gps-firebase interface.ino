#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

static const int RXPin = 12, TXPin = 13;
static const uint32_t GPSBaud = 9600;

// repace your wifi username and password
const char* ssid     = "siri";
const char* password = "8919089349";

#define FIREBASE_HOST "final-2b6e1.firebaseio.com"
#define FIREBASE_AUTH "ICTM3JGeOwXmcjTtxd3p7jfRJ3D18Uuce1VN0ggZ"

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  Serial.begin(115200);
  ss.begin(GPSBaud);
  Serial.println(F("GPS module"));
  Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println();

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
   Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}
void displayInfo()
{
  if (gps.location.isValid())
  {

    double latitude = (gps.location.lat());
    double longitude = (gps.location.lng());
    
    String latbuf;
    latbuf += (String(latitude, 6));
    Serial.println(latbuf);

    String lonbuf;
    lonbuf += (String(longitude, 6));
    Serial.println(lonbuf);

    if(Firebase.setString("gps","location"))
    {
    Firebase.setString("latitude",latbuf);
    Firebase.setString("longitude",lonbuf);
    String str1 = Firebase.getString("latitude");
    String str2 = Firebase.getString("longitude");
    Serial.println(str1);
    Serial.println(str2); 
    }
    delay(20000);
    
  }
  else
  {
    Serial.print(F("INVALID"));
    if(Firebase.setString("gps","location"))
    {
    Firebase.setString("latitude","null");
    Firebase.setString("longitude","null");
    String str1 = Firebase.getString("latitude");
    String str2 = Firebase.getString("longitude");
    Serial.println(str1);
    Serial.println(str2); 
    }
  }
  Serial.println();
}
