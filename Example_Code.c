
#include "CCS811.h"

extern I2C_HandleTypeDef hi2c2;

int main(void) {
    HAL_Init();
    CCS811_Init(&hi2c2);
    CCS811_Configure(DRIVE_MODE_1SEC);

    while (1) {
        if (CCS811_DataAvailable()) {
            CCS811_ReadData();
            printf("CO2: %u ppm, TVOC: %u ppb\r\n", CO2_ppm, TVOC_ppb);
        }
        HAL_Delay(1000);
    }
}
