/*
   TUTORIAL RELAY 3
   ON/OFFRELAY DENGAN IR REMOTE RECEIVER PADA ARDUINO

   D4 -> Led Merah
   D6 -> Led Biru

   VCC relay -> VCC
   GND relay -> GND
   IN RELAY -> SDA (atau sama dengan A4)

*/

#include "EcadioIRremote.h"

#define RECV_PIN 2//the SIG pin of Infrared Receiver is connected with D2 of OPEN-SMART UNO R3
#define biru 6
#define merah 4
#define pinRelay A4

IRrecv IR(RECV_PIN);
int statusLed = LOW;
int statusRelay = HIGH;


void setup()
{
  Serial.begin(115200);
  IR.enableIRIn(); // memulai receiver
  pinMode(biru, OUTPUT);
  pinMode(merah, OUTPUT);
  pinMode(pinRelay, OUTPUT);
  digitalWrite(pinRelay,HIGH);//mematikan relay saat awal, relay Active LOW dimatikan dengan HIGH
}

void loop()
{
  if (IR.decode()) {//kalau ada kode yang valid

    if (IR.isReleased())
    {
      digitalWrite(merah, HIGH);
      Serial.print("key code is ");
      Serial.println(IR.keycode, DEC);
      Serial.println("*************");

    }
    digitalWrite(merah, LOW);
    if (IR.keycode == 28) {
      statusLed = !statusLed; //kebalikan nya
      statusRelay = !statusRelay;
    }
    digitalWrite(biru, statusLed);
    digitalWrite(pinRelay, statusRelay);

    IR.resume(); //lanjutkan menerima sinyal IR lagi
  }
}
