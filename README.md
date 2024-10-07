# Projeto Arduino: Sistema de Destrancamento com RFID

## Descrição
Este projeto utiliza um Arduino Uno R3 para criar um sistema de destrancamento baseado em RFID. O sistema utiliza um leitor RFID RC522 para ler cartões RFID e destrancar um servo motor se o cartão for aceito. Além disso, um display LCD I2C exibe mensagens para o usuário, e LEDs indicam se o cartão foi aceito ou não.

## Componentes utilizados
* Arduino Uno R3
* Leitor RFID RC522
* Servo Motor 9g
* Display LCD I2C (16x2)
* LEDs (Verde e Vermelho)
* Resistores de 1000Ω
* Jumpers e Protoboard

## Conexões de Hardware

### LCD I2C:
* GND -> GND do Arduino
* VCC -> 5V do Arduino
* SDA -> A4 do Arduino
* SCL -> A5 do Arduino

### RFID RC522:
* SDA -> Pin 10 do Arduino
* SCK -> Pin 13 do Arduino
* MOSI -> Pin 11 do Arduino
* MISO -> Pin 12 do Arduino
* IRQ -> Não conectado
* GND -> GND do Arduino
* RST -> Pin 9 do Arduino
* 3.3V -> 3.3V do Arduino

### Servo Motor:
* GND -> GND do Arduino
* VCC -> 5V do Arduino
* Sinal -> Pin 3 do Arduino

### LEDs:
* **LED Verde:**
  * Anodo -> Resistor 1000Ω -> Pin 4 do Arduino
  * Catodo -> GND do Arduino
* **LED Vermelho:**
  * Anodo -> Resistor 1000Ω -> Pin 5 do Arduino
  * Catodo -> GND do Arduino

## Bibliotecas necessárias
* Wire.h
* LiquidCrystal_I2C.h
* MFRC522.h
* Servo.h

### Instalação das bibliotecas
1. Abra o Arduino IDE.
2. Vá para Sketch -> Incluir Biblioteca -> Gerenciar Bibliotecas....
3. Pesquise e instale as bibliotecas LiquidCrystal_I2C, MFRC522 e Servo

## Como Executar
1. Conecte os componentes conforme descrito na seção "Conexões de Hardware".
2. Abra o Arduino IDE e carregue o código main.ino no Arduino Uno R3.
3. Abra o Monitor Serial (Ferramentas -> Monitor Serial) para verificar a saída do UID dos cartões.
4. Aproxime um cartão RFID do leitor.
5. Se o cartão for aceito, o servo motor destrancará, o LED verde acenderá e uma mensagem de boas-vindas será exibida no LCD.
6. Se o cartão não for aceito, o LED vermelho acenderá e uma mensagem de erro será exibida no LCD.

### Adicionando Novos Cartões
Para adicionar novos cartões, siga estes passos:

1. Use o código de leitura de UID para obter o UID do novo cartão.
2. Adicione o UID do novo cartão ao código principal, criando um novo array byte para armazenar o UID.
3. Modifique a função loop() para verificar o novo UID e exibir a mensagem apropriada.

### Licença
Este projeto é licenciado sob a licença MIT. Para mais detalhes, consulte o arquivo LICENSE.
