 #include "Operador.h"

Operador::Operador(const ConfiguracaoOperador& config)
    : interfaceLCD(config.LCD_ADDRESS),
      leds(config.RED_LED, config.RGB_RED, config.RGB_GREEN, config.RGB_BLUE),
      configMQTT(config.server, config.ssid, config.password, config.token, config.deviceLabel, config.LCD_ADDRESS) {
  this->limitePeso        = config.limitePeso;
  this->DT                = config.DT;
  this->SCK               = config.SCK;
  this->BUTTON_PIN        = config.BUTTON_PIN;
  this->RED_LED           = config.RED_LED;
  this->RGB_RED           = config.RGB_RED;
  this->RGB_GREEN         = config.RGB_GREEN;
  this->RGB_BLUE          = config.RGB_BLUE;
  this->BME_ADDRESS       = config.BME_ADDRESS;
  this->LCD_ADDRESS       = config.LCD_ADDRESS;
  this->SPEAKER_PIN       = config.SPEAKER_PIN;
  this->BUTTON_TARE_PIN   = config.BUTTON_TARE_PIN;
  this->ssid              = config.ssid;
  this->password          = config.password;  
  this->token             = config.token;
  this->deviceLabel       = config.deviceLabel;
  this->server            = config.server;
  this->tempSensor        = Adafruit_BME280();
  this->cargaSensor       = HX711();
  this->cartaosd          = SDcard();
}

void Operador::iniciar() {
  // Iniciar o Serial
  Serial.begin(57600);
  Serial.println("Iniciando...");
  // Inicia o pino do botão
  pinMode(BUTTON_PIN, INPUT_PULLDOWN);
  // Inicia o pino de botão de tara
  pinMode(BUTTON_TARE_PIN, INPUT_PULLDOWN);
  // Inicia o pino do buzzer
  pinMode(SPEAKER_PIN, OUTPUT);
  // Iniciar o HX711
  cargaSensor.begin(DT, SCK);
  // Definindo a escala na qual a célula de carga trabalha
  cargaSensor.set_scale(223497);
  //Tara padrão da célula de carga
  cargaSensor.tare(444120);
  // Inicia o BME280
  tempSensor.begin(BME_ADDRESS);
  // Inicia as clasess
  interfaceLCD.iniciar();
  leds.iniciar();
  configMQTT.conectar();
  cartaosd.iniciar();
  interfaceLCD.escrever("Desligado", "Aperte o botao");
}

void Operador::executar() {
  // Caso seja apertado o botão de iniciar/interromper
  if (digitalRead(BUTTON_PIN) == HIGH) {
    // Inicia a função que lê os valores da célula de carga
    this->iniciarOuInterromperLeitura();
    delay(500);
  }
  this->leituraAtivada();
  this->estadoDaMaquina();
  configMQTT.executar();
}

void Operador::iniciarOuInterromperLeitura() {
  // Esse if verifica se a leitura está acontecendo ou não.
  if (!leituraAtiva){
    // Variável que identifica se está havendo leitura é tornada verdadeira e o led verde é aceso.
    leituraAtiva = true;
    // leds.rgbVerde();
  } else {
    // Torna a variável de leitura falsa, para que se para de executar a função de leiutra
    leituraAtiva = false;
    // Feedback visual para o usuário que a leitura foi interrompida, tanto através do lcd, como do led rgb acendendo vermelho. 
    interfaceLCD.escrever("Leitura", "Interrompida.");
    // leds.rgbVermelho();
    leds.desligarLED();
    // Zera a tara, caso o usuário tenha definido uma nova e queira reiniciá-la.
    cargaSensor.tare();
  }
}

std::pair<float, float> Operador::coletarDados() {
  // As variáveis guardam as leituras respectivamente do peso, através do hx711, e da temperatura através do bme280.
  float peso        = cargaSensor.get_units();
  float temperatura = tempSensor.readTemperature();
  // Impede de mostrar o peso negativo para o usuário.
  if (peso < 0){
    peso = 0;
  }
  return std::make_pair(peso, temperatura);
}

void Operador::leituraAtivada(){
  // Verifica se é permitida a realização de leitura de dados
  if (leituraAtiva) {
    std::pair<float, float> dados = this->coletarDados();
    // Caso o botão de tara seja pressionado, é realizada a nova tara da balança.
    if(digitalRead(BUTTON_TARE_PIN) == HIGH){
      cargaSensor.tare();
    }
    // Mostra no lcd, através da função as informações lidas pelos sensores
    interfaceLCD.exibirDados(dados.first, dados.second);
    
    char mass[10];
    char temperature[10];
    sprintf(temperature, "%.2f", dados.second);
    sprintf(mass, "%.2f", dados.first);
    cartaosd.appendFile(SD, "/fernando.txt", mass);
    cartaosd.appendFile(SD, "/fernando.txt", " kg;");
    cartaosd.appendFile(SD, "/fernando.txt", temperature);
    cartaosd.appendFile(SD, "/fernando.txt", " C\n");
    
    // Manda para o Ubidots e publica as informações sobre os labels: Temperatura e Peso
    configMQTT.publicar("Massa", "Temperatura", dados);
    // Caso o peso esteja superando o limite definido pelos engenheiros
    if (dados.first > limitePeso) {
      // Led vermelho é ligado, junto ao buzzer com uma intensidade 50.
      leds.ligarRedLED();
      analogWrite(SPEAKER_PIN,50);
    } else {
      analogWrite(SPEAKER_PIN,0);
      leds.desligarLED();
    }
  }
  delay(500);
}

void Operador::estadoDaMaquina(){
  if (cargaSensor.read() <= -18000){
    leds.rgbVermelho();
  } else {
    leds.rgbVerde();
  }
}