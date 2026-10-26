
#include <WiFi.h>
#include <ThingSpeak.h>
#include <DHT.h>

const unsigned long channelNumber = 3551769;
const char* apiKey = "6AGNS0GMCIUNOWJS";
const char* universityID = "12323561";

DHT dht(15, DHT22);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin("Wokwi-GUEST", "");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.println("Wi-Fi connected!");
  ThingSpeak.begin(client);
}

void loop() {
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temp) || isnan(humidity)) {
    Serial.println("Sensor reading failed!");
    delay(20000);
    return;
  }

  ThingSpeak.setField(1, temp);
  ThingSpeak.setField(2, humidity);

  int status = ThingSpeak.writeFields(channelNumber, apiKey);

  Serial.print("University ID: ");
  Serial.println(universityID);

  Serial.print("Temperature: ");
  Serial.println(temp);

  Serial.print("Humidity: ");
  Serial.println(humidity);
  Serial.println(status == 200 ? "Upload successful!" : "Upload failed!");

  delay(20000);
}
