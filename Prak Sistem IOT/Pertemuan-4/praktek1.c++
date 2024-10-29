#include <WiFi.h>
#include <PubSubClient.h>
#define LED1 19
#define LED2 18
#define LED3 5
#define LED4 17
const char* ssid = "harjolukito";
const char* password = "ami1971da";
const char* mqtt_server = "broker.mqtt-dashboard.com";
WiFiClient espClient;
PubSubClient client(espClient);
char msg[50];
String tpk=String(50);
void setup_wifi() {
 delay(10);
 Serial.println();
 Serial.print("Connecting to ");
 Serial.println(ssid);
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 }
 randomSeed(micros());
 Serial.println("");
 Serial.println("WiFi connected");
 Serial.println("IP address: ");
 Serial.println(WiFi.localIP());
}
void callback(char* topic, byte* payload, unsigned int 
length) {
 Serial.print("Message arrived [");
 Serial.print(topic);
 Serial.println("] ");
 tpk=topic;
 for(int i=0;i<length;i++){
 Serial.print(payload[i]);
 }
 if(tpk=="yogya/utara/lampu"){
 switch (char(payload[0])) {
 case '1': if ((char)payload[1] == '1') {
 digitalWrite(LED1, HIGH); 
 } else if ((char)payload[1] == '0'){
 digitalWrite(LED1, LOW); 
 } 
 break;
 case '2': if ((char)payload[1] == '1') {
 digitalWrite(LED2, HIGH);
 } else if ((char)payload[1] == '0'){
 digitalWrite(LED2, LOW); 
 } 
 break;
 }
 } 
 if(tpk=="yogya/timur/lampu"){
 switch (char(payload[0])) {
 case '1': if ((char)payload[1] == '1') {
 digitalWrite(LED3, HIGH);
 } else if ((char)payload[1] == '0'){
 digitalWrite(LED3, LOW); 
 } 
 break;
 case '2': if ((char)payload[1] == '1') {
 digitalWrite(LED4, HIGH);
 } else if ((char)payload[1] == '0'){
 digitalWrite(LED4, LOW); 
 } 
 break;
 }
 }
 
}