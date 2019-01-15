#include <Radio.h>
#include "wiring_analog.c"    // Necessário para o PWMWrite
#include <AcoesTiva2.h>
#include <Motor.h>
#include <Hall.h>

#define ID_ROBO 0x03

void parar();
bool isChecksumOk(char);
void contagemPulsos1();
void contagemPulsos2();
void contagemPulsos3();


//void contagemSubida1();
//void contagemDescida1();
//void contagemSubida2();
//void contagemDescida2();
//void contagemSubida3();
//void contagemDescida3();



int valorRoda1, valorRoda2, valorRoda3, qntPulsosTotal[3] = {0};
unsigned long tempoRadioParado = millis(), tempoPulso1, tempoPulso2, tempoPulso3;
boolean radioParou = true, interruptRoda1 = true, interruptRoda2 = true, interruptRoda3 = true;


Motor *robo[3];
Hall *hallMotores[3];
Radio radio(109, "RX"); 
AcoesTiva2 tiva;

void setup() {  
  //Serial.begin(38400);
  Serial.begin(9600);
  for(int i = 0; i < 3; i++){
    robo[i] = new Motor(i+1);
    robo[i]->configurar();
    hallMotores[i] = new Hall(robo[i]->_hall, 8);
  }
  
 
  attachInterrupt(digitalPinToInterrupt(robo[0]->_hall), contagemPulsos1 , CHANGE);
  attachInterrupt(digitalPinToInterrupt(robo[1]->_hall), contagemPulsos2 , CHANGE);
  attachInterrupt(digitalPinToInterrupt(robo[2]->_hall), contagemPulsos3 , CHANGE);

  tiva.configurarTiva();  
  radio.setup();
  
  parar();
}



void loop() {
  char msg[7];
  char sendFrame[6];
  static unsigned int tempoHorus, tempoTotal, tempoInicial, tempoAtual, tempoPulso;
  static boolean flagHorus = false, inicio = true;


// PRINTS PARA TESTES DA RODA GIRANDO NA MÃO
//  Serial.print("  pul1: ");
//  Serial.print(qntPulsosTotal[0]);
//  Serial.print("  pul2: ");
//  Serial.print(qntPulsosTotal[1]);
//  Serial.print("  pul3: ");
//  Serial.println(qntPulsosTotal[2]);


  if(radio.receive(msg, 7) && isChecksumOk(msg) && ((msg[0] == 'M') && ((msg[1] & 0x07) == ID_ROBO))){
      //Serial.println("recebeu");
      if(inicio){
        tempoInicial = millis();
        tempoRadioParado = tempoInicial;
        tempoPulso1 = tempoInicial;
        tempoPulso2 = tempoInicial;
        tempoPulso3 = tempoInicial;
        for(int k = 0; k < 3; k++){
          qntPulsosTotal[k] = 0;
        }
        inicio = false;
        Serial.print("PWM");
        Serial.print("    RPM R1");
        Serial.print("    RPM R2");
        Serial.println("    RPM R3");
      }
      else{
        tempoAtual = millis();
        tempoTotal = tempoAtual - tempoInicial;
      }
      
      for(int j = 0; j < 3; j++){
         robo[j]->andar(msg);
         PWMWrite(robo[j]->_velocidade, 127, robo[j]->_output, 1000);          // PWMWrite(pin, resolution, duty, frequency);
      }

      // PRINTS PARA TESTES DA RODA GIRANDO RECEBENDO PELO RÁDIO
//      Serial.print("tempo: ");
//      Serial.print(tempoTotal);    
//      Serial.print("  pul1: ");
//      Serial.print(qntPulsosTotal[0]);
//      Serial.print("  pul2: ");
//      Serial.print(qntPulsosTotal[1]);
//      Serial.print("  pul3: ");
//      Serial.println(qntPulsosTotal[2]);

      
    
      tiva.driblar(msg);
      if(tiva.carregarCapacitor(msg, false))
        PWMWrite(tiva._chutePWM, 255, DUTY, 3000);       //PWMWrite(pin, resolution, duty, frequency);
      else
        PWMWrite(tiva._chutePWM, 255, 0, 3000);       //PWMWrite(pin, resolution, duty, frequency);
      tiva.chutar(msg, true);
      
      //tempoRadioParado = millis();
      tempoRadioParado = tempoAtual;
      radioParou = false;
   
      // Horus
     /* if(msg[1] & 0x80 && !flagHorus){
        tempoHorus = millis();
        flagHorus = true;
      }
      if(flagHorus && millis() - tempoHorus >= ID_ROBO * 100){
        PWMWrite(tiva._chutePWM, 255, 0, 3000);       //PWMWrite(pin, resolution, duty, frequency);
        tiva.horus(sendFrame, msg[1]);
        radio.sendHorus(sendFrame);
        flagHorus = false;
      }*/
    //}
    
  }
  else{
    //Serial.println("nao recebeu");
    delay(1);
    if(millis() - tempoRadioParado >= 500)
      parar();  
  }  
}


void parar(){
  char protocol[6] = {'M', ID_ROBO, 1, 1, 1, 1};
  for(int j = 0; j < 3; j++){
    robo[j]->andar(protocol);
    PWMWrite(robo[j]->_velocidade, 127, robo[j]->_output, 1000);          // PWMWrite(pin, resolution, duty, frequency);
  }
  if(millis() - tempoRadioParado >= 3000){
    PWMWrite(tiva._chutePWM, 255, 0, 3000);       //PWMWrite(pin, resolution, duty, frequency);
    tiva.chutar(protocol, radioParou);
    radioParou = true;
  }
  tiva.driblar(protocol);
}

bool isChecksumOk(char msg[]) {
  return (msg[6] == (msg[0] ^ msg[1] ^ msg[2] ^ msg[3] ^ msg[4] ^ msg[5]));
}

void contagemPulsos1(){
  valorRoda1 = digitalRead(robo[0]->_hall);
  if(valorRoda1){
    Serial.println("1 HIGH");
    //tempoPulso1 = micros();
  }
  else{
    Serial.println("1 LOW");
    /*if(micros() - tempoPulso1 >= 700){
      qntPulsosTotal[0]++;
    }*/
  }
}

void contagemPulsos2(){
  valorRoda2 = digitalRead(robo[1]->_hall);
  if(valorRoda2){
    Serial.println("2 HIGH");
    //tempoPulso2 = micros();
  }
  else{
    Serial.println("2 LOW");
    /*if(micros() - tempoPulso2 >= 700){
      qntPulsosTotal[0]++;
    }*/
  }
}

void contagemPulsos3(){
  valorRoda3 = digitalRead(robo[2]->_hall);
  if(valorRoda3){
    Serial.println("3 HIGH");
    //tempoPulso3 = micros();
  }
  else{
    Serial.println("3 LOW");
    /*if(micros() - tempoPulso3 >= 700){
      qntPulsosTotal[2]++;
    }*/
  }
}
