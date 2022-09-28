#pragma once

#include <Arduino.h>

// Definición de los pines de la placa.

// Pines temporizador TPL5010
//---------------------------
#define TPL5010_DONE PIN_PC0
#define TPL5010_WAKE PIN_PC2

// Pines módulo LoRa RFM95W
//-------------------------
#define RFM95_DIO0 PIN_PC1
#define RFM95_DIO1 PIN_PC3
#define RFM95_RST PIN_PD6
#define RFM95_SS PIN_PA7
#define RFM95_SCK PIN_PA6
#define RFM95_MISO PIN_PA5
#define RFM95_MOSI PIN_PA4

// Pin LED interno de placa
//-------------------------
//#define LED_BUILTIN DD0
#define D0 PIN_PA0