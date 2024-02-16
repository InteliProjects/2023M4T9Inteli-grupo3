#ifndef OPERADOR_H
#define OPERADOR_H

#include "ConfiguracaoOperador.h"
#include "Arduino.h"
#include "cstdint"
#include "InterfaceLCD.h"
#include "LEDs.h"
#include "ConfigMQTT.h"
#include "Adafruit_BME280.h"
#include "HX711.h"
#include "SDcard.h"

class Operador {
  public:
    Operador(const ConfiguracaoOperador& config); // Construtour que recebe um struct, o qual armazena todas as variáveis necessárias para a classe funcionar. 
    void iniciar();                               // Função para instanciar os objetos e realizar configurações base do projeto
    void executar();                              // Função a qual é repetida no loop, fazendo a medição através dos sensores.
  private:
    Adafruit_BME280 tempSensor;         // Objeto da biblioteca do sensor bme280
    HX711 cargaSensor;                  // Objeto da biblioteca do conversor HX711
    InterfaceLCD interfaceLCD;          // Objeto da classe InterfaceLCD, a qual controla um LiquidCrystal I2C 
    LEDs leds;                          // Objeto da classe LEDs, responsável por realizar a manipulação dos leds.
    ConfigMQTT configMQTT;              // Objeto da classe ConfigMQTT, o qual faz a conexão com o WiFi e sua publicação no ubidots.
    WiFiServer server;                  // Objeto da biblioteca WifiServer, responsável pela interação entre esp e WiFi
    SDcard cartaosd;                    // Objeto da classe SDcard, a qual realizar as modificações no cartão sd

    int limitePeso;                     // Variável responsável por definir a carga máxima de peso antes que o alarme seja ativado
    const char* ssid;                   // Variável que armazena o endereço ssid da rede que o esp será conectado.
    const char* password;               // Variável que armazena a senha da rede que o esp será conectado.
    const char* token;                  // Variável que armazena o token da conta do ubidots que será enviado os dados.
    const char* deviceLabel;            // Variável que armazena o "api-label" do device que receberá os dados.
    uint8_t DT;                         // Variável que armazena o endereço da porta DT, a qual realiza a transmissão de dados entre HX711
    uint8_t SCK;                        // Variável que armazena o endereço da porta SCK, a qual realiza a transmissão de dados entre HX711
    uint8_t BUTTON_PIN;                 // Variável que armazena a porta do esp32 em que o botão de inicializar está conectado.
    uint8_t RED_LED;                    // Variável que armazena a porta do esp32 em que o led vermelho está conectado.
    uint8_t RGB_RED;                    // Variável que armazena a porta do esp32 em que o canal vermelho do led RGB está conectado.
    uint8_t RGB_GREEN;                  // Variável que armazena a porta do esp32 em que o canal verde do led RGB está conectado.
    uint8_t RGB_BLUE;                   // Variável que armazena a porta do esp32 em que o canal vermelho do led RGB está conectado.
    uint8_t BME_ADDRESS;                // Variável que armazena o endereço I2C do sensor BME280.
    uint8_t LCD_ADDRESS;                // Variável que armazena o endereço I2C do display LCD.
    uint8_t SPEAKER_PIN;                // Variável que armazena a porta do esp32 em que o buzzer está conectado. 
    uint8_t BUTTON_TARE_PIN;            // Variável que armazena a porta do esp32 em que o botão de tara está conectado.

    bool leituraAtiva = false;          // Variável que armazena se está sendo mostrado os resultado das medições e se há envios para o ubidots

    void iniciarOuInterromperLeitura();       // Função responsável por ler o estado do botão de inicialização e verificar se foi iniciada/interrompida a leitura.
    std::pair<float, float> coletarDados();   // Função responsável por retornar as medições dos sensores instalados.
    void leituraAtivada();                    // Responsável por chamar a coletarDados e mostrar no dispositivo LCD
    void estadoDaMaquina();
};

#endif
