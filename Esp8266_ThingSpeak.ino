#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <WiFiClient.h>
#define RX_PIN D3  // Define the RX pin
#define TX_PIN D2  // Define the TX pin

SoftwareSerial uart(RX_PIN, TX_PIN); 
WiFiClient client;

const char *ssid = "Airtel_suja_8425";
const char *password = "air67005";
long myChannelNumber = 2436746;
const char myWriteAPIKey[] = "06WQOVKLQPXCCCJ5";

struct SensorData
{
  float temp_data;
	float humid_data;
	int mq_data;
	int ir_data;
	int sound_data;
}S_Data;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  uart.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
   // Serial.print("..");
  }
  Serial.println("WiFi is connected!");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (uart.available() >= sizeof(SensorData)) {
    SensorData S_Data;
    uart.readBytes((char*)&S_Data, sizeof(SensorData));
    Serial.println("----------!!!!!!!!!!!!!!!!!!!------------");
    
    int gas = S_Data.mq_data;
    Serial.print("MQ-5 Sensor Data-: ");
    Serial.println(S_Data.mq_data);
    Serial.println("-------------------------");

    int IR = S_Data.ir_data;
    Serial.print("IR Sensor Data-: ");
    Serial.println(S_Data.ir_data);
    Serial.println("-------------------------");
    
    int sound = S_Data.sound_data;
    Serial.print("Sound Sensor Data-: ");
    Serial.println(S_Data.sound_data);
    Serial.println("-------------------------");

    float  temp = S_Data.temp_data;
    Serial.print("DHT22 Temp Data-: ");
    Serial.println(S_Data.temp_data);

    float  humid = S_Data.humid_data;
    Serial.print("DHT22 Humidity Data-: ");
    Serial.println(S_Data.humid_data);
    Serial.println("----------!!!!------------");
 
    ThingSpeak.writeField(myChannelNumber, 3, sound, myWriteAPIKey);
    ThingSpeak.writeField(myChannelNumber, 1, gas, myWriteAPIKey);
    ThingSpeak.writeField(myChannelNumber, 4, temp, myWriteAPIKey);
    ThingSpeak.writeField(myChannelNumber, 5, humid, myWriteAPIKey);
    ThingSpeak.writeField(myChannelNumber, 2, IR, myWriteAPIKey);

    delay(1000);
  }
}
