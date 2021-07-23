#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <PubSubClient.h>

#include "group15NodeMCUcode.h";

/* Set these to your desired credentials. */
const char *ssid = "ChandimaWifi";//wifi ssid 
const char *password = "Chandi@1";//wifi password

//details about mqtt broker and the topics you are going to use
const char* mqtt_server = "test.mosquitto.org"; //using the mosquito broker
//const char* outTopic = "ENTC/EN2560/out/000001"; //we have to upload these to the mqtt client in the computer
const char* inTopic = "POS/EN2560/order";

const int output5 = 5;
const int output4 = 4;
const int output0 = 0;

ESP8266WebServer server(80);

WiFiClient espClient; //WifiClient Object to handle the wifi connection.(protocol stack)
PubSubClient client(espClient); //PubSubClient Object (MQTT protocl stack) runs on the WiFi Client object.


void webpage() {
  server.send(200, "text/html", group15NodeMCUcode);
}

void setup_wifi(){
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

//------------------------MQTT start--------------------

void callback(char* topic, byte* payload, unsigned int length) { //we use a callback function to do tasks after an event occurs. This function runs 
//  when you recieve a msg to the subscribed topic
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, HIGH);
    led();
  }else{
    digitalWrite(BUILTIN_LED, LOW);
  }

}

void reconnect() { 
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
//    we need a unique client id to connect to a
//    MQTT broker. To avoid collisions client ID is
//    randomized each time connections reset
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe(inTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

//----------------------------------MQTT end---------------------------------

void led(){
  for(int i=0; i<5; i++){
    digitalWrite(output5, HIGH);
    delay(500);
    digitalWrite(output5, LOW);
    digitalWrite(output4, HIGH);
    delay(500);
    digitalWrite(output4, LOW);
    digitalWrite(output0, HIGH);
    delay(500);
    digitalWrite(output0, LOW);
  }
}


void setup() {
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(output0, OUTPUT);
  delay(1000);
  setup_wifi();
  server.on("/", webpage);
  server.begin();
  client.setServer(mqtt_server, 1883); //setting up mqtt function
  client.setCallback(callback);
}

void loop() {
  server.handleClient();
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); 
//  this function handles incoming msges from the subscribed topic and
//  calls the callback function. If no data is recieved after a timeout,
//  function returns
  
}
