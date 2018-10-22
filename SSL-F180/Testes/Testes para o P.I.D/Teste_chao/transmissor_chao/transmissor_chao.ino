/*
  cÃ³digo usado no recebimento de dados a partir do chip nrf24l01.
  circuito:
  PD_0 conectado ao SCK do radio
  PD_1 conectado ao CE do radio
  PD_2 MISO do radio
  PD_3 MOSI do radio
  PC_4 CSN do radio
  PC_5 IRQ do radio
  A alimentaÃ§Ã£o do chip de radio pode ser feita com o prÃ³prio micro atravÃ©s dos pinos de 3,3V e GND


Motor 11 - 24, Motor 10 - 24, Motor 12 - 24
Motor 9 - 16 , Motor 8 - 24, Motor 7 - 24
Motor 6 - 24, Motor 5 - 24 , Motor 4 - 8 
Motor 3 - morreu, Motor 2 - 24, Motor 1 - morreu 
*/



#include <SPI.h>      //|-----------------------------------------------------------
#include <Enrf24.h>   //|Inclui as bibliotecas refentes ao radio
#include <nRF24L01.h> //|
#include <string.h>   //|-----------------------------------------------------------

#include <wiring_analog.c>  //Biblioteca de manipulaÃ§Ã£o do pwm

//mapeamento de pinos
#define Chute_PWM       PB_4   // Pwm do chute
#define disparo         PD_6   // Comando de chute 
#define Speed_M1        PB_5   // Controle de Velocidade do Motor 1
#define Speed_M2        PB_0   // Controle de Velocidade do Motor 2
#define Speed_M3        PB_1   // Controle de Velocidade do Motor 3
#define Motor1_sentido  PA_2   // Controle de sentido do Motor 1
#define Motor2_sentido  PA_3   // Controle de sentido do Motor 2
#define Motor3_sentido  PA_4   // Controle de sentido do Motor 3
#define Motor1_hall     PF_4   // Leitura do Sensor Hall do Motor 1
#define Motor2_hall     PD_7   // Leitura do Sensor Hall do Motor 2
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
#define PROTOCOL_SIZE 8
#define FAIL_SAFE_SIZE PROTOCOL_SIZE - 4 //levando em consideraÃ§Ã£o deslocamentos do protocolo somente Ã  direita

/*   
 *        Estrutura do protocolo
 *     [START][ID][V1][V2][V3][STOP]
 */

#define CHUTAR 67
#define PASSAR 80
#define DUTY 180                                     //Duty cycle para o chute 70% de 256
#define Den_chute 0.05476458075846455051348017708874 //Define-se o inverso do denominador da regra de 3 do chute para evitar divisÃµes no cÃ³digo visto que divisÃµes em MCUS sÃ£o lentas
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


Enrf24 radio(PD_1, PC_4, PC_5); //DefiniÃ§Ã£o dos pinos do rÃ¡dio no MCU PD_1: CE   PC_4: CSN   PC_5:IRQ
const uint8_t rxaddr[] = {0x11, 0x22, 0x33, 0x44, 0x55};
const uint8_t txaddr[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE};
char Velocidade_1 = 0;
char Velocidade_2 = 0;
char Velocidade_3 = 0;



//*******MAPEAMENTO DE FUNÃ‡Ã•ES A SEREM UTILIZADAS*******
void Status_do_radio_serial(uint8_t status);
void Tratar_Radio(double freq[], byte pwm);
void Stop();
boolean controle_chute(int Chute_Passe);
float Bateria();
void lerSensorHallDosMotores(byte pwm);


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

  radio.begin();  //padrÃµes 1Mbps, canal 0, max TX power

  /* if (digitalRead(frequencia==HIGH)) radio.setChannel(0);   //seleciona a frequencia utilizada
    else radio.setChannel(1);*/
  //  Serial.println("AQUI");
  Status_do_radio_serial(radio.radioState());
 // radio.setChannel(10);
  radio.setTXaddress((void*)rxaddr);
  //radio.setRXaddress((void*)rxaddr);
  //radio.enableRX();  //comeÃ§a a receber
  
    
  Status_do_radio_serial(radio.radioState());

  Stop();

  delay(5000);
}


#define INTERVALO 100

double frequencias[3];

void loop()
{
 static int i = 0;
 int State = 0;
 byte veloc[] = {1, 25, 50, 75, 100, 125, 100, 75, 50, 25, 1};
 static unsigned int t = millis();
 if (State == 0){
 //2 rodas por vez 
  if(i<11){
    
    //******roda 1****
    /*digitalWrite(Motor1_sentido, LOW);
    Velocidade_1 = veloc[i];
    PWMWrite(Speed_M1, 128, Velocidade_1, 1000); //PWMWrite(pin, resolution, duty, frequency);
    //Serial.println((int)Velocidade_1);*/
    digitalWrite(Motor1_sentido, HIGH);
    Velocidade_1 = (veloc[i] & ANTI_HORARIO);
    PWMWrite(Speed_M1, 128, Velocidade_1, 1000); 
  
    //*******roda 2******
    digitalWrite(Motor2_sentido, LOW);
    Velocidade_2 = veloc[i];
    PWMWrite(Speed_M2, 128, Velocidade_2, 1000); 

    //*******roda 3******
    /*digitalWrite(Motor3_sentido, HIGH);
    Velocidade_3 = veloc[i];
    PWMWrite(Speed_M3, 128, Velocidade_3, 1000); */
    digitalWrite(Motor3_sentido, LOW);
    Velocidade_3 = veloc[i];
    PWMWrite(Speed_M3, 128, Velocidade_3, 1000);

    //Serial.println(veloc[i]);
    //Serial.println(i);
    //Serial.print(t);
    //Serial.print(millis());
    lerSensorHallDosMotores(veloc[i]);
    //Tratar_Radio(veloc[i]);

     
        
    if(millis() - t > 2000){
     i++;
     t = millis();
    } 
  }
  else if(i >11)
    State++; 
 } 
/*else if(State == 1){
//Andar pro lado?
     //******roda 1****
  digitalWrite(Motor1_sentido, LOW);
  Velocidade_1 = veloc[i];
  PWMWrite(Speed_M1, 128, Velocidade_1, 1000); //PWMWrite(pin, resolution, duty, frequency);
        //Serial.println((int)Velocidade_1); 

  //*******roda 2******
  digitalWrite(Motor2_sentido, LOW);
  Velocidade_2 = veloc[i];
  PWMWrite(Speed_M2, 128, Velocidade_2, 1000); 

  //*******roda 3******
  //digitalWrite(Motor2_sentido, LOW);
  //Velocidade_2 = veloc[i];
  //PWMWrite(Speed_M2, 128, Velocidade_2, 1000); 
   
   Tratar_Radio();
        
   if(millis() - t > 2000){
     State++;
     t = millis();
    } 
} 

else if(State == 2){
//Andar pro outro lado?
     //******roda 1****
  digitalWrite(Motor1_sentido, LOW);
  Velocidade_1 = veloc[i];
  PWMWrite(Speed_M1, 128, Velocidade_1, 1000); //PWMWrite(pin, resolution, duty, frequency);
        //Serial.println((int)Velocidade_1); 

  //*******roda 2******
  digitalWrite(Motor2_sentido, LOW);
  Velocidade_2 = veloc[i];
  PWMWrite(Speed_M2, 128, Velocidade_2, 1000); 

  //*******roda 3******
  //digitalWrite(Motor2_sentido, LOW);
  //Velocidade_2 = veloc[i];
  //PWMWrite(Speed_M2, 128, Velocidade_2, 1000); 
   
   Tratar_Radio(veloc[i]);

   if(millis() - t > 2000){
     State++;
     t = millis();
    } 
} */

else if (State == 1){
//Fazer nada  
//Serial.println("estado 1");
}

 
}  //end loop

void lerSensorHallDosMotores(byte pwm){
  //lerSensorHallMotor1();
  //lerSensorHallMotor2();
  //lerSensorHallMotor3();
  static byte estado1 = 0, estado2 = 0, estado3 = 0;
  static int contador1=0, contador2=0, contador3=0;
  static unsigned int t1=0;
  
  switch(estado1){
    case 0:
      if(digitalRead(Motor1_hall)==HIGH) estado1=1;
    break;
    case 1:
      if(digitalRead(Motor1_hall)==LOW){
        estado1=0;

        contador1++;
       //Serial.println(contador);
      }
    break;
  }
  switch(estado2){
    case 0:
      if(digitalRead(Motor2_hall)==HIGH) estado2=1;
    break;
    case 1:
      if(digitalRead(Motor2_hall)==LOW){
        estado2=0;

        contador2++;
        //Serial.println(contador);
      }
    break;
  }
  switch(estado3){
    case 0:
      if(digitalRead(Motor3_hall)==HIGH) estado3=1;
    break;
    case 1:
      if(digitalRead(Motor3_hall)==LOW){
        estado3=0;

        contador3++;
        //Serial.println(contador);

      }
    break;
  }

  if(millis()-t1>=INTERVALO){
    frequencias[0]=(((double)contador1/24)/INTERVALO)*1000*60;
    frequencias[1]=(((double)contador2/24)/INTERVALO)*1000*60;
    frequencias[2]=(((double)contador3/24)/INTERVALO)*1000*60;
    Tratar_Radio(frequencias, pwm);
    //Serial.print(frequencias[0]);
    //Serial.print(" ");
    //Serial.print((byte)((int)frequencias[0]%100));
    //Serial.println();
    contador1=0;
    contador2=0;
    contador3=0;
    t1=millis();
  }
  
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
       //Serial.println(contador);
      }
    break;
  }


  //Serial.println((int)frequencias[0]);
  
  //Serial.println(contador);
  if(millis()-t1>=INTERVALO){
    frequencias[0]=(((double)contador/24)/INTERVALO)*1000*60;
    //testar(frequencias[0]);
    //Serial.print(frequencias[0]);
    //Serial.print(" ");
    //Serial.print((byte)((int)frequencias[0]%100));
    //Serial.println();
    contador=0;
    t1=millis();
  }
  //Serial.println(frequencias[0]);
}

void testar (double freq, double freq2, double freq3){
  /*Serial.print(freq);
  Serial.print("  ");
  Serial.print(freq2);
  Serial.print("  ");
  Serial.println(freq3);*/
  
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
        //Serial.println(contador);
      }
    break;
  }
  
  if(millis()-t1>=INTERVALO){
    frequencias[1]=(((double)contador/24)/INTERVALO)*1000*60;
    /*Serial.print(frequencias[1]);
    Serial.print(" ");
    Serial.print((byte)((int)frequencias[1]%100));
    Serial.println();*/
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
        //Serial.println(contador);

      }
    break;
  }
  
  if(millis()-t1>=INTERVALO){
    frequencias[2]=(((double)contador/24)/INTERVALO)*1000*60;
    /*Serial.print(frequencias[2]);
    Serial.print(" ");
    Serial.print((byte)((int)frequencias[2]%100));
    Serial.println();*/
    contador=0;

    t1=millis();
  }
}

void Tratar_Radio(double freq[], byte pwm) {
  char protocol[PROTOCOL_SIZE];

  //Serial.println(frequencias[0]);
   
  if (radio.radioState() == ENRF24_STATE_NOTPRESENT) {
    Serial.println("erro no radio");
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, HIGH);
  }

  else {
    digitalWrite(BLUE_LED, HIGH);

  protocol[0] = 'M';
  int j = 0;
  for(int i = 1; i<6;i=i+2){
    protocol[i] = (byte)((int)freq[j]/100);
    if(protocol[i] == 0)
      protocol[i] = 1;    
    j++;
    }
  j = 0;
  for(int i = 2; i<7;i=i+2){
    protocol[i] = (byte)((int)freq[j]%100);
    if(protocol[i] == 0)
      protocol[i] = 1;
    j++;
    }
   protocol[7] = pwm;

   /*for(int i = 0; i<11; i++){
    Serial.print(protocol[i]);
   }
   Serial.println();*/
   /*Serial.print(frequencias[0]);
   Serial.print("     ");
   Serial.print(frequencias[1]);
   Serial.print("     ");
   Serial.print(frequencias[2]);
   Serial.print("     ");
   Serial.println(pwm);*/
   Serial.print((byte)protocol[1]);
   Serial.print((byte)protocol[2]);
   Serial.print(" ");
   Serial.print((byte)protocol[3]);
   Serial.print((byte)protocol[4]);
   Serial.print(" ");
   Serial.print((byte)protocol[5]);
   Serial.print((byte)protocol[6]);
   Serial.print(" ");
   Serial.println((byte)protocol[7]);
   //Serial.println(frequencias[2]);
   //Serial.println((byte)((int)frequencias[0]%100));
   radio.print(protocol);
   radio.flush();
  
  }


  
}   //end tratar radio


  /*
   * Divisor de tensÃ£o (10M e 3M): 12 volts ------------ 2.76923
   *                               carga da bateria----- tensÃ£o na porta
   *                               
   * ADC:  3 volts ----------- 4095
   *       tensÃ£o na porta--- valor de contagem
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
  Divisor de tensÃ£o (1,5M e 22K):  200 volts -------- 2.89093 volts   2.8836                        pode ser 2M e 27k
                          carga do capacitor ----- tensÃ£o na porta
                          
  ADC:   3 volts (mÃ¡ximo)-------4095 (12 bits de resoluÃ§Ã£o)
         tensÃ£o na porta --------- valor de contagem
  
  
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


  carga_capacitor=valor_capacitor*Den_chute;  //2,9430=valor fÃ­sico      NÃ£o foram feitas as multiplicaÃ§Ãµes para diminuir erros e para o caso de se precisar mudar o divisor de tensÃ£o
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

  //**********nÃ£o chutar nem driblar************
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


