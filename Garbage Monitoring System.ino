#include <ESP8266WiFi.h>

#define echoPin D7 // Echo Pin for Ultrasonic Sensor
#define trigPin D6 // Trigger Pin Ultrasonic Sensor
 
float duration, distance; // Duration used to calculate distance
 
 
const char* ssid = "MERCUSYS_BD20"; // WiFi name
const char* password = ""; // WiFi passward
const char* host = "iot-based-garbage-monitoring-system.000webhostapp.com"; //website hosting page url

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  //connecting wifi module to wifi
  WiFi.begin(ssid, password); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
}
void loop() {
  // The sensor is triggered by a HIGH pulse of 15 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  //Calculating the distance (in cm) based on the speed of sound.
  distance = duration/58.2;
  Serial.println(distance);
  //Delay 100ms before next reading.
  delay(100);
  //checking invalid measure
  if (isnan(distance)) {
    Serial.println("Failed to read from sensor!");
    return;
  }

  Serial.print("connecting to ");
  Serial.println(host);

  //building a tcp connection
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  //sending data to the hosting site by distance_cm and distance_inch variable
  String url = "/api/insert.php?distance_cm=" + String(distance) + "&distance_inch="+ String(distance*0.393701);
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(500);
  
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  //closing connection
  Serial.println();
  Serial.println("closing connection");
  delay(6000);
}
 
