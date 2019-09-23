// include the library code:
#include <LiquidCrystal.h>
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// define some values used by the panel and buttons
bool ban = true;
int read_LCD_buttons();
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"


// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
//MPU6050 accelgyro(0x69); // <-- use for AD0 high
int16_t prueba;
int16_t ax, ay, az;
int16_t gx, gy, gz;



// uncomment "OUTPUT_READABLE_ACCELGYRO" if you want to see a tab-separated
// list of the accel X/Y/Z and then gyro X/Y/Z values in decimal. Easy to read,
// not so easy to parse, and slow(er) over UART.
#define OUTPUT_READABLE_ACCELGYRO

// uncomment "OUTPUT_BINARY_ACCELGYRO" to send all 6 axes of data as 16-bit
// binary, one right after the other. This is very fast (as fast as possible
// without compression or data loss), and easy to parse, but impossible to read
// for a human.
//#define OUTPUT_BINARY_ACCELGYRO

void setup() {
    lcd.begin(16, 2);
    lcd.setCursor(0,0);
    // Print a message to the LCD.
    lcd.print("Hola");
    
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    
    // initialize serial communication
    // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
    // it's really up to you depending on your project)
    Serial.begin(38400);

    // initialize device
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
}

void loop() {
    lcd_key = read_LCD_buttons();  // read the buttons

   switch (lcd_key)               // depending on which button was pushed, we perform an action
   {
     case btnRIGHT:
       {
       Serial.println("Derecha");
       break;
       }
     case btnLEFT:
       {
       Serial.println("Izquierda");
       break;
       }
     case btnUP:
       {
       Serial.println("Saltar");
       break;
       }
     case btnDOWN:
       {
       Serial.println("Disparar");
       break;
       }
     case btnSELECT:
       {
        if(ban){ban=false;}
        else{ban=true;}
        delay(500);
       break;
       }
       case btnNONE:
       {
       break;
       }
   }

    if(ban){
      // read raw accel/gyro measurements from device
      accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
      ax = ax / 1000;
      ay = ay / 1000;
      az = az / 1000;
      gx = gx / 1000;
      gy = gy / 1000;
      gz = gz / 1000;
      // these methods (and a few others) are also available
      //accelgyro.getAcceleration(&ax, &ay, &az);
      //accelgyro.getRotation(&gx, &gy, &gz);
  
      #ifdef OUTPUT_READABLE_ACCELGYRO
  /*        // display tab-separated accel/gyro x/y/z values
          Serial.print("a/g:\t");
          Serial.print(ax); Serial.print("\t");
          Serial.print(ay); Serial.print("\t");
          Serial.print(az); Serial.print("\t");
          Serial.print(gx); Serial.print("\t");
          Serial.print(gy); Serial.print("\t");
          Serial.println(gz);*/
          if (ax > 8){Serial.println("Izquierda");}
          if (ax < -8){Serial.println("Derecha");}
          if (ay > 8){Serial.println("Saltar");}
      #endif
    }
}

// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 // For V1.1 us this threshold
 if (adc_key_in < 50)   return btnRIGHT;
 if (adc_key_in < 250)  return btnUP;
 if (adc_key_in < 450)  return btnDOWN;
 if (adc_key_in < 650)  return btnLEFT;
 if (adc_key_in < 850)  return btnSELECT;

 // For V1.0 comment the other threshold and use the one below:
/*
 if (adc_key_in < 50)   return btnRIGHT;
 if (adc_key_in < 195)  return btnUP;
 if (adc_key_in < 380)  return btnDOWN;
 if (adc_key_in < 555)  return btnLEFT;
 if (adc_key_in < 790)  return btnSELECT;
*/


 return btnNONE;  // when all others fail, return this...
}
