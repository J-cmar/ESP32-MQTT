#include <WiFi.h>
#include<PubSubClient.h>


#define PIN_LED 2
// the setup function runs once when you press reset or power the board

const char *ssid_Router = ""; //Enter the router name
const char *password_Router = ""; //Enter the router password
const char *mqtt_server = ""; //Enter ip address of MQTT server
const char *mqtt_topic = "ledProduct";

WiFiClient espClient;
PubSubClient client(espClient);


void setup() {
 // initialize digital pin LED_BUILTIN as an output.
  pinMode(PIN_LED, OUTPUT);

  Serial.begin(115200);
  delay(2000);
  Serial.println("Setup start");
  WiFi.begin(ssid_Router, password_Router);
  Serial.println(String("Connecting to ")+ssid_Router);
  while (WiFi.status() != WL_CONNECTED){
  delay(500);
  Serial.print(".");
  }
  Serial.println("\nConnected, IP address: ");
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Handle incoming messages
  String receivedPayload = "";
  for (int i = 0; i < length; i++) {
    receivedPayload += (char)payload[i];
  }
  Serial.println();

  if (receivedPayload.equals("1")) {
    digitalWrite(PIN_LED, HIGH);
  } else if (receivedPayload.equals("2")) {
    digitalWrite(PIN_LED, LOW);
  }
}

// the loop function runs over and over again forever
void loop() {
  if(client.connected() == false){
    reconnect();
  }
  client.loop();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to Broker...");
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      client.subscribe("ledProduct");
    } else {
      Serial.print("failed to connect");
      Serial.print(client.state());
      delay(1000);
    }
  }
}