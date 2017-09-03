/**************************************************************************
*                           Demo da Ingresso Rápido
* 
* Descrição: Leitor de RFID deve guardar informações do cliente. Na hora 
* da consumação, ele lê e a fatura é aumentada em relação ao produto 
* consumido.
* 
* Hardware utilizado:
*   1. 1 Leitor RFID RS522 (https://playground.arduino.cc/Learning/MFRC522)
*   2. 2 Displays de 7 segmentos (https://playground.arduino.cc/Main/SevenSegmentLibrary)
*   3. 1 Buzzer com breakaway board (https://www.arduino.cc/en/Reference/Tone)
*   
* Bibliotecas utilizadas:   
*   1. SPI - Serial peripheral interface (https://www.arduino.cc/en/Reference/SPI)
*   2. ArduinoThread (https://github.com/ivanseidel/ArduinoThread)
*   
* Ligação dos pinos da placa RFID:
*   SDA -> pino 10
*   SCK -> pino 13
*   MOSI -> pino 11
*   MISO -> pino 12
*   NC –> Não conectado
*   GND -> GND
*   RST -> pino 9
*   3V3 –> 3V3
*   
*   
*                           Autor: Victor Teodoro
*                           Área: Soluções Stone Co.
*                               Data: 02/09/17
****************************************************************************/

// Importa as bibliotecas do projeto
#include <Thread.h>
#include <ThreadController.h>
#include <MFRC522.h>
#include <SPI.h>

// Configura o leitor RFID
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Define os pinos usados
const int buzzerPin = 3;

// Define as notas disponíveis
enum noteFrequencies {
  DO = 262,
  RE = 294,
  MI = 330,
  FA = 349,
  SOL = 392,
  LA = 432,
  SI = 495  
};

void setup() {
  // Inicia a porta serial
  Serial.begin(9600);

  // Define a função dos pinos digitais
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  // Configura o RFID e avisa o usuário
  SPI.begin();    // Inicia  SPI bus
  mfrc522.PCD_Init(); // Inicia MFRC522
  //Serial.print("Aproxime o seu cartao do leitor...\n");
}

void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }

  // Lê a tag e envia sua UID para a serial
  readRFIDTag();
}

void readRFIDTag(){
  //Mostra UID na serial
  //Serial.print("UID da tag :");
  String conteudo = "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     //Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  conteudo.toUpperCase();
  if (conteudo.substring(1) == "70 59 FD 73") //UID 1 - Chaveiro
  {
    Serial.print(conteudo.substring(1));
    tone(buzzerPin, FA, 500);
    delay(3000);
  }
 
  else
  {
    Serial.println("Ola Cartao " + conteudo.substring(1) + "!");
    Serial.println("Acesso negado!");
    tone(buzzerPin, DO, 500);
    delay(3000);
  }  
}
