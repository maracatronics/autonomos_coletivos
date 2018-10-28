/*
  código usado no recebimento de dados a partir do chip nrf24l01.
  circuito:
  PD_0 conectado ao SCK do radio
  PD_1 conectado ao CE do radio
  PD_2 MISO do radio
  PD_3 MOSI do radio
  PC_4 SCN do radio
  PC_5 IRQ do radio
  A alimentação do chip de radio pode ser feita com o próprio micro através dos pinos de 3,3V e GND


*/

#include <Enrf24.h>
#include <nRF24L01.h>
#include <string.h>
#include <SPI.h>

#define PROTOCOL_SIZE 6

#define RED0 PB_0
#define BLUE0 PE_4
#define GREEN0 PB_1

#define RED1 PE_5
#define BLUE1 PA_6
#define GREEN1 PA_7


#define RED2  PD_6
#define BLUE2 PF_4
#define GREEN2 PD_7


#define RED3 PE_1
#define BLUE3 PE_3
#define GREEN3 PE_2


Enrf24 radio(PA_3, PE_0, PB_3); //PA_3: CE   PE_0: CSN   PB_3:IRQ //Rádio no mód 0
//Enrf24 radio(PF_3, PC_6, PC_7); //PF_3: CE   PC_6: CSN   PC_7:IRQ //Rádio no mód 1
//Enrf24 radio(PD_1, PC_4, PC_5); //PB_5: CE   PC_4: CSN   PC_5:IRQ //Rádio no mód 2
//Enrf24 radio(PD_1, PC_4, PC_5); //PD_1: CE   PB_2: CSN   PC_5:IRQ //Rádio no mód 3

const uint8_t txaddr[] = {0x11, 0x22, 0x33, 0x44, 0x55};

char protocol[PROTOCOL_SIZE];
int i = 0;
int timer = 0;
boolean state = false;
boolean reception = false;

void Status_do_radio_serial(uint8_t status);

void setup()
{
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  Serial.begin(38400);

  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);           //MSB primeiro
  SPI.setModule(0);         //seleciona o modulo de SPI do micro
  radio.setChannel(0);      //troca de canal, deve ir até 124 (em teoria)

  radio.begin();  //padrões 1Mbps, canal 0, max TX power
  Status_do_radio_serial(radio.radioState());

  radio.setTXaddress((void*)txaddr);
}

void loop()
{

  if (radio.radioState() == ENRF24_STATE_NOTPRESENT) {
    Serial.println("erro no radio");
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, HIGH);
  }

  else {
    digitalWrite(BLUE_LED, HIGH);

   if (Serial.available()) {

      digitalWrite(BLUE_LED, LOW);
      digitalWrite(RED_LED, LOW);
      

      char a = Serial.read();
      if(a==0){
        a=1;
      }
      protocol[i] = a;
      i++;
      timer = 0;
      Serial.println(a);

      if (i >= PROTOCOL_SIZE)
      {
        radio.print(protocol);
        radio.flush();
        delay(5);
        state=!state;
        digitalWrite(GREEN_LED, state);
        Serial.println("...");
        i = 0;
      }
    }

    else {
      digitalWrite(RED_LED, LOW);

      if (timer <= 1000){
        timer++;
      }
      else{
        digitalWrite(BLUE_LED, HIGH);
        digitalWrite(GREEN_LED, LOW);
      }
    }
  }
}

void Status_do_radio_serial(uint8_t status)
{
  Serial.print("Enrf24 radio transceiver status: ");
  switch (status) {
    case ENRF24_STATE_NOTPRESENT:
      Serial.println("NO TRANSCEIVER PRESENT");
      break;

    case ENRF24_STATE_DEEPSLEEP:
      Serial.println("DEEP SLEEP <1uA power consumption");
      break;

    case ENRF24_STATE_IDLE:
      Serial.println("IDLE module powered up w/ oscillators running");
      break;

    case ENRF24_STATE_PTX:
      Serial.println("Actively Transmitting");
      break;

    case ENRF24_STATE_PRX:
      Serial.println("Receive Mode");
      break;

    default:
      Serial.println("UNKNOWN STATUS CODE");
  }
}

