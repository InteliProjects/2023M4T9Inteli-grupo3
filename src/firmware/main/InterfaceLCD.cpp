#include "InterfaceLCD.h"

InterfaceLCD::InterfaceLCD(uint8_t endereco) : endereco(endereco), lcd(endereco, 16, 2) {}

void InterfaceLCD::iniciar() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Desligado.");
  lcd.setCursor(0, 1);
  lcd.print("Aperte o botao ");
}
void InterfaceLCD::escrever(String linha1, String linha2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(linha1);
  lcd.setCursor(0, 1);
  lcd.print(linha2);
}

void InterfaceLCD::exibirDados(float peso, float temperatura) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Peso: ");
  lcd.print(peso);
  lcd.print("  kg");
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperatura);
  lcd.print(" C");
}