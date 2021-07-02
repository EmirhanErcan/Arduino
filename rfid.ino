#include <LiquidCrystal.h>
#include <MFRC522.h>
#include <SPI.h>
#include <Servo.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
int RST_PIN = 9;                          
int SS_PIN = 10;                         
int servoPin = 8;                        

Servo motor;                            
MFRC522 rfid(SS_PIN, RST_PIN);          
//byte ID[4] = {71, 254, 179, 96}; 
byte ID[4] = {217, 52, 249, 179 };


void setup() { 
  motor.attach(servoPin);                
  Serial.begin(9600);                     
  SPI.begin();                           
  rfid.PCD_Init();
  lcd.begin(16, 2); 
  lcd.setCursor(4, 0);
  lcd.print("CLOSED!");
  lcd.cursor();
  delay(500);
  lcd.noCursor();
  delay(500);
                      
}
 
void loop() {

  if ( ! rfid.PICC_IsNewCardPresent())  
    return;
    
  if ( ! rfid.PICC_ReadCardSerial())     
    return;
    
  if (rfid.uid.uidByte[0] == ID[0] &&     
    rfid.uid.uidByte[1] == ID[1] && 
    rfid.uid.uidByte[2] == ID[2] && 
    rfid.uid.uidByte[3] == ID[3] ) {
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("WELCOME HOME");
        lcd.setCursor(5, 1);
        lcd.print("BOSS!");
        Serial.println("THE DOOR IS OPEN");
        prtSc(); 
        delay(250);
        motor.write(270);                 
        delay(1500);
        motor.write(0);                 
        delay(1500);
        lcd.clear();
        lcd.setCursor(4, 0);
      lcd.print("CLOSED!");
      lcd.cursor();
      delay(500);
      lcd.noCursor();
      delay(500);
        
    }
    else{                                
      Serial.println("UNAUTHORIZED ENTRY");
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("UNAUTHORIZED");
      lcd.setCursor(5, 1);
      lcd.print("ENTRY!");
       delay(1500);
       lcd.clear();
       lcd.setCursor(4, 0);
      lcd.print("CLOSED!");
      lcd.cursor();
     delay(500);
      lcd.noCursor();
      delay(500);
      prtSc();
    }
  rfid.PICC_HaltA();
}
void prtSc(){
  Serial.print("ID Number: ");
  for(int counter = 0; counter < 4; counter++){
    Serial.print(rfid.uid.uidByte[counter]);
    Serial.print(" ");
  }
Serial.println("");
}
