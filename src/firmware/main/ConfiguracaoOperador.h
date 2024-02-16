#ifndef CONFIGURACAO_OPERADOR_H
#define CONFIGURACAO_OPERADOR_H

#include "cstdint"
#include "WiFi.h"

struct ConfiguracaoOperador{
  int limitePeso;
  WiFiServer server;
  const char* ssid;
  const char* password;
  const char* token;
  const char* deviceLabel;
  uint8_t DT;
  uint8_t SCK;
  uint8_t BUTTON_PIN;
  uint8_t RED_LED;
  uint8_t RGB_RED;
  uint8_t RGB_GREEN;
  uint8_t RGB_BLUE;
  uint8_t BME_ADDRESS;
  uint8_t LCD_ADDRESS;
  uint8_t SPEAKER_PIN;
  uint8_t BUTTON_TARE_PIN;
};

#endif