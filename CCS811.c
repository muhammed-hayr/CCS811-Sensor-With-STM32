/**
 ******************************************************************************
 * @file    CCS811.c
 * @brief   CCS811 Air Quality Sensor Driver Source (for STM32 & RAK3172)
 * @author  Muhammed KANJO
 * @version 1.0
 * @date    2025-07-09
 * @license MIT
 *
 * @note    Compatible with STM32 HAL drivers and RAK3172 (STM32WLE5)
 ******************************************************************************
 */

#include "CCS811.h"
#include <stdio.h>

/* Internal I2C handler */
static I2C_HandleTypeDef *ccs811_i2c;

/* Public variables to hold sensor readings */
uint16_t CO2_ppm = 0;
uint16_t TVOC_ppb = 0;

/**
 * @brief  Initialize the CCS811 sensor
 * @param  hi2c: Pointer to HAL I2C handle (e.g., &hi2c1 or &hi2c2)
 */
void CCS811_Init(I2C_HandleTypeDef *hi2c)
{
    ccs811_i2c = hi2c;

    // Check hardware ID
    if (!CCS811_CheckHardware())
    {
        printf("CCS811 not detected! Check wiring and I2C address.\r\n");
        while (1);
    }

    // Start application mode
    uint8_t cmd = CCS811_APP_START;
    HAL_I2C_Master_Transmit(ccs811_i2c, CCS811_I2C_ADDR, &cmd, 1, HAL_MAX_DELAY);
    HAL_Delay(100); // Allow app start
}

/**
 * @brief  Check CCS811 hardware ID (expected: 0x81)
 * @retval 1 if detected, 0 otherwise
 */
uint8_t CCS811_CheckHardware(void)
{
    uint8_t hw_id = 0;
    HAL_I2C_Mem_Read(ccs811_i2c, CCS811_I2C_ADDR, CCS811_HW_ID_REG,
                     I2C_MEMADD_SIZE_8BIT, &hw_id, 1, HAL_MAX_DELAY);
    return (hw_id == 0x81);
}

/**
 * @brief  Configure measurement mode
 * @param  mode: DRIVE_MODE (0–4)
 */
void CCS811_Configure(uint8_t mode)
{
    if (mode > DRIVE_MODE_RAW) mode = DRIVE_MODE_RAW;
    uint8_t meas_mode = mode << 4;
    HAL_I2C_Mem_Write(ccs811_i2c, CCS811_I2C_ADDR, CCS811_MEAS_MODE_REG,
                      I2C_MEMADD_SIZE_8BIT, &meas_mode, 1, HAL_MAX_DELAY);
}

/**
 * @brief  Check if new sensor data is available
 * @retval 1 if data ready, 0 otherwise
 */
uint8_t CCS811_DataAvailable(void)
{
    uint8_t status = 0;
    HAL_I2C_Mem_Read(ccs811_i2c, CCS811_I2C_ADDR, CCS811_STATUS_REG,
                     I2C_MEMADD_SIZE_8BIT, &status, 1, HAL_MAX_DELAY);
    return (status & 0x08);
}

/**
 * @brief  Read CO₂ (ppm) and TVOC (ppb) values
 */
void CCS811_ReadData(void)
{
    uint8_t data[4];
    HAL_I2C_Mem_Read(ccs811_i2c, CCS811_I2C_ADDR, CCS811_ALG_RESULT_DATA,
                     I2C_MEMADD_SIZE_8BIT, data, 4, HAL_MAX_DELAY);

    CO2_ppm = (data[0] << 8) | data[1];
    TVOC_ppb = (data[2] << 8) | data[3];
}

/**
 * @brief  Set environmental compensation data
 * @param  humidity: Relative humidity in %
 * @param  temperature: Temperature in °C
 */
void CCS811_SetEnvironmentalData(float humidity, float temperature)
{
    uint8_t env_data[4];
    uint16_t hum = (uint16_t)(humidity * 512 + 0.5);
    uint16_t temp = (uint16_t)((temperature + 25) * 512 + 0.5);

    env_data[0] = (hum >> 8) & 0xFF;
    env_data[1] = hum & 0xFF;
    env_data[2] = (temp >> 8) & 0xFF;
    env_data[3] = temp & 0xFF;

    HAL_I2C_Mem_Write(ccs811_i2c, CCS811_I2C_ADDR, CCS811_ENV_DATA_REG,
                      I2C_MEMADD_SIZE_8BIT, env_data, 4, HAL_MAX_DELAY);
}

/**
 * @brief  Perform software reset of the CCS811 sensor
 */
void CCS811_SoftwareReset(void)
{
    uint8_t reset_cmd[5] = {CCS811_RESET_REG, 0x11, 0xE5, 0x72, 0x8A};
    HAL_I2C_Master_Transmit(ccs811_i2c, CCS811_I2C_ADDR, reset_cmd, 5, HAL_MAX_DELAY);
    HAL_Delay(100);
}
