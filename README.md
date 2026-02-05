# Anti-leakage System for Students on Buses
**Hệ thống Cảnh báo Chống bỏ quên Học sinh trên Xe buýt**



---

##  Giới thiệu 
Dự án này là một hệ thống nhúng được xây dựng trên nền tảng **Arduino Mega 2560**, nhằm mục đích giám sát và phát hiện sự hiện diện của học sinh còn lại trên xe buýt sau khi xe đã tắt máy. Hệ thống sử dụng kết hợp **cảm biến siêu âm** (Ultrasonic) và **cảm biến chuyển động** (PIR) để quét khoang xe và đưa ra cảnh báo chính xác, giúp ngăn chặn các tai nạn đáng tiếc do bỏ quên học sinh.

###  Tính năng chính (Key Features)
* **Đo khoảng cách đa điểm:** Sử dụng 03 cảm biến siêu âm HC-SR04 để quét các khu vực ghế ngồi khác nhau.
* **Phát hiện chuyển động:** Tích hợp cảm biến PIR (HC-SR501) để phát hiện chuyển động của người còn sót lại trong xe.
* **Hiển thị trực quan:** Màn hình LCD 1602 hiển thị khoảng cách đo được từ các cảm biến và trạng thái cảnh báo (Có người/Không có người).
* **Mở rộng (Future/WIP):** Tích hợp Module SIM (SIM800L/SIM900A) để gửi tin nhắn SMS/gọi điện cảnh báo đến tài xế và phụ huynh (Phần cứng đã sẵn sàng, tính năng đang được cập nhật).

---

##  Phần cứng yêu cầu 
| STT | Tên linh kiện | Số lượng | Ghi chú |
|:---:|:---|:---:|:---|
| 1 | **Arduino Mega 2560** | 1 | Vi điều khiển trung tâm |
| 2 | **Cảm biến siêu âm HC-SR04** | 3 | Đo khoảng cách |
| 3 | **Cảm biến chuyển động PIR HC-SR501** | 1 | Phát hiện chuyển động |
| 4 | **LCD 1602 kèm Module I2C** | 1 | Hiển thị thông tin |
| 5 | **Module SIM800L/SIM900A** | 1 | (Tùy chọn) Gửi SMS/Call |
| 6 | Breadboard & Dây cắm (Jumper wires) | 1 bộ | |

---

##  Sơ đồ đấu nối

Hệ thống được kết nối với **Arduino Mega 2560** theo sơ đồ chân dưới đây:

### 1. Màn hình LCD (I2C)
| Chân LCD | Chân Arduino Mega | Ghi chú |
|:---|:---|:---|
| **VCC** | 5V | |
| **GND** | GND | |
| **SDA** | **20 (SDA)** | Giao tiếp I2C |
| **SCL** | **21 (SCL)** | Giao tiếp I2C |

### 2. Cảm biến 
| Thiết bị | Chân thiết bị | Chân Arduino Mega |
|:---|:---|:---|
| **Cảm biến 1 (HC-SR04)** | Trig | **48** |
| | Echo | **49** |
| **Cảm biến 2 (HC-SR04)** | Trig | **50** |
| | Echo | **51** |
| **Cảm biến 3 (HC-SR04)** | Trig | **52** |
| | Echo | **53** |
| **Cảm biến PIR** | OUT | **46** |

---

##  Hướng dẫn Cài đặt & Nạp code 

### Bước 1: Cài đặt thư viện
Để biên dịch được dự án, bạn cần cài đặt thư viện điều khiển màn hình LCD I2C:
1. Mở **Arduino IDE**.
2. Đi đến menu: `Sketch` -> `Include Library` -> `Manage Libraries...`
3. Nhập từ khóa: `LiquidCrystal_I2C`.
4. Cài đặt thư viện của **Frank de Brabander** (hoặc tương đương).

### Bước 2: Cấu hình phần cứng
Kết nối các linh kiện theo bảng **Sơ đồ đấu nối** ở trên. Đảm bảo nguồn điện ổn định (đặc biệt nếu dùng thêm module SIM).

### Bước 3: Nạp chương trình
1. Kết nối Arduino Mega với máy tính qua cáp USB.
2. Mở file `.ino` của dự án.
3. Chọn Board: `Tools` -> `Board` -> `Arduino Mega or Mega 2560`.
4. Chọn đúng cổng COM kết nối.
5. Nhấn nút **Upload (->)**.

---

##  Lưu ý quan trọng 

### Vấn đề địa chỉ I2C của màn hình LCD
Mặc định trong mã nguồn đang thiết lập địa chỉ LCD là `0x3F`. Tuy nhiên, các màn hình trên thị trường thường có hai loại địa chỉ phổ biến là `0x3F` hoặc `0x27`.

### file báo cáo
https://drive.google.com/file/d/1NqSa-8jGalH_PaRdhCAoxCvVNpkKwT-r/view?usp=sharing

Nếu nạp code xong mà màn hình không hiển thị hoặc chỉ sáng đèn nền:
1. Tìm dòng code sau trong file `.ino`:
   ```cpp
   LiquidCrystal_I2C lcd(0x3F, 16, 2);
