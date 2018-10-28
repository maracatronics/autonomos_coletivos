 /*
  * Código usado para o recebimento do PWM das rodas enquanto o robô anda no chão.
  * Recebimento por rádio.
  */
 
 /*
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

#define PROTOCOL_SIZE 8                     //Tamanho do protocolo em bytes
#define FAIL_SAFE_SIZE PROTOCOL_SIZE - 4    
#define START       'M'                     //byte de start
#define ID_ROBO     0x03                    //ID do robô
#define ID_BIT          0x07

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

//SPI do rádio
Enrf24 radio(PA_3, PE_0, PB_3); //PA_3: CE   PE_0: CSN   PB_3:IRQ //Rádio no mód 0
//Enrf24 radio(PF_3, PC_6, PC_7); //PF_3: CE   PC_6: CSN   PC_7:IRQ //Rádio no mód 1
//Enrf24 radio(PD_1, PC_4, PC_5); //PB_5: CE   PC_4: CSN   PC_5:IRQ //Rádio no mód 2
//Enrf24 radio(PD_1, PC_4, PC_5); //PD_1: CE   PB_2: CSN   PC_5:IRQ //Rádio no mód 3

//Endereço de transmição
const uint8_t txaddr[] = {0x11, 0x22, 0x33, 0x44, 0x55};

//Variáveis
unsigned long tempo=0;
uint16_t FS = 0;  // contador do fail safe
char protocol[PROTOCOL_SIZE];
int i = 0;
int timer = 0;
boolean state = false;
boolean reception = false;

//Definição de funções
void Status_do_radio_serial(uint8_t status);
void Tratar_Radio();
String Descodificar(char recebido);


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
  radio.setChannel(0);      //troca de canal, deve ir até 124

  radio.begin();  //padrões 1Mbps, canal 0, max TX power
  Status_do_radio_serial(radio.radioState());

  //Set rádio como receptor com o endereço de transmissão
  radio.setRXaddress((void*)txaddr);
  radio.enableRX();
}

void loop()
{
   boolean erro_no_radio = false;
  if (radio.radioState() == ENRF24_STATE_PRX) { //if que garante o estado do radio
    digitalWrite(RED_LED, LOW);
    if (radio.available(true)) {         //if acionado quando o radio recebe alguma informação
      digitalWrite(BLUE_LED, LOW);
      state = !state;
      digitalWrite(GREEN_LED, state); //desliga indicação de aguardo e liga a de recepção
      FS = 0;                    //reinicia a contagem de fail safe
      Tratar_Radio();
    }
    else {  
      if (FS==0){
        tempo=millis();
      }
      FS=millis()-tempo;
    } //end else
    
  }  //end estado de recepção
  
  else {
    erro_no_radio = true;
  }
  if (erro_no_radio == true) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    FS = 0;
  }
  if (FS >= 500) {
    digitalWrite(GREEN_LED, LOW);
  }
  if (FS >= 1000) {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);
    FS = 0;
  }
}


void Tratar_Radio() {
  //******declaração de variáveis locais*******
  char protocol[PROTOCOL_SIZE];
  int i = 0;
  boolean exit = false;
  //Serial.println("entrou");
  //*****inicio da recepção******
   if (radio.read(protocol,PROTOCOL_SIZE)) {
  
    //******Testes de comunicação**********
    for (i = 0; i <= FAIL_SAFE_SIZE && !exit; i++) {
      if (protocol[i] == START) {
        exit = true;
      }
    }
    
    //******análise de solicitações recebidas********
    if (i <= FAIL_SAFE_SIZE) {
        //Imprime o protocolo recebido
        for(int j=i; j<i+6; j=j+2){
          Serial.print(Descodificar(protocol[j]));
          Serial.print(Descodificar(protocol[j+1]));
          Serial.print("  ");
        }
        Serial.println((byte)protocol[i+6]);
    } 
    
  } //end leitura do radio
}//end tratar radio


//Função para adicionar 0 para numeros menores que 10
String Descodificar(char recebido){
  int num = recebido;
  if(num < 10){
    if(num == 1)
      return "00";
     else
       return "0" + String(num);
  }
  else
    return String(num);
}


void Status_do_radio_serial(uint8_t status){
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

