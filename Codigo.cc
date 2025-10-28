#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = ""; // Incluir senha na implementação física
const char* mqtt_server = "broker.hivemq.com"; // era "test.mosquitto.org"

WiFiClient WOKWI_Client; // cria um objeto wi-fi para comunicação
PubSubClient client(WOKWI_Client); // cria um objeto Cliente mqtt associado 

int led1 = 2;
int led2 = 15;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA); // ativa o modo cliente do wi-fi
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

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("WOKWI_Client")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void wifi_on() {
  if (WiFi.status() == WL_CONNECTED)
    digitalWrite(2, HIGH);
  else
    digitalWrite(2, LOW);
}

void broker_on() {
  if (client.connected())
    digitalWrite(15, HIGH);
  else
    digitalWrite(15, LOW);
}

void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();  
  broker_on();
  wifi_on();
  delay(10); 
}
