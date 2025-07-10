# CCS811 STM32/RAK3172 Driver

## 👤 Author
**Muhammed KANJO**

This is a lightweight C driver for the **CCS811 Air Quality Sensor**, supporting both:

✅ Generic **STM32 MCUs** (STM32F0/F1/F4/L0/L4/L1/WL series)  
✅ **RAK3172 LoRa Module** (STM32WLE5 based)

It allows reading **CO₂ (ppm)** and **TVOC (ppb)** values over I2C and printing them to UART.

---

## 📦 Features
- I2C communication with CCS811 (supports I2C1, I2C2, etc.)
- Automatic initialization and configuration (APP_START & Drive Mode)
- CO₂ and TVOC measurement retrieval
- Optional environmental data compensation (temperature & humidity)
- Works out-of-the-box on **RAK3172 (STM32WLE5)** and other STM32 boards

---

## 🔌 Hardware Connections

| CCS811 Pin | STM32 Pin (I2C2 Example) | RAK3172 Pin (I2C2) |
|------------|---------------------------|---------------------|
| VCC        | 3.3V                      | 3.3V                |
| GND        | GND                       | GND                 |
| SDA        | PB11                      | PB11 (I2C2 SDA)     |
| SCL        | PB10                      | PB10 (I2C2 SCL)     |

⚠️ Make sure to use 4.7kΩ pull-up resistors on SDA and SCL lines.

---

## 📄 Usage

### 1️⃣ Initialize the sensor
```c
Init_I2C_CCS811();
configureCCS811();
