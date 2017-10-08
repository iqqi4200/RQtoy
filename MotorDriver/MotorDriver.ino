//didn't test!!!!!
#include <SoftwareSerial.h>

#define PIN_LEFT_VREF 5
#define PIN_LEFT_INPUT_1 6
#define PIN_LEFT_INPUT_2 7
#define PIN_STOP 8
#define PIN_RIGHT_INPUT_1 9
#define PIN_RIGHT_INPUT_2 10
#define PIN_RIGHT_VREF 11
#define PIN_Interrupt 2
#define IntteruptNumber 0
SoftwareSerial Arduino(3, 4);

unsigned char arduino_Command[4] = {0};
unsigned char arduino_Reply[4] = {0};
String INPUT_COMMADN;
String PWM;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Arduino.begin(9600);
  arduino_Command[0] = 0xBB;
  init_Pin();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Arduino.available())
  {
    int aa = 4;
             Arduino.readBytesUntil('\r', arduino_Reply, 4);
    for (int i = 0; i < 4; i++)
    {
      Serial.println(arduino_Reply[i]);
    }
    MOTOR_COMMAND();
  }

}
void init_Pin()
{
  pinMode( PIN_LEFT_VREF, OUTPUT);
  pinMode( PIN_LEFT_INPUT_1, OUTPUT);
  pinMode( PIN_LEFT_INPUT_2, OUTPUT);
  pinMode( PIN_STOP, OUTPUT);
  pinMode( PIN_RIGHT_INPUT_1, OUTPUT);
  pinMode( PIN_RIGHT_INPUT_2, OUTPUT);
  pinMode( PIN_RIGHT_VREF, OUTPUT);
  pinMode( PIN_Interrupt, INPUT);
  digitalWrite( PIN_LEFT_VREF, LOW);
  digitalWrite( PIN_RIGHT_INPUT_1, LOW);
  digitalWrite( PIN_LEFT_INPUT_1, LOW);
  digitalWrite( PIN_LEFT_INPUT_2, LOW);
  digitalWrite( PIN_STOP, HIGH);
  digitalWrite( PIN_RIGHT_INPUT_1, LOW);
  digitalWrite( PIN_RIGHT_INPUT_2, LOW);
  digitalWrite( PIN_RIGHT_VREF, LOW);
  attachInterrupt(IntteruptNumber, FinalMethod, RISING);
}
void FinalMethod()
{
  if (digitalRead(PIN_Interrupt))
  {
    digitalWrite(PIN_RIGHT_INPUT_1, LOW);
    digitalWrite(PIN_RIGHT_INPUT_2, LOW);
    digitalWrite( PIN_LEFT_INPUT_1, LOW);
    digitalWrite( PIN_LEFT_INPUT_2, LOW);
  }

}
void MOTOR_COMMAND()
{
  if (arduino_Reply[0] == 0xA0 && arduino_Reply[1] == 0x02)
  {
    int Vref = arduino_Reply[3];
    if (arduino_Reply[2] == 0x01)
    {
      //foward
      digitalWrite( PIN_RIGHT_INPUT_1, LOW);
      digitalWrite( PIN_RIGHT_INPUT_2, HIGH);
      analogWrite( PIN_RIGHT_VREF, Vref);
      Serial.println("u're in right_on_forward");
    } else if (arduino_Reply[2] == 0x02)
    {
      digitalWrite( PIN_RIGHT_INPUT_1, HIGH);
      digitalWrite( PIN_RIGHT_INPUT_2, LOW);
      analogWrite( PIN_RIGHT_VREF, Vref);
      //Serial.println("u're in right_on_back");
    } else
    {
      digitalWrite( PIN_RIGHT_INPUT_1, LOW);
      digitalWrite( PIN_RIGHT_INPUT_2, LOW);
      //Serial.println("u're in right_off");
    }

  }
}

