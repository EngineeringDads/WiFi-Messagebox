
#include <Wire.h>
#include "SSD1306Wire.h"
#include "font.h"
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <EEPROM.h>
#include <TZ.h>
#include <Servo.h>
#include "OLEDDisplayUI.h"


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define ID_ADDR 142
#define READ_ADDR 144

const int scanningDelay = 60 * 1000;


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
SSD1306Wire oled(0x3C, SDA, SCL);
OLEDDisplayUi ui (&oled);
Servo myservo;
int pos = 90;
int increment = -1;
int lightValue;
String line;
String mode;
char idSaved = '0';
bool wasRead = true;


const char* ssid = //Enter WIFI SSID
const char* password = //Enter WIFI password
String url = //Enter GITHUB url



void wifiConnect() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
    }
  }
  Serial.print("..done. IP ");
  Serial.println(WiFi.localIP());
}

void drawMessage(const String& message) {
  oled.clear();
  if (mode[0] == 't') {
    oled.setFont(Rancho_Regular_16);
    oled.setTextAlignment(TEXT_ALIGN_CENTER);
    oled.drawStringMaxWidth(64, 20, 128, message);
  }
  else {
    for (int i = 0; i <= message.length(); i++) {
      int x = i % 129;
      int y = i / 129;
      if (message[i] == '1') {
        oled.setPixel(x,y);
      }
    }
  }

  //display.display();
  oled.display();
}

void getGistMessage() {
  Serial.println("Getting Message");
  const int httpsPort = 443;
  const char* host = "gist.githubusercontent.com";
  const char fingerprint[] = "70 94 DE DD E6 C4 69 48 3A 92 70 A1 48 56 78 2D 18 64 E0 B7";

  WiFiClientSecure client;
  client.setFingerprint(fingerprint);
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: ESP8266\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("request sent");

  while (client.connected()) {
    String temp = client.readStringUntil('\n');
    if (temp == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  

  String id = client.readStringUntil('\n');
  Serial.printf("\tid: '%s', last processed id: '%c'\n", id.c_str(), idSaved);
  if (id[0] != idSaved) { // new message
    wasRead = 0;
    idSaved = id[0];

    mode = client.readStringUntil('\n');
    Serial.println("\tmode: " + mode);
    line = client.readStringUntil(0);
    Serial.println("\tmessage: " + line);
    drawMessage(line);
  } else {
    Serial.println("\t-> message id wasn't updated");
    oled.clear();
    oled.display();
  }

}

void spinServo() {
    for (pos = 84; pos <= 96; pos+= +1) {
        myservo.write(pos);
    delay(15);    //
    }
    for (pos = 96; pos >= 84; pos+= -1) {
        myservo.write(pos);
    delay(15);    //
    }
        for (pos = 84; pos <= 96; pos+= +1) {
        myservo.write(pos);
    delay(15);    //
    }
    for (pos = 96; pos >= 84; pos+= -1) {
        myservo.write(pos);
    delay(15);    //
    }
        for (pos = 84; pos <= 96; pos+= +1) {
        myservo.write(pos);
    delay(15);    //
    }
    for (pos = 96; pos >= 84; pos+= -1) {
        myservo.write(pos);
    delay(15);    //
    }
    delay(1500);



}


void setup() {
  Serial.begin(115200);

  myservo.attach(16);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);


  WiFi.mode(WIFI_STA);
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  WiFi.begin(ssid, password);
  int counter = 0;

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


  while (WiFi.status() != WL_CONNECTED) {
    delay(2000);
    oled.init();
    oled.flipScreenVertically();
    oled.setColor(WHITE);
    oled.setFont(ArialMT_Plain_16);
    oled.setTextAlignment(TEXT_ALIGN_CENTER);
    oled.clear();
    oled.drawStringMaxWidth(64,22,128, "WAITING TO CONNECT...");
    oled.display();



  }
  delay(2000);
  oled.clear();
  oled.setTextAlignment(TEXT_ALIGN_LEFT);
  oled.setFont(Satisfy_Regular_18);
  oled.setColor(WHITE);
  oled.drawString(19,23,"HI <3");
  oled.display();
  delay(100);

}

void loop() {



  if (WiFi.status() != WL_CONNECTED) {
    wifiConnect();
  }


  if (wasRead) {
    getGistMessage();
  }

  while (!wasRead) {
    yield();
    spinServo();
    lightValue = analogRead(0);
    Serial.println(lightValue);
    if (lightValue > 300) {
      Serial.printf("Message Read");
      wasRead = 1;
      myservo.write(90);
    }
  }
  delay(scanningDelay);
}
