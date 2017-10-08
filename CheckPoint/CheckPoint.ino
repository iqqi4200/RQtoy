#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#define LED_PIN 11
#define Debug_Time
SoftwareSerial nodeMCU(4,5);  //wait for complete wifi to pc

unsigned char nodeMCU_Command[4] = {0}; //to arduino
unsigned char nodeMCU_Reply[4] = {0}; //from RPI
//check,forwording,space
const char* ssid = "abcd";
const char* password = "402370166";

const char* host = "172.20.10.2";
const int httpPort = 9527;

bool answer = true;
void setup() {
  // put your setup code here, to run once:
  nodeMCU.begin(9600);
  Serial.begin(115200);
  nodeMCU_Command[0] = 0xA0;
  Serial.print("Connecting to");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address:");
  Serial.println(WiFi.localIP());
}

void loop() {
  if(answer)Serial.print("Connecting to ");
  if(answer)Serial.println(host); //call one time if no timeout

  WiFiClient client;
  if(!client.connect(host, httpPort))
  {
    if(answer)Serial.println("connection failed");
    delay(2000);
    return;
  }
  if(answer)
  {
    client.print("here is nodeMCU");
    answer = false;
  }
  //before this line is default
  while(nodeMCU_Reply[0] != 0xFF)
  {
    client.readBytesUntil('\r',nodeMCU_Reply,3);
    #ifdef Debug_Time
    for(int i = 0; i < 4; i++)
    {
      Serial.println(nodeMCU_Reply[i]);
    }
    #endif
    if(nodeMCU_Reply[0] == 0xC0)
    {
      nodeMCU_Command[1] = nodeMCU_Reply[1];
      #ifdef Debug_Time
      Serial.println("The message from RPI send susscessful");
      #endif
      if(nodeMCU_Reply[1] == 0x01) //to talk
      {
        static int i = 5;
        while(i > 0)
        {
          client.print("I'm in talk mode");
          i--;
          delay(1000);
        }
      }else if(nodeMCU_Reply[1] == 0x02)
      {
        nodeMCU_Command[2] = nodeMCU_Reply[2];
        nodeMCU_Command[3] = nodeMCU_Reply[3];
        nodeMCU.write(nodeMCU_Command,sizeof(nodeMCU_Command));
      }
      
    }else {
      Serial.println("Didn't have the message");
    }
    unsigned long timeout = millis();
    while (client.available() == 0)
    {
      if (millis() - timeout > 12000)
      {
        Serial.println(">>> Client Timeout !");
        client.stop();
        answer = true;
        return;
      }
    }
  }
  
}





