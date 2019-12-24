/*
    NodeMCU RC522 RFID Card Access System
    * Taha SIVACI <info@tahasivaci.com> 2019
    * The Apprentice Magazine
    * Configuration: NodeMCU 1.0 (ESP-12E Module), 80 MHz (160 MHz optional),
    * 921600 Upload Speed, Flash, 4M (3M SPIFFS), Erase Flash: Only Sketch (Card version 2.4.2)
*/

#define SS_PIN D4 //SDA Pin
#define RST_PIN D3

int greenLed = D1;
int redLed = D2;

#include <SPI.h>
#include <MFRC522.h>

MFRC522 mfrc522(SS_PIN, RST_PIN);
int out = 0;

void setup()
{
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);

  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
}

void loop()
{
  // New cards scan
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // if the card was read
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  //Read the UID of the card and write to the serial port
  Serial.println();
  Serial.print(" UID etiketi :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.println();
  if (content.substring(1) == "2F 6F 10 G7") // Replace this UID with the value of the card you want to define.
  {
    Serial.println(" Login successful ! ");
    digitalWrite(greenLed, HIGH);
    delay(500);
    digitalWrite(greenLed, LOW);
    delay(1000);
  }

  else   {
    Serial.println("Card not recognized! ");
    digitalWrite(redLed, HIGH);
    delay(100);
    digitalWrite(redLed, LOW);
    delay(100);
    digitalWrite(redLed, HIGH);
    delay(100);
    digitalWrite(redLed, LOW);
    delay(100);
    digitalWrite(redLed, HIGH);
    delay(100);
    digitalWrite(redLed, LOW);
    delay(100);
    delay(3000);
  }
}
