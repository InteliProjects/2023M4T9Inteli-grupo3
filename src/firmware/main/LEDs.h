#ifndef LEDS_H
#define LEDS_H

#include <Arduino.h>

class LEDs {
  public:

    LEDs(int redLED, int rgbRed, int rgbGreen, int rgbBlue);
    void iniciar();           // Faz o setup dos Leds existentes, sendo eles o rgb e o led vermelho.
    void ligarRedLED();       // Liga o led vermelho, passando o valor High através da porta digital.
    void desligarLED();       // Desliga o led vermelho, passando o valor LOW através da porta digital.
    void rgbVermelho();       // Liga o Led RGB para que seja mostrada a cor vermelha através dele.
    void rgbVerde();          // Liga o Led RGB para que seja mostrada a cor verde através dele.
    void rgbAzul();           // Liga o Led RGB para que seja mostrada a cor azul através dele.
    void rgbBranco();         // Liga o Led RGB para que seja mostrada a cor branca através dele.
    void rgbMagenta();        // Liga o Led RGB para que seja mostrada a cor magenta através dele.
    void rgbAmarelo();        // Liga o Led RGB para que seja mostrada a cor amarela através dele.
    void rgbCiano();          // Liga o Led RGB para que seja mostrada a cor ciano através dele.
    void rgbOff();            // Desliga o led RGB, fazendo com que todos os canais recebam 0.  

  private:
    //Armazenam quais são as portas conectadas ao led vermelho e aos três canais do led RGB.
    int redLED;   
    int rgbRed;
    int rgbGreen;
    int rgbBlue;

};

#endif