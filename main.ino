#include <WiFiClientSecure.h>
#include <Wire.h>
#include <UniversalTelegramBot.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>   // Universal Telegram Bot Library written by Brian Lough: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
#include <ArduinoJson.h>

#define BOTtoken "6127169570:AAEndaFo-4INZV0PFfgRycfjeRdqK8p_wTM" // your Bot Token (Get from Botfather)
#define CHAT_ID "2070295919"

// Replace with your network credentials
const char* ssid = "";
const char* password = "";

#ifdef ESP8266
  X509List cert(TELEGRAM_CERTIFICATE_ROOT);
#endif

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// Checks for new messages every 1 second.
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

#define DHTPIN 25
#define LED_Pin 26
#define Buzzer_Pin 14
#define Smoke_Pin 34
#define Fire_Pin 35
#define Relay_Pin 5
bool relayState = LOW;

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Handle what happens when you receive new messages
void handleNewMessages(int numNewMessages) {
 Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    
    // Print the received message
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;

    if (text == "/info") {
      String welcome = "Welcome, MEGALODON " + from_name + ".\n";
      welcome += "Use the following commands to control your outputs.\n\n";
      welcome += "/cek_suhu - mengecek kondisi suhu ruangan saat ini \n";
      bot.sendMessage(chat_id, welcome, "");
    }

    if (text == "/cek_suhu"){
      float t = dht.readTemperature();
      if (!isnan(t)) {
        String message = "Suhu saat ini: " + String(t) + " °C";
        bot.sendMessage(chat_id, message, "");
      }
    }
    if (text == "yes"){
      bot.sendMessage(chat_id, "Pompa Air Dihidupkan", "");
      relayState = HIGH;
      digitalWrite(Relay_Pin,relayState);
    }
    if (text == "no"){
      bot.sendMessage(chat_id, "Pompa Air Dimatikan", "");
      relayState = LOW;
      digitalWrite(Relay_Pin,relayState);
    }
  }
}

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);
  dht.begin();
  pinMode(LED_Pin, OUTPUT);
  pinMode(Buzzer_Pin, OUTPUT);
  pinMode(Fire_Pin, INPUT);
  pinMode(Smoke_Pin, INPUT);
  pinMode(Relay_Pin, OUTPUT);
  digitalWrite(Relay_Pin, LOW);

#ifdef ESP8266
    configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
    client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
  #endif

// Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  #ifdef ESP32
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  #endif
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());  
}

void loop() {
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
  digitalWrite(Relay_Pin, LOW);
delay(1000);

int fire = analogRead(Fire_Pin);
Serial.println (fire);
if (fire <= 500){
  bot.sendMessage(CHAT_ID, "Api Terdeteksi!!!");
  bot.sendMessage(CHAT_ID, "Menghidupkan Pompa Air!!!");
  digitalWrite(Relay_Pin, HIGH);
  digitalWrite(LED_Pin, HIGH);
  tone(Buzzer_Pin, 1000);
}else{
  digitalWrite(LED_Pin, LOW);
  noTone(Buzzer_Pin);
  digitalWrite(Relay_Pin, LOW);
}

int smoke = analogRead(Smoke_Pin);
Serial.println (smoke);
if (smoke > 1500){
  bot.sendMessage(CHAT_ID, "Asap Terdeteksi!!!, Apakah ingin menyalakan pompa air? (yes/no)");
}

float h = dht.readHumidity();
float t = dht.readTemperature();
float f = dht.readTemperature(true);

if (isnan(h) || isnan(t) || isnan(f)) {
Serial.println(F("Sensor Gagal Terbaca!"));
return;
}
Serial.print(F("Kelembaban: "));
Serial.println(h);
Serial.print(F("Suhu: "));
Serial.print(t);
Serial.println(F("°C"));
Serial.print(f);
Serial.println(F("°F"));

lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Suhu: ");
lcd.print(t);
lcd.print(" C");

}
