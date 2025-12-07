Nguyen Quang Minh - 0916254336
#  Anti-leakage System for Students on Buses
**(Hệ thống Cảnh báo Chống bỏ quên Học sinh trên Xe buýt)**

Dự án này là một hệ thống nhúng được xây dựng trên nền tảng Arduino Mega, nhằm mục đích giám sát và phát hiện sự hiện diện của học sinh còn lại trên xe buýt sau khi xe đã tắt máy. Hệ thống sử dụng kết hợp cảm biến siêu âm và cảm biến chuyển động để đưa ra cảnh báo chính xác.

##  Tính năng chính
- **Đo khoảng cách đa điểm:** Sử dụng 3 cảm biến siêu âm để quét các khu vực ghế ngồi khác nhau.
- **Phát hiện chuyển động:** Tích hợp cảm biến PIR để phát hiện chuyển động của người trong xe.
- **Hiển thị thông tin:** Hiển thị trực quan khoảng cách đo được và trạng thái có người/không có người lên màn hình LCD.
- **Mở rộng (Future):** Tích hợp Module SIM để gửi tin nhắn SMS cảnh báo đến tài xế/phụ huynh (Phần cứng đã sẵn sàng, đang cập nhật code).

##  Phần cứng yêu cầu
* **Vi điều khiển:** Arduino Mega 2560
* **Cảm biến khoảng cách:** 3 x HC-SR04
* **Cảm biến chuyển động:** 1 x PIR (HC-SR501)
* **Hiển thị:** 1 x LCD 1602 kèm module I2C
* **Module SIM:** SIM800L/SIM900A (Tùy chọn cho tính năng SMS)
* Dây cắm (Jumper wires) & Breadboard

##  Sơ đồ đấu nối (Pinout)

Hệ thống được kết nối với **Arduino Mega** theo sơ đồ chân sau:

| Linh kiện | Chân Linh Kiện | Chân Arduino Mega | Ghi chú |
| :--- | :--- | :--- | :--- |
| **LCD I2C** | SDA | **20** (SDA) | Địa chỉ I2C mặc định: `0x3F` |
| | SCL | **21** (SCL) | |
| | VCC | 5V | |
| | GND | GND | |
| **Cảm biến 1 (HC-SR04)** | Trig | **48** | |
| | Echo | **49** | |
| **Cảm biến 2 (HC-SR04)** | Trig | **50** | |
| | Echo | **51** | |
| **Cảm biến 3 (HC-SR04)** | Trig | **52** | |
| | Echo | **53** | |
| **Cảm biến PIR** | OUT | **46** | Cảm biến chuyển động |

##  Hướng dẫn Cài đặt & Nạp code

### 1. Cài đặt thư viện
Để chạy được dự án, bạn cần cài đặt thư viện cho màn hình LCD trong Arduino IDE:
1. Vào **Sketch** -> **Include Library** -> **Manage Libraries...**
2. Tìm kiếm và cài đặt thư viện: `LiquidCrystal_I2C` (của Frank de Brabander hoặc các thư viện tương thích).

### 2. Nạp chương trình
1. Kết nối Arduino Mega với máy tính.
2. Mở file `.ino` trong dự án.
3. Chọn Board: **Tools** -> **Board** -> **Arduino Mega or Mega 2560**.
4. Chọn đúng cổng COM.
5. Nhấn **Upload**.

##  Lưu ý quan trọng
- **Địa chỉ I2C:** Code đang thiết lập địa chỉ LCD là `0x3F`. Một số màn hình LCD trên thị trường sử dụng địa chỉ `0x27`. Nếu màn hình không hiển thị, hãy sửa dòng code sau:
  ```cpp
  LiquidCrystal_I2C lcd(0x27, 16, 2); // Đổi 0x3F thành 0x27
