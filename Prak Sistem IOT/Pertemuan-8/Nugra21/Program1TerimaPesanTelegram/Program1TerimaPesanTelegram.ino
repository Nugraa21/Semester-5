#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// Wifi network station credentials
#define WIFI_SSID "RPLA_2.4"
#define WIFI_PASSWORD "utdijogja"

// Telegram BOT Token (Get from Botfather)
#define BOT_TOKEN "7650684774:AAGob6Ye1lWLl0ZtvmRbhDjqZAoXHN9a0ik"
#define LED1 19
#define LED1 18
#define LED1 05
#define LED1 17

const unsigned long BOT_MTBS = 1000; // mean time between scan messages

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime; // last time messages' scan has been done


int led1Status = 0;
int led2Status = 0;
int led3Status = 0;
int led4Status = 0;

void handleNewMessages(int numNewMessages)
{
  Serial.print("handleNewMessages ");
  Serial.println(numNewMessages);

  for (int i = 0; i < numNewMessages; i++)
  {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "")
      from_name = "Guest";

    if (text == "/led1on")
    {
      digitalWrite(LED1, HIGH); // turn the LED on (HIGH is the voltage level)
      led1Status = 1;
      bot.sendMessage(chat_id, "Led1 ON", "");
    }

    if (text == "/led1off")
    {
      led1Status = 0;
      digitalWrite(LED1, LOW); // turn the LED off (LOW is the voltage level)
      bot.sendMessage(chat_id, "Led1 OFF", "");
    }

    if (text == "/status")
    {
      if (led1Status)
      {
        bot.sendMessage(chat_id, "Led1 ON", "");
      }
      else
      {
        bot.sendMessage(chat_id, "Led1 OFF", "");
      }
    }

    if (text == "/start")
    {
      String welcome = "Welcome to Universal Arduino Telegram Bot library, " + from_name + ".\n";
      welcome += "This is Flash Led Bot example.\n\n";
      welcome += "/led1on : to switch the Led ON\n";
      welcome += "/led1off : to switch the Led OFF\n";
      welcome += "/status : Returns current status of LED\n";
      bot.sendMessage(chat_id, welcome, "");
    }
  }
}


void setup()
{
  Serial.begin(115200);
  Serial.println();

  pinMode(LED1, OUTPUT); // initialize digital ledPin as an output.
  delay(10);
  digitalWrite(LED1, LOW); // initialize pin as off (active LOW)

  // attempt to connect to Wifi network:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);
}

void loop()
{
  if (millis() - bot_lasttime > BOT_MTBS)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages)
    {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
}