#include "Operador.h"
#include "ConfiguracaoOperador.h"
#include "SDcard.h";


ConfiguracaoOperador config = {
  .limitePeso       = 4,                                          // Constante para o limite de peso
  
  // Configurações para o MQTT
  .server           = WiFiServer(80),                             // Servidor WiFi
  .ssid             = "",                                         // SSID da rede WiFi
  .password         = "",                                         // Senha da rede WiFi
  .token            = "BBUS-EWV8icKtOB8sJOCSzz1UpyRs0s24Lv",      // Token do Ubidots   
  .deviceLabel      = "iot",                                      // Label do dispositivo no Ubidots
  
  // Definição dos pinos  
  .DT               = 4,                                          // Pino DT
  .SCK              = 2,                                          // Pino SCK
  .BUTTON_PIN       = 25,                                         // Pino onde o botão está conectado
  .RED_LED          = 13,                                         // Pino do LED Vermelho
  .RGB_RED          = 14,                                         // Pino do LED Vermelho no RGB 
  .RGB_GREEN        = 32,                                         // Pino do LED Verde no RGB 
  .RGB_BLUE         = 33,                                         // Pino do LED Azul no RGB 
  .BME_ADDRESS      = 0x76,                                       // Endereço I2C do sensor BME280
  .LCD_ADDRESS      = 0x27,                                       // Endereço I2C do LCD
  .SPEAKER_PIN      = 27,                                         // Pino do Buzzer
  .BUTTON_TARE_PIN  = 26                                          // Pino do Botão de tara 
};

Operador operador(config); // Classe que é responsável pela interação dos demais objetos

void setup() {
  operador.iniciar();
}

void loop() {
  operador.executar();
}
