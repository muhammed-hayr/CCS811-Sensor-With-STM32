# CCS811 STM32/RAK3172 Driver

A lightweight CCS811 air quality sensor driver written for STM32 microcontrollers and RAK3172 (STM32WLE5C) modules.

## 👤 Author
**Muhammed KANJO**

## 📦 Features
- Supports STM32 HAL (I2C1, I2C2)
- Works with RAK3172 (I2C2)
- Reads CO₂ (ppm) and TVOC (ppb)
- Environmental compensation (humidity & temperature)
- Clean, MIT-licensed, and ready for GitHub

## 🛠️ Hardware Connection
| CCS811 Pin | STM32 Pin    |
|------------|--------------|
| VCC        | 3.3V         |
| GND        | GND          |
| SDA        | I2C2_SDA     |
| SCL        | I2C2_SCL     |

---

## 📄 Usage

### 1️⃣ Initialize the sensor
```c
Init_I2C_CCS811();
configureCCS811();
