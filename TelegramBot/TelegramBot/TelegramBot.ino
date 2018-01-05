//#include <WiFi101.h> 
#include <SPI.h>  
#include <TelegramBot.h>  
#include <ESP8266WiFi.h>
 
// Initialize Wifi connection to the router  
const char* ssid = "3Dit-temp";              // your network ssid
const char* password = "8EQ2z9x6";           // your network key 
// Initialize Telegram BOT  
const char* BotToken = "279470197:AAEYzyzvL1PuULjicogYKjpOUnxUUvUyW-Q";    // your Bot Teken  
WiFiClient client;  
TelegramBot bot(BotToken,client);  
const int ledPin = 13;  // the number of the LED pin  
void setup() 
{  
 Serial.begin(115200);  
 while (!Serial) {}  //Start running when the serial is open 
 delay(3000);  
 // attempt to connect to Wifi network:  
 Serial.print("Connecting Wifi: ");  
 Serial.println(ssid);  
 WiFi.begin(ssid, password);
 
 while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 Serial.println("");  
 Serial.println("WiFi connected");  
 bot.begin();  
 pinMode(ledPin, OUTPUT);  
}  
void loop() 
{  
 message m = bot.getUpdates(); // Read new messages  
 if (m.text.equals("On")) 
       {  
   digitalWrite(ledPin, HIGH);  
   Serial.println("message received");  
   bot.sendMessage(m.chat_id, "The Led is now ON");  
 }  
 else if (m.text.equals("Off")) 
       {  
   digitalWrite(ledPin, LOW);  
   Serial.println("message received");  
   bot.sendMessage(m.chat_id, "The Led is now OFF");  
 }  
}  
