/*
   ----------------------------------------------------------------------------
   This sketch uses the MFRC522 library ; see https://github.com/miguelbalboa/rfid
   for further details and other examples.

   NOTE: The library file MFRC522.h has a lot of useful info. Please read it.

   This sketch show a simple locking mechanism using the RC522 RFID module.
   ----------------------------------------------------------------------------
   Typical pin layout used:
   -----------------------------------------------------------------------------------------
               MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
               Reader/PCD   Uno           Mega      Nano v3    Leonardo/Micro   Pro Micro
   Signal      Pin          Pin           Pin       Pin        Pin              Pin
   -----------------------------------------------------------------------------------------
   RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
   SPI SS      SDA(SS)      10            53        D10        10               10
   SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
   SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
   SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15

*/
#define CAYENNE_DEBUG         // Uncomment to show debug messages
#define CAYENNE_PRINT Serial  // Comment this out to disable prints and save space

#include "CayenneDefines.h"
#include "BlynkSimpleEsp8266.h"
#include "CayenneWiFiClient.h"
#include <SPI.h>
#include <MFRC522.h>
char token[] = "y3nmeuc2l3";
// Your network name and password.
char ssid[] = "DI";
char password[] = "united007";

#define RST_PIN         D3           // Configurable, see typical pin layout above
#define SS_PIN          D8         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

String read_rfid;
String ok_rfid_1 = "452b85ab";
String ok_rfid_2 = "8525fab";
String ok_rfid_3 = "7e287b25";
String ok_rfid_4 = "559acd65";
//String ok_rfid_2="ffffffff"; //add as many as you need.




/*
   Initialize.
*/
void setup() {
  Serial.begin(9600);         // Initialize serial communications with the PC
  while (!Serial);            // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();                // Init SPI bus
  mfrc522.PCD_Init();         // Init MFRC522 card
  Cayenne.begin(token, ssid, password);

}

/*
   Helper routine to dump a byte array as hex values to Serial.
*/
void dump_byte_array(byte *buffer, byte bufferSize) {
  read_rfid = "";
  for (byte i = 0; i < bufferSize; i++) {
    read_rfid = read_rfid + String(buffer[i], HEX);
  }
}


void loop() {
  Cayenne.run();

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
    return;

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
    return;

  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);

}
CAYENNE_OUT(V1)
{
  
  if (read_rfid == ok_rfid_1) {
    Cayenne.virtualWrite(V1, "1");
   }
  else
  {
    Cayenne.virtualWrite(V1, "0");
  }
}
CAYENNE_OUT(V2)
{
  if (read_rfid == ok_rfid_2) {
    Cayenne.virtualWrite(V2, "1");
  }
   else
  {
    Cayenne.virtualWrite(V2, "0");
  }
}
CAYENNE_OUT(V3)
{
  if (read_rfid == ok_rfid_3) {
    Cayenne.virtualWrite(V3, "1");
  }
   else
  {
    Cayenne.virtualWrite(V3, "0");
  }
}
CAYENNE_OUT(V4)
{
  if (read_rfid == ok_rfid_4) {
    Cayenne.virtualWrite(V4, "1");
  }
   else
  {
    Cayenne.virtualWrite(V4, "0");
  }
}
