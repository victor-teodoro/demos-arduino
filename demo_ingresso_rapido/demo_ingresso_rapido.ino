/********************************************
*         Demo da Ingresso Rápido
* 
* Leitor de RFID deve guardar informações
* do cliente. Na hora da consumação, ele lê
* e a fatura é aummentada em relação ao 
* produto consumido.
* 
* Autor: Victor Teodoro
* Data: 02/09/17
**********************************************/

// Declara as constantes a serem usadas no programa
const int led = 13;
const int blink_time_ms = 1000;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {
  // Pisca o led 13 por 1000ms
  blink_led(led, 1000);
}

void blink_led(const int led_pin, const int time_ms) {
    
}
