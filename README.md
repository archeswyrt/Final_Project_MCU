# Final Project MCU - Traffic Light Control System

## 📋 Mô tả dự án

Đây là một hệ thống điều khiển đèn giao thông (Traffic Light Control System) được phát triển trên microcontroller **STM32F103RB** (ARM Cortex-M3). Dự án sử dụng **HAL (Hardware Abstraction Layer)** và tích hợp nhiều thành phần phần cứng như nút nhấn (buttons), LCD I2C, đèn LED RGB, và bộ định thời mềm (software timer).

## 🎯 Tính năng chính

### 1. **Chế độ tự động (Auto Mode)**
   - Đèn giao thông tự động chuyển đổi giữa các trạng thái:
     - Đỏ ➜ Xanh ➜ Vàng ➜ Đỏ
     - Các thời gian sáng của mỗi màu có thể được cấu hình

### 2. **Chế độ thủ công (Manual Mode)**
   - Điều khiển trực tiếp màu đèn thông qua nút nhấn
   - Cho phép chuyển đổi thủ công giữa các trạng thái

### 3. **Cấu hình thời gian (Time Configuration)**
   - Cho phép thiết lập thời gian sáng cho từng màu đèn:
     - Thời gian đèn đỏ
     - Thời gian đèn xanh
     - Thời gian đèn vàng
   - Cấu hình được lưu trữ để sử dụng lại

### 4. **Hiển thị LCD**
   - Màn hình LCD I2C hiển thị trạng thái hiện tại
   - Cập nhật thông tin thời gian và chế độ hoạt động

### 5. **Xử lý nút nhấn (Button Handling)**
   - 3 nút nhấn với khả năng phát hiện:
     - Nhấn bình thường (single press)
     - Nhấn dài (long press)
   - Chống dội (debouncing) tích hợp

### 6. **Hệ thống định thời mềm (Software Timer)**
   - Timer không phụ thuộc vào hardware timer
   - Cho phép quản lý các sự kiện theo thời gian

### 7. **Bộ lập lịch tác vụ (Scheduler)**
   - Quản lý các tác vụ định kỳ
   - Chia sẻ tài nguyên CPU hiệu quả

## 🏗️ Cấu trúc dự án

```
Final_Project_MCU/
├── Core/
│   ├── Inc/                          # Các file header
│   │   ├── main.h                    # File chính
│   │   ├── traffic_light.h           # Quản lý trạng thái đèn giao thông
│   │   ├── buttons.h                 # Xử lý các nút nhấn
│   │   ├── i2c_lcd.h                 # Giao tiếp LCD qua I2C
│   │   ├── tasks.h                   # Định nghĩa các tác vụ
│   │   ├── scheduler.h               # Bộ lập lịch tác vụ
│   │   ├── software_timer.h          # Bộ định thời mềm
│   │   ├── global.h                  # Biến và hằng số toàn cục
│   │   └── stm32f1xx_hal_conf.h      # Cấu hình HAL
│   └── Src/                          # Các file source
│       ├── main.c                    # Chương trình chính
│       ├── traffic_light.c           # Triển khai FSM đèn giao thông
│       ├── buttons.c                 # Triển khai xử lý nút nhấn
│       ├── i2c_lcd.c                 # Triển khai giao tiếp LCD
│       ├── tasks.c                   # Các tác vụ chính
│       ├── scheduler.c               # Triển khai bộ lập lịch
│       ├── software_timer.c          # Triển khai timer mềm
│       └── global.c                  # Khởi tạo biến toàn cục
├── Drivers/                          # Các driver STM32
│   ├── CMSIS/                        # CMSIS (Cortex Microcontroller Software Interface Standard)
│   └── STM32F1xx_HAL_Driver/        # HAL Driver cho STM32F1
├── Debug/                            # Thư mục build (sản sinh tự động)
└── README.md                         # File tài liệu này
```

## 🔧 Thành phần phần cứng được sử dụng

| Thành phần | Mô tả |
|-----------|-------|
| **Microcontroller** | STM32F103RB (ARM Cortex-M3, 128KB Flash, 20KB RAM) |
| **LED Red/Green/Amber** | 3 LED RGB để hiển thị trạng thái đèn giao thông |
| **Buttons** | 3 nút nhấn để điều khiển (Button 0, 1, 2) |
| **LCD Display** | LCD 16x2 với giao tiếp I2C |
| **Timer** | TIM2 cho việc định thời |
| **UART** | USART2 cho debug (baud rate 115200) |
| **I2C** | I2C1 cho giao tiếp LCD |

## 📊 Sơ đồ trạng thái (State Machine)

Hệ thống sử dụng Finite State Machine (FSM) để quản lý các trạng thái của đèn giao thông:

```
┌─────────────────┐
│      INIT       │  (Khởi tạo hệ thống)
└────────┬────────┘
         │
    ┌────┴─────┬──────────────────┐
    │           │                  │
    ▼           ▼                  ▼
AUTO MODE    MANUAL MODE      CONFIG MODE
    │           │                  │
    ├─ RED_GREEN   ├─ RED_GREEN    ├─ RED_TIME_CONFIG
    ├─ RED_AMBER   ├─ RED_AMBER    ├─ AMBER_TIME_CONFIG
    ├─ GREEN_RED   ├─ GREEN_RED    └─ GREEN_TIME_CONFIG
    └─ AMBER_RED   └─ AMBER_RED
```

## 🚀 Cách sử dụng

### Yêu cầu
- STM32CubeIDE hoặc IDE tương thích
- STM32CubeMX (để sinh code và cấu hình MCU)
- Trình biên dịch ARM GCC
- ST-Link debugger để lập trình board

### Lập trình board
1. Kết nối ST-Link với board STM32F103RB
2. Mở project trong STM32CubeIDE
3. Build project: `Ctrl + B`
4. Lập trình: `Run` hoặc `Debug`

### Hoạt động tại runtime
- **Button 0**: Chuyển chế độ (Auto ↔ Manual ↔ Config)
- **Button 1**: Tăng giá trị (trong chế độ config hoặc chuyển trạng thái trong manual)
- **Button 2**: Giảm giá trị (trong chế độ config hoặc chuyển trạng thái trong manual)

## 💻 Mô-đun chính

### `traffic_light.c/h`
- Triển khai FSM cho đèn giao thông
- Định nghĩa các trạng thái và chuyển đổi
- Quản lý thời gian hiển thị của mỗi trạng thái

### `buttons.c/h`
- Xử lý đầu vào từ 3 nút nhấn
- Phát hiện nhấn bình thường và nhấn dài
- Chống dội phần cứng

### `i2c_lcd.c/h`
- Giao tiếp với LCD qua I2C
- Hiển thị thông tin trạng thái

### `scheduler.c/h`
- Quản lý các tác vụ định kỳ
- Phân chia CPU time cho các tác vụ

### `software_timer.c/h`
- Cung cấp timer không phụ thuộc hardware
- Hỗ trợ các sự kiện theo thời gian

### `tasks.c/h`
- Định nghĩa các tác vụ chính:
  - `blinkyLED()`: Nhất nhạp LED
  - `getButtons()`: Lấy trạng thái nút nhấn
  - `fsm()`: Chạy FSM chính
