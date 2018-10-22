/*
  código usado no recebimento de dados a partir do chip nrf24l01.
  circuito:
  PD_0 conectado ao SCK do radio
  PD_1 conectado ao CE do radio
  PD_2 MISO do radio
  PD_3 MOSI do radio
  PC_4 CSN do radio
  PC_5 IRQ do radio
  A alimentação do chip de radio pode ser feita com o próprio micro através dos pinos de 3,3V e GND

*/



#include <SPI.h>      //|-----------------------------------------------------------
#include <Enrf24.h>   //|Inclui as bibliotecas refentes ao radio
#include <nRF24L01.h> //|
#include <string.h>   //|-----------------------------------------------------------

#include <wiring_analog.c>  //Biblioteca de manipulação do pwm

//mapeamento de pinos
#define Chute_PWM       PB_4   // Pwm do chute
#define disparo         PD_6   // Comando de chute 
#define Speed_M1        PB_5   // Controle de Velocidade do Motor 1
#define Speed_M2        PB_0   // Controle de Velocidade do Motor 2
#define Speed_M3        PB_1   // Controle de Velocidade do Motor 3
#define Motor1_sentido  PA_2   // Controle de sentido do Motor 1
#define Motor2_sentido  PA_3   // Controle de sentido do Motor 2
#define Motor3_sentido  PA_4   // Controle de sentido do Motor 3
#define Motor1_hall     PB_6   // Leitura do Sensor Hall do Motor 1
#define Motor2_hall     PB_7   // Leitura do Sensor Hall do Motor 2
#define Motor3_hall     PE_0   // Leitura do Sensor Hall do Motor 3
#define Infrared        PE_4   // Leitura do Infravermelho - Posse de bola
#define drible          PE_5   // Controle do Drible
#define adc_bateria     PE_1   // Canal A2 do ADC
#define adc_chute       PE_3   // Canal A0 do ADC
#define Led_Capacitor   PF_0   // Led indicativo do Capacitor

//atuadores
#define BATERIA_BIT     0x08
#define DRIBLE_BIT      0x10
#define CHUTE_BIT       0x40
#define PASSE_BIT       0x20
#define ID_BIT          0x07
#define ANTI_HORARIO    0x7F

/*
 *          X C P D B I I I
 */

//controle de protocolo
#define START       0xFF
#define ID_ROBO     0x03
#define PROTOCOL_SIZE 6
#define FAIL_SAFE_SIZE PROTOCOL_SIZE - 4 //levando em consideração deslocamentos do protocolo somente à direita

/*   
 *        Estrutura do protocolo
 *     [START][ID][V1][V2][V3][STOP]
 */

#define CHUTAR 67
#define PASSAR 80
#define DUTY 180                                     //Duty cycle para o chute 70% de 256
#define Den_chute 0.05476458075846455051348017708874 //Define-se o inverso do denominador da regra de 3 do chute para evitar divisões no código visto que divisões em MCUS são lentas
                                                     //den_chute=(200*3.3)/(4095*div tensao)
#define Den_bat 0.00349206446208139819721378494034   //Mesmo motivo do chute

int l=0;

uint16_t FS = 0;  // contador do fail safe
unsigned long tempo=0;
unsigned long tempo_pulso=0;
boolean estado_chute = false;
boolean state = false;
int Chute_passe= PASSAR;
boolean esta_chutando=false;


Enrf24 radio(PD_1, PC_4, PC_5); //Definição dos pinos do rádio no MCU PD_1: CE   PC_4: CSN   PC_5:IRQ
const uint8_t rxaddr[] = {0x11, 0x22, 0x33, 0x44, 0x55};
const uint8_t txaddr[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE};
char Velocidade_1 = 0;
char Velocidade_2 = 0;
char Velocidade_3 = 0;



//*******MAPEAMENTO DE FUNÇÕES A SEREM UTILIZADAS*******
void Status_do_radio_serial(uint8_t status);
void Tratar_Radio();
void Stop();
boolean controle_chute(int Chute_Passe);
float Bateria();


char protocol2[PROTOCOL_SIZE];

int count_safe=0;



void setup()
{
  pinMode(adc_chute,INPUT);
  pinMode(Chute_PWM, OUTPUT);
  pinMode(disparo, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(Infrared, INPUT);
  pinMode(Motor1_sentido, OUTPUT);
  pinMode(Motor2_sentido, OUTPUT);
  pinMode(Motor3_sentido, OUTPUT);
  pinMode(Motor1_hall, INPUT);
  pinMode(Motor2_hall, INPUT);
  pinMode(Motor3_hall, INPUT);
  pinMode(drible,OUTPUT);
  pinMode(Led_Capacitor,OUTPUT);
  pinMode(drible,OUTPUT);
  
  digitalWrite(disparo, LOW);

  Serial.begin(38400);

  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);           //MSB primeiro
  SPI.setModule(3);  //seleciona o modulo de SPI 3 do micro

  radio.begin();  //padrões 1Mbps, canal 0, max TX power

  /* if (digitalRead(frequencia==HIGH)) radio.setChannel(0);   //seleciona a frequencia utilizada
    else radio.setChannel(1);*/
  //  Serial.println("AQUI");
  Status_do_radio_serial(radio.radioState());
 radio.setChannel(3);
  radio.setRXaddress((void*)rxaddr);
  //radio.setTXaddress((void*)txaddr);
  radio.enableRX();  //começa a receber
  
    
  Status_do_radio_serial(radio.radioState());

  Stop();
}


#define INTERVALO 100

double frequencias[3];

void loop()
{
  boolean erro_no_radio = false;
  // Status_do_radio_serial(radio.radioState());
  if (radio.radioState() == ENRF24_STATE_PRX) { //if que garante o estado do radio
    digitalWrite(RED_LED, LOW);
    //Serial.println("antes leitura");
    if (radio.available(true)) {         //if acionado quando o radio recebe algum  a informação
      Serial.println("ok");
      //      count++;
      //      Serial.println(count);
      digitalWrite(BLUE_LED, LOW);
      state = !state;
      digitalWrite(GREEN_LED, state); //desliga indicação de aguardo e liga a de recepção
      FS = 0;                    //reinicia a contagem de fail safe
      Tratar_Radio();

      //delay(1);
      // Serial.println("apos leitura");
    }  //end recepção
  
   

/*
 * tempo=millis();
 * 
 * 
 * se millis()-tempo==1000
 * para
 */


    else {  
      if (FS==0){
        tempo=millis();
      }
      //delay(1);
      FS=millis()-tempo;
     
    } //end else
    //Serial.println("if recepção");
  }  //end estado de recepção
  else {
    erro_no_radio = true;
  }

//******** controle de variáveis do robo
  //Serial.println("antes bateria");
  //Bateria();
  //Serial.println("antes chute");
  controle_chute(Chute_passe);
  //Serial.println("antes esta chutando");
  if (esta_chutando && (millis()-tempo_pulso)>=100){
    digitalWrite(disparo, LOW);
    Chute_passe=PASSAR;
    tempo_pulso=0;
  }

//Serial.println("depois esta chutando");
  

  if (erro_no_radio == true) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    Stop();
    FS = 0;
  }

  if (FS >= 500) {
    digitalWrite(GREEN_LED, LOW);
  }
  if (FS >= 1000) {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);
    Stop();
    FS = 0;
  }
  //Serial.println("fim loop");

  lerSensorHallDosMotores();

  printFrequencias();
  
}  //end loop

void printFrequencias(){
  static unsigned int t1=0;

  if(millis()-t1>=10){
   // Serial.println(String(frequencias[0]) + " " + String(frequencias[1]) + " " + String(frequencias[2]));

    t1=millis();
  }
}

void lerSensorHallDosMotores(){
  lerSensorHallMotor1();
  lerSensorHallMotor2();
  lerSensorHallMotor3();
}

void lerSensorHallMotor1(){
  static byte estado=0;
  static int contador=0;
  static unsigned int t1=0;
  
  switch(estado){
    case 0:
      if(digitalRead(Motor1_hall)==HIGH) estado=1;
    break;
    case 1:
      if(digitalRead(Motor1_hall)==LOW){
        estado=0;

        contador++;
      }
    break;
  }

  if(millis()-t1>=INTERVALO){
    frequencias[0]=(((double)contador/48)/INTERVALO)*1000*60;

    contador=0;

    t1=millis();
  }
}

void lerSensorHallMotor2(){
  static byte estado=0;
  static int contador=0;
  static unsigned int t1=0;
  
  switch(estado){
    case 0:
      if(digitalRead(Motor2_hall)==HIGH) estado=1;
    break;
    case 1:
      if(digitalRead(Motor2_hall)==LOW){
        estado=0;

        contador++;
      }
    break;
  }

  if(millis()-t1>=INTERVALO){
    frequencias[1]=(((double)contador/48)/INTERVALO)*1000*60;

    contador=0;

    t1=millis();
  }
}

void lerSensorHallMotor3(){
  static byte estado=0;
  static int contador=0;
  static unsigned int t1=0;
  
  switch(estado){
    case 0:
      if(digitalRead(Motor3_hall)==HIGH) estado=1;
    break;
    case 1:
      if(digitalRead(Motor3_hall)==LOW){
        estado=0;

        contador++;
      }
    break;
  }

  if(millis()-t1>=INTERVALO){
    frequencias[2]=(((double)contador/48)/INTERVALO)*1000*60;

    contador=0;

    t1=millis();
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
 /*   for(int k=0;k<6;k++){
      int nome=protocol[k];
      Serial.print(nome);
      Serial.print(" ");
    }
    Serial.println();*/

  
    //******Testes de comunicação**********
    for (i = 0; i <= FAIL_SAFE_SIZE && !exit; i++) {
      if (protocol[i] == START) {
        exit = true;
      }
    }

    //Serial.println((byte)protocol[i]);

    //Serial.println("oi");
    //******análise de solicitações recebidas********
    if (i <= FAIL_SAFE_SIZE && ((protocol[i] & ID_BIT) == ID_ROBO)) {

      //      Serial.print("ID ");
            //Serial.println(protocol[i] & ID_BIT);
      //      Serial.print(", pwm1 ");
            //Serial.print((int)protocol[i+1]);
            //Serial.print(" ");
            //Serial.print((int)protocol[i+2]);
            //Serial.print(" ");
            //Serial.println((int)protocol[i+3]);
      //      Serial.println("...");


      //Serial.println("antes de receber");


      //Fail safedereceber comandos iguais
      
  /*    bool is_equal=true;
     for(int k=0;k<PROTOCOL_SIZE;k++){
      if(protocol[k]!=protocol2[k]){
        is_equal=false;
        break;
      }
      
     }
      for(int k=0;k<PROTOCOL_SIZE;k++){
        Serial.print((int)protocol[k]);
        Serial.print(" ");
        protocol2[k]=protocol[k];
      }
      Serial.print(count_safe);
      Serial.print("\n");
     if(is_equal){
      count_safe++;
     }
     else{
      count_safe=0;
     }
     if(count_safe>15){
      Stop();
      if(count_safe>=100){
        count_safe=0;
      }
        
      return;
     }

     
*/



//******roda 1****
      if (protocol[i + 1] <= ANTI_HORARIO)
      {
        digitalWrite(Motor1_sentido, LOW);
        Velocidade_1 = protocol[i + 1];

      }
      else
      {
        digitalWrite(Motor1_sentido, HIGH);
        Velocidade_1 = (protocol[i + 1] & ANTI_HORARIO);

      }
      PWMWrite(Speed_M1, 128, Velocidade_1, 1000); //PWMWrite(pin, resolution, duty, frequency);
            //Serial.println((int)Velocidade_1);

      //**********************

      //*******roda 2******
      if (protocol[i + 2] <= ANTI_HORARIO)
      {
        digitalWrite(Motor2_sentido, LOW);
        Velocidade_2 = protocol[i + 2];
      }
      else
      {
        digitalWrite(Motor2_sentido, HIGH);
        Velocidade_2 = (protocol[i + 2] & ANTI_HORARIO);
      }
      PWMWrite(Speed_M2, 128, Velocidade_2, 1000); //PWMWrite(pin, resolution, duty, frequency);
            //Serial.println((int)Velocidade_2);
      //**********************


      //*******roda 3******
      if (protocol[i + 3] <= ANTI_HORARIO)
      {
        digitalWrite(Motor3_sentido, LOW);
        Velocidade_3 = protocol[i + 3];
      }
      else
      {
        digitalWrite(Motor3_sentido, HIGH);
        Velocidade_3 = (protocol[i + 3] & ANTI_HORARIO);
      }
      PWMWrite(Speed_M3, 128, Velocidade_3, 1000); //PWMWrite(pin, resolution, duty, frequency);
             //Serial.println((int)Velocidade_3);
      //**********************

            //Serial.println("...");
      //******chute*******
        
        if((protocol[i]&CHUTE_BIT)){
          Chute_passe=CHUTAR;
          if (controle_chute(Chute_passe) && (digitalRead(Infrared) == HIGH)){
            digitalWrite(disparo, HIGH);
            esta_chutando=true;
            tempo_pulso=millis();          
          }
        }
      //Serial.println("ja chutou");
        //**********passe**********

        if(protocol[i]&PASSE_BIT){
          Chute_passe=PASSAR;
          if (controle_chute(Chute_passe) && (digitalRead(Infrared) == HIGH)){
            digitalWrite(disparo, HIGH);
            esta_chutando=true;
            tempo_pulso=millis();         
          }
          
        }
        //Serial.println("ja passou");

        //******drible*******
          if ((protocol[i] & DRIBLE_BIT)){
            digitalWrite(drible,HIGH);
          }
          else{
            digitalWrite(drible,LOW);
          }

         //Serial.println("ja driblou");
    }
//Serial.println("ja driblou2");
      
/*
      //******bateria*******
          if ((protocol[5]&BATERIA_BIT){
            //envia nivel de bateria
            toggle o modo do radio para transmissor -> muda o canal -> envia
            volta para receptor -> volta o canal
            radio.disableRX(); // desabilita o modo de recepção
            radio.setChannel(7);
            radio.print(conversao de float pra char da carga da bateria associado a um protocolo simples);
            radio.flush();
            //convém deixar um tempo curto apos o envio mas se n der problema fica assim
            radio.enableRX();// volta o modo de recepção
            radio.setChannel(1);
          }*/

    //*********************************
  } //end leitura do radio
 // Serial.println("ja driblou3");
}   //end tratar radio


  /*
   * Divisor de tensão (10M e 3M): 12 volts ------------ 2.76923
   *                               carga da bateria----- tensão na porta
   *                               
   * ADC:  3 volts ----------- 4095
   *       tensão na porta--- valor de contagem
   *       
   *       carga da bateria=  12*3*valor de contagem/4095*2.76923
   *       
   * 
   * */


/*float Bateria (){
  int valor_bateria=analogRead(adc_bateria);
  float carga_bateria=0;
   carga_bateria=valor_bateria*Den_bat;
   if(carga_bateria<=11.5){
    digitalWrite(Led_Bat,HIGH);
   }
   else{
    digitalWrite(Led_Bat,LOW);
   }

   return carga_bateria;  

  
}*/

/*
  Divisor de tensão (1,5M e 22K):  200 volts -------- 2.89093 volts   2.8836                        pode ser 2M e 27k
                          carga do capacitor ----- tensão na porta
                          
  ADC:   3 volts (máximo)-------4095 (12 bits de resolução)
         tensão na porta --------- valor de contagem
  
  
                       200*3*valor de contagem
  Carga do capacitor= ---------------------------
                              4095*2.891
  */

boolean controle_chute(int Chute_Passe) {
  
  int valor_capacitor = analogRead(adc_chute);
  int tensao=0;
  if (Chute_Passe==PASSAR){
    tensao=100;
  }
  else if(Chute_Passe==CHUTAR){
    tensao=180;
  }
  float carga_capacitor;


  carga_capacitor=valor_capacitor*Den_chute;  //2,9430=valor físico      Não foram feitas as multiplicações para diminuir erros e para o caso de se precisar mudar o divisor de tensão
  if (carga_capacitor <= (tensao-10)) PWMWrite (Chute_PWM, 256, DUTY, 5000); //PWMWrite(pin, resolution, duty, frequency);
  else if (carga_capacitor >= tensao) PWMWrite (Chute_PWM, 256, DUTY, 5000);
  if (carga_capacitor >= (tensao-10)) {
    digitalWrite (Led_Capacitor,HIGH);
    estado_chute = true;
  }
  else{
    digitalWrite (Led_Capacitor,LOW);
    estado_chute = false;
  }

}  //end controle_chute





void Stop() {
  //********parar as rodas desativando os enables******
  PWMWrite(Speed_M1, 128, 0, 1000);
  PWMWrite(Speed_M2, 128, 0, 1000);
  PWMWrite(Speed_M3, 128, 0, 1000);

  //**********não chutar nem driblar************
  digitalWrite(disparo, LOW);
  digitalWrite(drible, LOW);
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
