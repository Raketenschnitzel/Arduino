
/*******************************************************************
    this is a basic example how to program a Telegram Bot
    using TelegramBOT library on ESP8266
 *                                                                 *
    Open a conversation with the bot, you can command via Telegram
    a led from ESP8266 GPIO
    https://web.telegram.org/#/im?p=@FlashledBot_bot
 *                                                                 *
    written by Giancarlo Bacchio
 *******************************************************************/

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266TelegramBOT.h>
#include "HX711.h" 

HX711 scale; 

// Initialize Wifi connection to the router
char ssid[]       = "Lotte-WLAN";               // your network SSID (name)
char password[]   = "GrueneLotteApril2016.";                 // your network key

// Initialize Telegram BOT
#define BOTtoken "279470197:AAEYzyzvL1PuULjicogYKjpOUnxUUvUyW-Q"  //token of FlashledBOT
#define BOTname "LotteBreadBot"
#define BOTusername "LotteBreadbot"

TelegramBOT bot(BOTtoken, BOTname, BOTusername);

int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done
bool Start = false;
float weight;
char botanswer[15];

// Initialize HX711 for Scale Reading
float calibration_factor = 405.94; //calibration value 2019-01-11
float offset             = 322342; 

/********************************************
   EchoMessages - function to Echo messages
 ********************************************/
void Bot_ExecMessages() {
  for (int i = 1; i < bot.message[0][0].toInt() + 1; i++)      {
    //bot.message[i][5]=bot.message[i][5].substring(1,bot.message[i][5].length());
    if (bot.message[i][5] == "ledon") {
      digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
      bot.sendMessage(bot.message[i][4], "Led is ON", "");
    }
    if (bot.message[i][5] == "ledoff") {
      digitalWrite(13, LOW);    // turn the LED off (LOW is the voltage level)
      bot.sendMessage(bot.message[i][4], "Led is OFF", "");
    }
     if (bot.message[i][5] == "breadamount") {
      weight = scale.get_units(10);
      dtostrf(weight,7, 3, botanswer);
      bot.sendMessage(bot.message[i][4], botanswer, "");
    }
    if (bot.message[i][5] == "start") {
      String wellcome = "Welcome from FlashLedBot, your personal Bot on ESP8266 board";
      String wellcome1 = "ledon : to switch the Led ON";
      String wellcome2 = "ledoff : to switch the Led OFF";
      Serial.println("Wellcome from FlashLedBot, your personal Bot on ESP8266 board");
      bot.sendMessage(bot.message[i][4], wellcome, "");
      bot.sendMessage(bot.message[i][4], wellcome1, "");
      bot.sendMessage(bot.message[i][4], wellcome2, "");
      Start = true;
    }
  }
  bot.message[0][0] = "";   // All messages have been replied - reset new messages
}


void setup() {
  Serial.begin(9600);

  //deactivate Watchdog
  ESP.wdtDisable();

  //scale
  Serial.print("Initialize Scale");
  scale.begin(4, 5); //GPIO4 is Data, GPIO5 is Serial Clock SCK
  scale.set_scale(calibration_factor);
  scale.set_offset(offset); //set fix offset for breadbot
  Serial.print(scale.get_units(),10);

  // attempt to connect to Wifi network:
  delay(3000);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  bot.begin();      // launch Bot functionalities
  pinMode(13, OUTPUT); // initialize digital pin 2 as an output.
}



void loop() {
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    bot.getUpdates(bot.message[0][1]);   // launch API GetUpdates up to xxx message
    Bot_ExecMessages();   // reply to message with Echo
    Bot_lasttime = millis();
  }
}

