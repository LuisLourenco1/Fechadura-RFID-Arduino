#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MFRC522.h>
#include <Servo.h>

// Pinos de conexão
#define SS_PIN 10
#define RST_PIN 9
#define SERVO_PIN 3
#define LED_VERDE_PIN 4
#define LED_VERMELHO_PIN 5

// Inicialização dos componentes
LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 rfid(SS_PIN, RST_PIN);
Servo servo;

// UIDs dos cartões aceitos
byte uidLuis[] = {0xAA, 0xBB, 0xCC, 0xDD};
byte uidBel[] = {0xDD, 0xCC, 0xBB, 0xAA};

void setup() {
  // Inicialização do LCD
  lcd.begin(16, 2); // Adiciona o número de colunas e linhas
  lcd.backlight();
  
  // Inicialização do RFID
  SPI.begin();
  rfid.PCD_Init();
  
  // Configuração dos pinos dos LEDs
  pinMode(LED_VERDE_PIN, OUTPUT);
  pinMode(LED_VERMELHO_PIN, OUTPUT);
  
  // Inicialização do Servo
  servo.attach(SERVO_PIN);
  servo.write(120); // Posição inicial (trancado)
  
  // Mensagem inicial no LCD
  lcd.setCursor(0, 0);
  lcd.print("Aproxime o");
  lcd.setCursor(0, 1);
  lcd.print("cartao RFID");
}

void loop() {
  // Verifica se um novo cartão foi detectado
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    // Verifica se o cartão é aceito
    if (verificaCartao(rfid.uid.uidByte, rfid.uid.size, uidLuis, sizeof(uidLuis))) {
      // Cartão de Luis aceito
      digitalWrite(LED_VERDE_PIN, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Bem vindo, Luis!");
      servo.write(20); // Destrancar
      
      delay(3000); // Manter destrancado por 3 segundos
      
      servo.write(120); // Trancar novamente
      digitalWrite(LED_VERDE_PIN, LOW);
    } else if (verificaCartao(rfid.uid.uidByte, rfid.uid.size, uidBel, sizeof(uidBel))) {
      // Cartão de Bel aceito
      digitalWrite(LED_VERDE_PIN, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Bem vinda, Bel!");
      servo.write(20); // Destrancar
      
      delay(3000); // Manter destrancado por 3 segundos
      
      servo.write(120); // Trancar novamente
      digitalWrite(LED_VERDE_PIN, LOW);
    } else {
      // Cartão não aceito
      digitalWrite(LED_VERMELHO_PIN, HIGH);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Pessoa nao");
      lcd.setCursor(0, 1);
      lcd.print("identificada");
      
      delay(3000); // Manter mensagem por 3 segundos
      
      digitalWrite(LED_VERMELHO_PIN, LOW);
    }
    
    // Resetar o leitor de cartões
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
    
    // Mensagem inicial no LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Aproxime o");
    lcd.setCursor(0, 1);
    lcd.print("cartao RFID");
  }
}

bool verificaCartao(byte *uid, byte tamanho, byte *uidAceito, byte tamanhoAceito) {
  if (tamanho != tamanhoAceito) return false;
  for (byte i = 0; i < tamanho; i++) {
    if (uid[i] != uidAceito[i]) return false;
  }
  return true;
}