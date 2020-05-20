// include the library code:
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

const int rs = PB11, en = PB10, d4 = PA4, d5 = PA3, d6 = PA2, d7 = PA1; //STM32 Pins to which LCD is connected
int isObstacle = 0;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //Initialize the LCD

void setup() {
  lcd.begin(40, 2);
  lcd.setCursor(0, 0); 
  lcd.print("I2C Scanner");
  lcd.setCursor(0, 1); 
  lcd.print("Starting scan...");
  delay (3000);
  Wire.begin();
}

void loop() {
 
  int nDevices;
  byte error, address;  

     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("Scanning I2C bus...");
	   delay (3000);
	   nDevices = 0;

	   for(address = 0; address < 128; address++ )

	   {
	     // The i2c_scanner uses the return value of
	     // the Write.endTransmisstion to see if
	     // a device did acknowledge to the address.

	     Wire.beginTransmission(address);
       error = Wire.endTransmission();

	     if (error == 0)
  	    {
          lcd.print(" Address is - 0x");
          if (address<16) 
            lcd.print("0");
         lcd.print(address,HEX);      
         nDevices++;
	      }

        else if (error==4) 
	      {
          lcd.print("Unknown error at address 0x");
          if (address<16) 
            lcd.print("0");
          lcd.print(address,HEX);
         }    
     
     }	   

	   if (nDevices == 0)

	      lcd.print("No I2C devices found\n");

	    else

	    {
        lcd.setCursor(0, 1);
	      lcd.print("Found ");
	      lcd.print(nDevices);
	      lcd.print(" device(s) ");
	    }

	   delay(3000);           // wait 5 seconds for next scan
  
}