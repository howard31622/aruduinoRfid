/**
* Read a card using a mfrc522 reader on your SPI interface
* Pin layout should be as follows (on Arduino Uno):
* MOSI: Pin 11 / ICSP-4
* MISO: Pin 12 / ICSP-1
* SCK: Pin 13 / ISCP-3
* SS: Pin 10
* RST: Pin 9
*
* Script is based on the script of Miguel Balboa. 
* New cardnumber is printed when card has changed. Only a dot is printed
* if card is the same.
*
* @version 0.1
* @author Henri de Jong
* @since 06-01-2013
*/

#include <SPI.h>
#include <RFID.h>
#include <Wire.h>
// LCD I2C Library，從這裡可以下載：
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN); 
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);   // 設定 LCD I2C 位址

// Setup variables:
    int serNum0;
    int serNum1;
    int serNum2;
    int serNum3;
    int serNum4;
    String saveNumAll;
    String saveNum0;
    String saveNum1;
    String saveNum2;
    String saveNum3;
    String saveNum4;

void setup()
{ 
  Serial.begin(9600);
  SPI.begin(); 
  rfid.init();
  Serial.println("Ready");
  lcd.begin(16,2);
  // 閃爍三次
  for(int i = 0; i < 3; i++) {
    lcd.backlight(); // 開啟背光
    delay(250);
    lcd.noBacklight(); // 關閉背光
    delay(250);
  }
  lcd.backlight();

  // 輸出初始化文字
  lcd.setCursor(0, 0); // 設定游標位置在第一行行首
  lcd.print("Hello !!!!");
  delay(1000);
  lcd.setCursor(0, 1); // 設定游標位置在第二行行首
  lcd.print("you can use card !!");
  
}

void loop()
{

    if (rfid.isCard()) {
        if (rfid.readCardSerial()) {
            if (rfid.serNum[0] != serNum0
                && rfid.serNum[1] != serNum1
                && rfid.serNum[2] != serNum2
                && rfid.serNum[3] != serNum3
                && rfid.serNum[4] != serNum4
            ) {
                /* With a new cardnumber, show it. */
                Serial.println(" ");
                Serial.println("Card found");
                serNum0 = rfid.serNum[0];
                serNum1 = rfid.serNum[1];
                serNum2 = rfid.serNum[2];
                serNum3 = rfid.serNum[3];
                serNum4 = rfid.serNum[4];
                saveNum0 = rfid.serNum[0];
                saveNum1 = rfid.serNum[1];
                saveNum2 = rfid.serNum[2];
                saveNum3 = rfid.serNum[3];
                saveNum4 = rfid.serNum[4];


                lcd.setCursor(0, 1);
                lcd.print("                ");
                saveNumAll = saveNum0+saveNum1+saveNum2+saveNum3+saveNum4;
                Serial.println(saveNumAll);
                lcd.setCursor(0, 1);
                lcd.print(saveNumAll);
                //Serial.println(" ");
                Serial.println("Cardnumber:");
                Serial.print("Dec: ");
                Serial.print(rfid.serNum[0],DEC);
                Serial.print(", ");
                Serial.print(rfid.serNum[1],DEC);
                Serial.print(", ");
                Serial.print(rfid.serNum[2],DEC);
                Serial.print(", ");
                Serial.print(rfid.serNum[3],DEC);
                Serial.print(", ");
                Serial.print(rfid.serNum[4],DEC);
                Serial.println(" ");

                Serial.print("Hex: ");
                Serial.print(rfid.serNum[0],HEX);
                Serial.print(", ");
                Serial.print(rfid.serNum[1],HEX);
                Serial.print(", ");
                Serial.print(rfid.serNum[2],HEX);
                Serial.print(", ");
                Serial.print(rfid.serNum[3],HEX);
                Serial.print(", ");
                Serial.print(rfid.serNum[4],HEX);
                Serial.println(" ");
             } else {
               /* If we have the same ID, just write a dot. */
               Serial.print(".");
             }
          }
    }

    rfid.halt();
}
