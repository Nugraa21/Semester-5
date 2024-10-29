#include <WiFi.h>
#include <PubSubClient.h>
#define LED1 19
#define LED2 18
#define LED3 5
#define LED4 17

const char* ssid = "RPLA_2.4"; // Ganti dengan SSID WiFi Anda
const char* password = "utdijogja"; // Ganti dengan password WiFi Anda
const char* mqtt_server = "broker.mqttdashboard.com"; // Alamat broker MQTT

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);

  // Inisialisasi pin LED
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  // Matikan semua LED di awal
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);

  setupWiFi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void setupWiFi() {
  delay(10);
  Serial.print("Menghubungkan ke ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(" Terhubung");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Menghubungkan ke MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Terhubung");
      client.subscribe("data/bersama"); // Hanya subscribe, tidak publish
    } else {
      Serial.print("Gagal, kode rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0'; // Menambahkan null terminator
  String message = String((char*)payload);
  Serial.print("Pesan diterima: ");
  Serial.println(message);

  // Mengendalikan LED berdasarkan pesan
  if (message.length() >= 4) {
    digitalWrite(LED1, message[0] == '1' ? HIGH : LOW);
    digitalWrite(LED2, message[1] == '1' ? HIGH : LOW);
    digitalWrite(LED3, message[2] == '1' ? HIGH : LOW);
    digitalWrite(LED4, message[3] == '1' ? HIGH : LOW);
  }
}
