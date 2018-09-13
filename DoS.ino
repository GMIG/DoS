#include <Ethernet.h>

IPAddress ip(10, 8, 4, 100);
IPAddress server(10, 8, 0, 123);

unsigned int localPort = 11213;     
EthernetClient client;
int sensorPin = 2;

byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte dns1[] = {  
  10, 0, 0, 10 };

byte gw[] = {  
  10, 8, 0, 1 };

byte sn[] = {  
  255, 255, 0, 0};

char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,


int prevSensorState = LOW;

void setup() {
  Ethernet.begin(mac,ip,dns1,gw,sn);
  Serial.begin(9600);
  delay(1000);
  pinMode(sensorPin, INPUT); 
  prevSensorState = digitalRead(sensorPin); 
}

void loop() {
  int sensorState = digitalRead(sensorPin); 
  if(sensorState == HIGH && prevSensorState == LOW){
     sendEvent();
     Serial.println(1);
  }
  else
      Serial.println(0);

prevSensorState = sensorState;
}


void sendEvent(){
  int res = client.connect(server, localPort);
  if (res) {
    Serial.println(1);
    client.println("SS-28-1:active");
    client.stop();
  } else {
    Serial.println("connection failed");
    Serial.println(res);
  }

}

