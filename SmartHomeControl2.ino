#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "FoxFi69";
const char* password = "adithya123";

#define ORG "wc6qda"
#define DEVICE_TYPE "omkaram"
#define DEVICE_ID "supriya7270"
#define TOKEN "priya7270"
String command;
char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char topic[] = "iot-2/cmd/home/fmt/String";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;
//Serial.println(clientID);

WiFiClient wifiClient;
void callback(char* topic, byte* payload, unsigned int payloadLength);
PubSubClient client(server, 1883, callback, wifiClient);

void setup() {
  Serial.begin(115200);
  Serial.println();
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  wifiConnect();
  mqttConnect();
}

void loop() {
  if (!client.loop()) {
    mqttConnect();
  }
delay(100);
}

void wifiConnect() {
  Serial.print("Connecting to "); Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("nWiFi connected, IP address: "); Serial.println(WiFi.localIP());
}

void mqttConnect() {
  if (!client.connected()) {
    Serial.print("Reconnecting MQTT client to "); Serial.println(server);
    while (!client.connect(clientId, authMethod, token)) {
      Serial.print(".");
      delay(500);
    }
    initManagedDevice();
    Serial.println();
  }
}
void initManagedDevice() {
  if (client.subscribe(topic)) {
    Serial.println("subscribe to cmd OK");
  } else {
    Serial.println("subscribe to cmd FAILED");
  }
}

void callback(char* topic, byte* payload, unsigned int payloadLength) {
  Serial.print("callback invoked for topic: "); Serial.println(topic);

  for (int i = 0; i < payloadLength; i++) {
    //Serial.println((char)payload[i]);
    command += (char)payload[i];
  }
Serial.println(command);
if(command == "lighton"){
  digitalWrite(D1,HIGH);
  Serial.println("Light is Switched ON");
}
else if(command == "lightoff"){
  digitalWrite(D1,LOW);
  Serial.println("Light is Switched OFF");
}
if(command == "fanon"){
  digitalWrite(D2,HIGH);
  Serial.println("Fan is Switched ON");
}
else if(command == "fanoff"){
  digitalWrite(D2,LOW);
  Serial.println("Fan is Switched OFF");
}
if(command == "allon"){
  digitalWrite(D1,HIGH);
  digitalWrite(D2,HIGH);
  Serial.println("Light and fan are Switched ON");
  
}
else if(command == "alloff"){
  digitalWrite(D1,LOW);
  digitalWrite(D2,LOW);
  Serial.println("Light and fan are Switched OFF");
}
command ="";
}
