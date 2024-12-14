#include <HX711_ADC.h> // need to install
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // need to install

HX711_ADC LoadCell(6, 7); // parameters: dt pin 6, sck pin 7;
LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27 is the i2c address, might be different; you can check with Scanner

const int buzzerPin = 8; // pin where the buzzer is connected
const float weightThreshold = 5000.0; // 5 kg in grams

void setup() 
{ 
  Serial.begin(9600); // Start serial communication for debugging (optional)
  
  LoadCell.begin(); // start connection to HX711
  LoadCell.start(2000); // load cell gets 2000ms of time to stabilize
  LoadCell.setCalFactor(1000.0); // calibration factor for load cell => dependent on your individual setup
  
  lcd.begin();
  lcd.backlight();
  
  pinMode(buzzerPin, OUTPUT); // set buzzer pin as output
}

void loop() 
{
  float load, load1;
  LoadCell.update(); // retrieves data from the load cell
  float weight = LoadCell.getData(); // get output value
  load1 = (((weight*weight)/(weight)));
  load = (load1-0.01
  );
  Serial.println(load);
  
  lcd.setCursor(0, 0); // set cursor to first row
  lcd.print("Weight [kg]:"); // print out to LCD
  
  lcd.setCursor(0, 1); // set cursor to second row
  lcd.print(load); // print out the retrieved value to the second row

  
  if (load > weightThreshold) {
    tone(buzzerPin, 1000); // sound the buzzer with a 1 kHz tone
  } else {
    noTone(buzzerPin); // stop the buzzer
  }
  
  delay(100); // small delay to avoid rapid toggling
}