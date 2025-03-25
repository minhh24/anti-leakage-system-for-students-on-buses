#include<Wire.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
#define trig1 48
#define echo1 49
#define trig2 50
#define echo2 51
#define trig3 52
#define echo3 53
unsigned long duration1; // biến đo thời gian
    int distance1;           // biến lưu khoảng cách
    unsigned long duration2; // biến đo thời gian
    int distance2;      // biến lưu khoảng ciách
    unsigned long duration3; // biến đo thời gian
    int distance3;      // biến lưu khoảng ciách
    int PIR = 46;
void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.clear();
    Serial.begin(9600);     // giao tiếp Serial với baudrate 9600
    pinMode(trig1,OUTPUT);   // chân trig sẽ phát tín hiệu
    pinMode(echo1,INPUT);    // chân echo sẽ nhận tín hiệu
    pinMode(trig2,OUTPUT);   // chân trig sẽ phát tín hiệu
    pinMode(echo2,INPUT);    // chân echo sẽ nhận tín hiệu
    pinMode(trig3,OUTPUT);   // chân trig sẽ phát tín hiệu
    pinMode(echo3,INPUT);    // chân echo sẽ nhận tín hiệu
    pinMode(PIR, INPUT);
}

void loop()
{
    docb1();
    docb2();
    docb3();
    Serial.print(distance1);
    Serial.println("cm");
    Serial.print(distance2);
    Serial.println("cm");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("1 ");
    lcd.print(distance1);
    lcd.setCursor(0,1);
    lcd.print("2 ");
    lcd.print(distance2);
    lcd.setCursor(8,0);
    lcd.print("3 ");
    lcd.print(distance3);
    delay(800);
    int value = digitalRead(PIR);
    if(value == HIGH)
  {
lcd.setCursor(10,1);
lcd.print("cd");
}  else {
  lcd.setCursor(10,1);
  lcd.print("k cd");
}
}
void docb1()
{
    digitalWrite(trig1,0);   // tắt chân trig
    delayMicroseconds(2);
    digitalWrite(trig1,1);   // phát xung từ chân trig
    delayMicroseconds(5);   // xung có độ dài 5 microSeconds
    digitalWrite(trig1,0);   // tắt chân trig
    
    /* Tính toán thời gian */
    // Đo độ rộng xung HIGH ở chân echo. 
    duration1 = pulseIn(echo1,HIGH);  
    // Tính khoảng cách đến vật.
    distance1 = int(duration1/2/29.412);
}
void docb2()
{
    digitalWrite(trig2,0);   // tắt chân trig
    delayMicroseconds(2);
    digitalWrite(trig2,1);   // phát xung từ chân trig
    delayMicroseconds(5);   // xung có độ dài 5 microSeconds
    digitalWrite(trig2,0);   // tắt chân trig
    
    /* Tính toán thời gian */
    // Đo độ rộng xung HIGH ở chân echo. 
    duration2 = pulseIn(echo2,HIGH);  
    // Tính khoảng cách đến vật.
    distance2 = int(duration2/2/29.412);
}
void docb3()
{
    digitalWrite(trig3,0);   // tắt chân trig
    delayMicroseconds(2);
    digitalWrite(trig3,1);   // phát xung từ chân trig
    delayMicroseconds(5);   // xung có độ dài 5 microSeconds
    digitalWrite(trig3,0);   // tắt chân trig
    
    /* Tính toán thời gian */
    // Đo độ rộng xung HIGH ở chân echo. 
    duration3 = pulseIn(echo3,HIGH);  
    // Tính khoảng cách đến vật.
    distance3 = int(duration3/2/29.412);
}

