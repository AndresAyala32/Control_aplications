#include <Adafruit_ADS1X15.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);
Adafruit_ADS1015 ads;     

void setup(void)
{
  lcd.init(); 
  lcd.backlight();
  Serial.begin(9600);
  Serial.println("Hello!");
  pinMode(14,OUTPUT);
  pinMode(12,OUTPUT);

  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");


  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }
  lcd.setCursor(0,0);
  lcd.print("Memory val:");
  lcd.setCursor(0,1);
  lcd.print("ADC value:");
}

void loop(void)
{
  int16_t adc0, adc1, adc2, adc3;
  float volts0, volts1, volts2, volts3;

  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);

  volts0 = ads.computeVolts(adc0);
  volts1 = ads.computeVolts(adc1);
  volts2 = ads.computeVolts(adc2);
  volts3 = ads.computeVolts(adc3);

  Serial.print("AIN3: "); Serial.print(adc3); Serial.print("  "); Serial.print(volts3); Serial.println("V");
  lcd.setCursor(10,1);
  lcd.print("      ");
  lcd.setCursor(11,0);
  lcd.print("986");
  lcd.setCursor(10,1);
  lcd.print(adc3);
  if (adc3 >= 986){
    digitalWrite(14,HIGH);
    digitalWrite(12,HIGH);
  }
  else{
    digitalWrite(14,LOW);
    digitalWrite(12,LOW);
  }
  

  delay(100);
}
