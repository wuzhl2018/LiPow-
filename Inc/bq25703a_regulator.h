/**
 ******************************************************************************
 * @file           : bq25703a_regulator.h
 * @brief          : Header for bq25703a_regulator.c file.
 ******************************************************************************
 */

#ifndef BQ25703A_REGULATOR_H_
#define BQ25703A_REGULATOR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32g0xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "cmsis_os.h"
#include "adc_interface.h"


#define I2C_TIMEOUT					(500 / portTICK_PERIOD_MS)

#define BQ26703A_I2C_ADDRESS		0xD6
#define BQ26703A_MANUFACTURER_ID	0x40
#define BQ26703A_DEVICE_ID			0x78

#define MANUFACTURER_ID_ADDR		0x2E
#define DEVICE_ID_ADDR				0x2F
#define MAX_CHARGE_VOLTAGE_ADDR		0x04
#define CHARGE_CURRENT_ADDR			0x02
#define CHARGE_OPTION_0_ADDR		0x00
#define MINIMUM_SYSTEM_VOLTAGE_ADDR	0x0D
#define CHARGE_STATUS_ADDR			0x20
#define ADC_OPTION_ADDR				0x3A
#define VBUS_ADC_ADDR				0x27
#define PSYS_ADC_ADDR				0x26
#define VSYS_ADC_ADDR				0x2D
#define VBAT_ADC_ADDR				0x2C
#define ICHG_ADC_ADDR				0x29
#define IDCHG_ADC_ADDR				0x28
#define IIN_ADC_ADDR				0x2B
#define IIN_DPM_ADDR				0x25
#define IIN_HOST_ADDR               0x0F

#define EN_LWPWR					0b0
#define EN_OOA						0b1

#define CHARGING_ENABLED_MASK		0b00000100
#define ADC_ENABLED_BITMASK			0b01010111
#define ADC_START_CONVERSION_MASK	0b01100000

//Max voltage register 1 values
#define MAX_VOLT_ADD_16384_MV		0b01000000
#define MAX_VOLT_ADD_8192_MV		0b00100000
#define MAX_VOLT_ADD_4096_MV		0b00010000
#define MAX_VOLT_ADD_2048_MV		0b00001000
#define MAX_VOLT_ADD_1024_MV		0b00000100
#define MAX_VOLT_ADD_512_MV			0b00000010
#define MAX_VOLT_ADD_256_MV			0b00000001

//Max voltage register 2 values
#define MAX_VOLT_ADD_128_MV			0b10000000
#define MAX_VOLT_ADD_64_MV			0b01000000
#define MAX_VOLT_ADD_32_MV			0b00100000
#define MAX_VOLT_ADD_16_MV			0b00010000

//Minimum system voltage register values
#define MIN_VOLT_ADD_8192_MV		0b00100000
#define MIN_VOLT_ADD_4096_MV		0b00010000
#define MIN_VOLT_ADD_2048_MV		0b00001000
#define MIN_VOLT_ADD_1024_MV		0b00000100
#define MIN_VOLT_ADD_512_MV			0b00000010
#define MIN_VOLT_ADD_256_MV			0b00000001

#define IIN_DPM_LSB_VALUE_MA		50
#define IIN_HOST_LSB_VALUE_MA		50

#define REG_ADC_MULTIPLIER			100000

#define VBUS_ADC_SCALE				(uint32_t)( 0.064 * REG_ADC_MULTIPLIER )
#define VBUS_ADC_OFFSET				(uint32_t)( 3.2 * REG_ADC_MULTIPLIER )

#define PSYS_ADC_SCALE				(uint32_t)( 0.012 * REG_ADC_MULTIPLIER )

#define VSYS_ADC_SCALE				(uint32_t)(0.064 * REG_ADC_MULTIPLIER)
#define VSYS_ADC_OFFSET				(uint32_t)(2.88 * REG_ADC_MULTIPLIER)

#define VBAT_ADC_SCALE				(uint32_t)(0.064 * REG_ADC_MULTIPLIER)
#define VBAT_ADC_OFFSET				(uint32_t)(2.88 * REG_ADC_MULTIPLIER)

#define ICHG_ADC_SCALE				(uint32_t)(0.064 * REG_ADC_MULTIPLIER)

#define IIN_ADC_SCALE				(uint32_t)(0.050 * REG_ADC_MULTIPLIER)

#define MAX_CHARGE_CURRENT_MA		8128
#define ASSUME_EFFICIENCY			0.95f
#define BATTERY_DISCONNECT_THRESH	(uint32_t)(4.215 * REG_ADC_MULTIPLIER)
#define MAX_CHARGING_POWER			100000
#define NON_USB_PD_CHARGE_POWER		2500
#define MAX_INPUT_CURRENT_MA        5000

#define TEMP_THROTTLE_THRESH_C		60
#define TEMP_FAN_THRESH_C			40
#define TEMP_FAN_HYSTER_C			5

uint8_t Get_Regulator_Connection_State(void);
uint8_t Get_Regulator_Charging_State(void);
uint32_t Get_VBAT_ADC_Reading(void);
uint32_t Get_VBUS_ADC_Reading(void);
uint32_t Get_PSYS_ADC_Reading(void);
uint32_t Get_Input_Current_ADC_Reading(void);
uint32_t Get_Charge_Current_ADC_Reading(void);
uint32_t Get_Max_Charge_Current(void);
uint32_t Get_Input_Current_Limit(void);
void vRegulator(void const *pvParameters);

/* Used to guard access to the I2C in case messages are sent to the UART from
 more than one task. */
extern SemaphoreHandle_t xTxMutex_Regulator;
osThreadId regulatorTaskHandle;

#endif /* BQ25703A_REGULATOR_H_ */
