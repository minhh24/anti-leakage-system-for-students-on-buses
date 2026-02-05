#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Cấu hình module SIM (RX=2, TX=3)
SoftwareSerial mySerial(2, 3); 

// Cấu hình LCD (Địa chỉ thường là 0x27 hoặc 0x3F. Trong ảnh là 0x3F)
LiquidCrystal_I2C lcd(0x3F, 16, 2); 

// --- KHAI BÁO CHÂN CẢM BIẾN ---
#define trig1 42 // Chân trig 1
#define echo1 43 // Chân echo 1
#define trig2 44
#define echo2 45
#define trig3 46
#define echo3 47
#define trig4 48
#define echo4 49
#define trig5 50
#define echo5 51
#define trig6 52
#define echo6 53

// --- BIẾN TOÀN CỤC ---
unsigned long duration1; int distance1; // Biến thời gian và khoảng cách 1
unsigned long duration2; int distance2;
unsigned long duration3; int distance3;
unsigned long duration4; int distance4;
unsigned long duration5; int distance5;
unsigned long duration6; int distance6;

int led = 31;
int at = 30; // Chân kích hoạt báo động hoặc Relay
int inputPin = 4; // Chân ngõ tín hiệu vào (PIR)
int pirState = LOW; 
int val = 0;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600); // Giao tiếp với SIM800L
  
  pinMode(inputPin, INPUT);
  pinMode(at, OUTPUT);
  pinMode(led, OUTPUT);
  
  // Khởi tạo LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  // Khởi tạo chân cảm biến siêu âm
  pinMode(trig1, OUTPUT); pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT); pinMode(echo2, INPUT);
  pinMode(trig3, OUTPUT); pinMode(echo3, INPUT);
  pinMode(trig4, OUTPUT); pinMode(echo4, INPUT);
  pinMode(trig5, OUTPUT); pinMode(echo5, INPUT);
  pinMode(trig6, OUTPUT); pinMode(echo6, INPUT);
}

void loop() {
  // Đọc dữ liệu từ 6 cảm biến
  docb1();
  docb2();
  docb3();
  docb4();
  docb5();
  docb6();
  
  // Đọc cảm biến chuyển động (PIR)
  val = digitalRead(inputPin);
  
  // Hiển thị lên LCD (có thể cần chỉnh lại tọa độ cho đẹp mắt hơn)
  lcd.clear(); // Xóa màn hình trước khi in mới
  
  lcd.setCursor(0, 0); lcd.print(distance1);
  lcd.setCursor(5, 0); lcd.print(distance2);
  lcd.setCursor(10, 0); lcd.print(distance3);
  
  lcd.setCursor(0, 1); lcd.print(distance4);
  lcd.setCursor(5, 1); lcd.print(distance5);
  lcd.setCursor(10, 1); lcd.print(distance6);
  
  lcd.setCursor(14, 1);
  if (val == HIGH) {
    lcd.print("cd"); // Có chuyển động
  } else {
    lcd.print("k");  // Không chuyển động
  }
  
  delay(600); // Delay hiển thị
  
  // --- LOGIC XỬ LÝ BÁO ĐỘNG ---
  // Điều kiện kiểm tra: Nếu khoảng cách < 25cm HOẶC > 35cm (vùng bất thường) HOẶC có chuyển động
  if (distance1 < 25 || distance2 < 25 || distance3 < 25 || distance4 < 25 || distance5 < 25 || distance6 < 25 ||
      distance1 > 35 || distance2 > 35 || distance3 > 35 || distance4 > 35 || distance5 > 35 || distance6 > 35 || 
      val == HIGH) 
  {
      delay(1000); // Chờ xác nhận
      
      // Đọc lại lần nữa để chắc chắn (chống nhiễu)
      val = digitalRead(inputPin);
      docb1(); docb2(); docb3(); docb4(); docb5(); docb6();
      
      // Kiểm tra lại điều kiện lần 2
      if (distance1 < 25 || distance2 < 25 || distance3 < 25 || distance4 < 25 || distance5 < 25 || distance6 < 25 ||
          distance1 > 35 || distance2 > 35 || distance3 > 35 || distance4 > 35 || distance5 > 35 || distance6 > 35 || 
          val == HIGH)
      {
          // Vòng lặp chờ xử lý báo động
          while (distance1 < 25 || distance2 < 25 || distance3 < 25 || distance4 < 25 || distance5 < 25 || distance6 < 25 ||
                 distance1 > 35 || distance2 > 35 || distance3 > 35 || distance4 > 35 || distance5 > 35 || distance6 > 35 || 
                 val == HIGH)
          {
              goidien(); // Gọi điện thoại cảnh báo
              digitalWrite(led, HIGH); // Bật đèn báo
              
              // Kích hoạt chân 'at' (coi/relay)
              digitalWrite(at, HIGH);
              delay(200);
              digitalWrite(at, LOW);
              
              // Cập nhật lại giá trị cảm biến trong vòng lặp
              docb1(); docb2(); docb3(); docb4(); docb5(); docb6();
              val = digitalRead(inputPin);
              delay(1000);
          }
      }
  } 
  else 
  {
      // Trạng thái bình thường
      digitalWrite(at, LOW);
      delay(500);
      digitalWrite(led, LOW);
  }
}

// --- CÁC CHƯƠNG TRÌNH CON ĐỌC CẢM BIẾN ---

void docb1() {
  digitalWrite(trig1, LOW); delayMicroseconds(2);
  digitalWrite(trig1, HIGH); delayMicroseconds(5);
  digitalWrite(trig1, LOW);
  duration1 = pulseIn(echo1, HIGH);
  distance1 = int(duration1 / 2 / 29.412);
}

void docb2() {
  digitalWrite(trig2, LOW); delayMicroseconds(2);
  digitalWrite(trig2, HIGH); delayMicroseconds(5);
  digitalWrite(trig2, LOW);
  duration2 = pulseIn(echo2, HIGH);
  distance2 = int(duration2 / 2 / 29.412);
}

void docb3() {
  digitalWrite(trig3, LOW); delayMicroseconds(2);
  digitalWrite(trig3, HIGH); delayMicroseconds(5);
  digitalWrite(trig3, LOW);
  duration3 = pulseIn(echo3, HIGH);
  distance3 = int(duration3 / 2 / 29.412);
}

void docb4() {
  digitalWrite(trig4, LOW); delayMicroseconds(2);
  digitalWrite(trig4, HIGH); delayMicroseconds(5);
  digitalWrite(trig4, LOW);
  duration4 = pulseIn(echo4, HIGH);
  distance4 = int(duration4 / 2 / 29.412);
}

void docb5() {
  digitalWrite(trig5, LOW); delayMicroseconds(2);
  digitalWrite(trig5, HIGH); delayMicroseconds(5);
  digitalWrite(trig5, LOW);
  duration5 = pulseIn(echo5, HIGH);
  distance5 = int(duration5 / 2 / 29.412);
}

void docb6() {
  digitalWrite(trig6, LOW); delayMicroseconds(2);
  digitalWrite(trig6, HIGH); delayMicroseconds(5);
  digitalWrite(trig6, LOW);
  duration6 = pulseIn(echo6, HIGH);
  distance6 = int(duration6 / 2 / 29.412);
}

// --- CHƯƠNG TRÌNH CON GỌI ĐIỆN ---
void goidien() {
  // Lệnh AT để gọi điện
  mySerial.println("ATD+84963118387;"); // Số điện thoại trong ảnh
  Serial.println("dang goi");
  delay(7000); // Chờ 7 giây cho cuộc gọi kết nối
  mySerial.println();
}
