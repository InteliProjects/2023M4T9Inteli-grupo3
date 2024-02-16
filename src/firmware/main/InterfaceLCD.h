#ifndef INTERFACELCD_H
#define INTERFACELCD_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class InterfaceLCD {
  public:

    InterfaceLCD(uint8_t endereco);                   // Construtor da classe que recebe o endereço I2C do dispositivo LCD.
    void iniciar();                                   // Função responsável por acender a luz de fundo do LCD.
    void escrever(String linha1, String linha2);      // Função capaz de escrever nas duas linhas do LCD as String passadas em seu parâmetro. 
    void exibirDados(float peso, float temperatura);  // Função que exibe as medições feitas pelos sensores instalados  
  
  private:
    uint8_t lcd_cols = 16;                            // Quantidade de colunas no LCD
    uint8_t lcd_rows = 2;                             // Quantidade de linhas no LCD
    uint8_t endereco;                                 // Endereço I2C do LCD
    LiquidCrystal_I2C lcd;                            // Objeto da biblioteca LiquidCrystal_I2C 

};

#endif