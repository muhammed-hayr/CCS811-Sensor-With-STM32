/**
 ******************************************************************************
 * @file    CCS811.h
 * @brief   CCS811 Air Quality Sensor Driver Header (for STM32 & RAK3172)
 * @author  Muhammed KANJO
 * @version 1.0
 * @date    2025-07-09
 * @license MIT
 *
 * @note    Compatible with STM32 HAL drivers and RAK3172 (STM32WLE5)
 ******************************************************************************
 */

#ifndef __CCS811_H
#define __CCS811_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h" // Change to your MCU's HAL header

/** CCS811 I2C default address (shifted for HAL) */
#define CCS811_I2C_ADDR        (0x5A << 1)

/** CCS811 Register Map */
#define CCS811_STATUS_REG      0x00
#define CCS811_MEAS_MODE_REG   0x01
#define CCS811_ALG_RESULT_DATA 0x02
#define CCS811_ENV_DATA_REG    0x05
#define CCS811_BASELINE_REG    0x11
#define CCS811_HW_ID_REG       0x20
#define CCS811_APP_START       0xF4
#define CCS811_RESET_REG       0xFF

/** Measurement Modes */
#define DRIVE_MODE_IDLE        0x00
#define DRIVE_MODE_1SEC        0x01
#define DRIVE_MODE_10SEC       0x02
#define DRIVE_MODE_60SEC       0x03
#define DRIVE_MODE_RAW         0x04

/** Public variables */
extern uint16_t CO2_ppm;
extern uint16_t TVOC_ppb;

/** API Functions */
void CCS811_Init(I2C_HandleTypeDef *hi2c);
uint8_t CCS811_CheckHardware(void);
void CCS811_Configure(uint8_t mode);
uint8_t CCS811_DataAvailable(void);
void CCS811_ReadData(void);
void CCS811_SetEnvironmentalData(float humidity, float temperature);
void CCS811_SoftwareReset(void);

#ifdef __cplusplus
}
#endif

#endif /* __CCS811_H */
