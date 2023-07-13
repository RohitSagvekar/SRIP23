
//Sketch for uploading to mosquitto


#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
#include <DHT.h>
#include <SD.h>
#include <TimeLib.h>

// Wi-Fi credentials
const char* WIFI_SSID = "Professor_RS";
const char* WIFI_PASSWORD = "11235813";

// MQTT broker details
const char* MQTT_SERVER = "35.226.208.187";
const int MQTT_PORT = 1883;
const char* MQTT_TOPIC = "your_topic";

// Create an instance of the Wi-Fi client
WiFiClient wifiClient;

// Create an instance of the MQTT client
PubSubClient mqttClient(wifiClient);

// Pin definitions
const int PMS_RX_PIN = D3;  // PMS5003 RX pin connected to NodeMCU D5 (GPIO14)
const int PMS_TX_PIN = D4;  // PMS5003 TX pin connected to NodeMCU D6 (GPIO12)

// DHT pin definitions
#define DHT_PIN D2
#define DHT_TYPE DHT11

// SD pin definitions
const int SD_CS_PIN = D8;  // Example: GPIO pin D8


DHT dht(DHT_PIN, DHT_TYPE);

// PMS5003 data structure
struct PMS5003Data {
  uint16_t pm1_0;
  uint16_t pm2_5;
  uint16_t pm10;
  float temperature;
  float humidity;
  char timeStamp;
};

PMS5003Data sensorData;

// SoftwareSerial for PMS5003
SoftwareSerial pmsSerial(PMS_RX_PIN, PMS_TX_PIN);


void setup() {
  Serial.begin(115200);

  dht.begin();

  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("Failed to initialize SD card module");
    return;
  }
  

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }

  Serial.println("Connected to Wi-Fi");

  // Set the MQTT server and callback functions
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setCallback(callback);

  // Connect to MQTT broker
  connectToMqttBroker();
  pmsSerial.begin(9600);

  // Set the time zone to IST (5 hours and 30 minutes ahead of GMT/UTC)
  configTime(0, 0, "pool.ntp.org");
  
}

void loop() {
  // Maintain the MQTT connection
  if (!mqttClient.connected()) {
    reconnectToMqttBroker();
  }
  mqttClient.loop();

  // Publish data to MQTT broker
  //publishData();



  if (readPMSData(&pmsSerial, &sensorData)) {
    // Print sensor data to Serial monitor
//    Serial.println("Sensor Data:");
//    Serial.print("PM1.0: ");
//    Serial.println(sensorData.pm1_0);
//    Serial.print("PM2.5: ");
//    Serial.println(sensorData.pm2_5);
//    Serial.print("PM10: ");
//    Serial.println(sensorData.pm10);
//    Serial.println();
  }
  
  //mqttClient.publish(MQTT_TOPIC, String(sensorData.temperature).c_str());
  //Serial.println("Published data: " + String(sensorData.pm2_5));

  time_t now = time(nullptr);
  now = now + 5 * 3600 + 30 * 60;

  // Convert Unix timestamp to human-readable date and time
  char buffer[30];
  snprintf(buffer, sizeof(buffer), "%s", ctime(&now));

  // Use the formatted date and time as needed
  Serial.println(buffer);

  publishData(sensorData);
  writeDataToSDCard(String(buffer));
    
  delay(1000); // Adjust the delay as needed
}

void connectToMqttBroker() {
  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT broker...");
    if (mqttClient.connect("NodeMCU_Client")) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void reconnectToMqttBroker() {
  Serial.println("Lost connection to MQTT broker. Reconnecting...");
  while (!mqttClient.connected()) {
    if (mqttClient.connect("NodeMCU_Client")) {
      Serial.println("Reconnected to MQTT broker");
    } else {
      Serial.print("Failed to reconnect to MQTT broker, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void publishData(const PMS5003Data& data) {
  // Convert the data to a JSON string
  String json = 
                "{\"pm1_0\":" + String(data.pm1_0) + ","
                "\"pm2_5\":" + String(data.pm2_5) + ","
                "\"pm10\":" + String(data.pm10) + ","
                "\"temperature\":" + String(data.temperature) + ","
                "\"humidity\":" + String(data.humidity) + "}";

  // Publish the data to the MQTT topic
  mqttClient.publish(MQTT_TOPIC, json.c_str());
  Serial.println("Published data: " + json);

  //Write data to the SD card
  writeDataToSDCard(json);
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Handle incoming MQTT messages if needed
  // This function will be called when a message is received
  // on a topic that the NodeMCU is subscribed to.
}

bool readPMSData(SoftwareSerial* serial, PMS5003Data* data) {
  if (serial->available() >= 32) {
    uint8_t buffer[32];
    serial->readBytes(buffer, 32);

    if (buffer[0] == 0x42 && buffer[1] == 0x4D) {
      data->pm1_0 = buffer[4] * 256 + buffer[5];
      data->pm2_5 = buffer[6] * 256 + buffer[7];
      data->pm10 = buffer[8] * 256 + buffer[9];

      // Read temperature and humidity
      data->temperature = dht.readTemperature();
      data->humidity = dht.readHumidity();
      
      return true;
    }
  }

  return false;
}

void writeDataToSDCard(const String& data) {
  File dataFile = SD.open("/data.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.println(data);
    dataFile.close();
    Serial.println("Data written to SD card");
  } else {
    Serial.println("Failed to open data file on SD card");
  }
}
