#define BLYNK_TEMPLATE_ID "TMPL4kjotKr4S"
#define BLYNK_TEMPLATE_NAME "Weather station"
#define BLYNK_AUTH_TOKEN ""//here write your auth token,if you want to print it on blynk app,do not do anything

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h> 
#include <Adafruit_BME280.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

//here in "" type name and password of your wi fi,I added 2 beacause i have different wi fi ssid in different rooms,you can fill only 1 if you have 2 fill 2.
char ssid1[] = ""; //name
char pass1[] = "";//password

char ssid2[] = ""; //name
char pass2[] = "";//password


TwoWire I2Cone = TwoWire(1);

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &I2Cone, OLED_RESET);
Adafruit_BME280 bme; 
BlynkTimer timer;

// function for connecting to available Wi-Fi
void connectToWiFi() {
  Serial.println("\nTrying to connect to the First Network...");
  WiFi.begin(ssid1, pass1);
  
  int attempt = 0;
  // waiting 10 seconds
  while (WiFi.status() != WL_CONNECTED && attempt < 20) {
    delay(500);
    Serial.print(".");
    attempt++;
  }
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nThe first network is unavailable. Trying the second network...");
    WiFi.disconnect();
    WiFi.begin(ssid2, pass2);
    
    attempt = 0;
    while (WiFi.status() != WL_CONNECTED && attempt < 20) {
      delay(500);
      Serial.print(".");
      attempt++;
    }
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nSuccessfully connected to Wi-Fi!");
    Serial.print("IP adreess: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nError: None of the Wi-Fi networks are available!");
  }
}
void updateMeteoStation() {
  // If Wi-Fi suddenly disconnects while you're working, try reconnecting.
  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
    Blynk.connect();
    return;
  }

  float temp = bme.readTemperature();
  float hum = bme.readHumidity();
  float pres = bme.readPressure() / 133.322368;

  if (temp > 100.0 || isnan(temp)) {
    Serial.println("--- BME280 sensor failure! Restarting line... ---");
    Wire.end(); delay(300); Wire.begin(21, 22); bme.begin(0x76, &Wire);
    return;
  }

  // Automatically changing color which depends on temperature
  if (temp >= 30.0) {
    Blynk.setProperty(V1, "color", "#FF0000"); // Red = warm
  } else if (temp <= 15.0) {
    Blynk.setProperty(V1, "color", "#0000FF"); // Blue = cold
  } else {
    Blynk.setProperty(V1, "color", "#00FF00"); // Green = ok
  }

  String presString = String(pres, 1) + " mm Hg";

  // Sending on phone -------- if do not want to work with blink,just comment with "//" these three lines below and Blynk.run(); on 132 line
  Blynk.virtualWrite(V1, temp);
  Blynk.virtualWrite(V2, hum);
  Blynk.virtualWrite(V3, presString);

  // Printing
  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);
  display.setTextSize(2);
  display.setCursor(0, 0); display.print("T: "); display.print(temp, 1); display.println(" C");
  display.setCursor(0, 22); display.print("H: "); display.print(hum, 0); display.println(" %");
  display.setTextSize(1);
  display.setCursor(0, 50); display.print("P: "); display.print(pres, 1); display.println(" mm Hg");
  display.display();
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("--- LAUNCH OF A DUAL-NETWORK WEATHER STATION ---");

  Wire.begin(21, 22);
  pinMode(21, INPUT_PULLUP); pinMode(22, INPUT_PULLUP);
  I2Cone.begin(16, 17, 100000); 

  if(!display.begin(0x3C)) { display.begin(0x3D); }

  if (bme.begin(0x76, &Wire)) {  
    bme.setSampling(Adafruit_BME280::MODE_NORMAL, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::SAMPLING_X1, Adafruit_BME280::FILTER_OFF, Adafruit_BME280::STANDBY_MS_1000);
  }
  connectToWiFi();
  
  Blynk.config(BLYNK_AUTH_TOKEN);
  Blynk.connect();

  timer.setInterval(4000L, updateMeteoStation);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    Blynk.run();//here
  }
  timer.run();
}
