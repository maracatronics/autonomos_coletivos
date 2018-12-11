 #include <Radio.h>
#include "wiring_analog.c"    // Necessário para o PWMWrite
#include <AcoesTiva2.h>
#include <Motor.h>
#include <Hall.h>


//PC_4 - RX
//PC_5 - TX

#define ID_ROBO 0x03

void parar();

Motor *robo[3];
Hall *hallMotores[3];
Radio radio(109, "RX"); 
AcoesTiva2 tiva;

int qntPulsos[3] = {48, 48, 48};
boolean radioParou = true;

unsigned int tempoRadioParado = millis();

void setup() {  
  Serial.begin(38400);
  for(int i = 0; i < 3; i++){
    robo[i] = new Motor(i+1);
    robo[i]->configurar();
    hallMotores[i] = new Hall(robo[i]->_hall, qntPulsos[i]);
  }

  tiva.configurarTiva();  
  
  radio.setup();

  parar();
}

bool isChecksumOk(char msg[]) {
  return (msg[6] == (msg[0] ^ msg[1] ^ msg[2] ^ msg[3] ^ msg[4] ^ msg[5]));
}

void loop() {
  char msg[7];
  char sendFrame[6];
  static unsigned int tempoHorus, tempinho;
  static boolean flagHorus = false;

  /*for(int j = 0; j < 3; j++){
    Serial.print(analogRead(robo[j]->_tacometro));
    Serial.print("   ");
  }
  Serial.println((int) msg[2]); */

//  Serial.print((char)msg[0]);
//  Serial.print("    ");
//  Serial.print((int)msg[1]);
//  Serial.print("     ");
//  Serial.print((int)msg[2]);
//  Serial.print("     ");
//  Serial.print((int)msg[3]);
//  Serial.print("     ");
//  Serial.print((int)msg[4]);
//  Serial.print("     ");
//  Serial.println((int)msg[5]);

  if(radio.receive(msg, 7) && isChecksumOk(msg) && ((msg[0] == 'M') && ((msg[1] & 0x07) == ID_ROBO))){
    //Serial.println("recebeu");
    //Serial.println((int)(msg[1]));
    //if((msg[0] == 'M') && ((msg[1] & 0x07) == ID_ROBO)){
      
      for(int j = 0; j < 3; j++){
         robo[j]->andar(msg);
         //Serial.print(hallMotores[j]->returnHall());
          
         Serial.print(analogRead(robo[j]->_tacometro));
         Serial.print("   ");
         PWMWrite(robo[j]->_velocidade, 127, robo[j]->_output, 1000);          // PWMWrite(pin, resolution, duty, frequency);
      }
      Serial.println((int) msg[2]);
//      Serial.print((char)msg[0]);
//      Serial.print("    ");
//      Serial.print((int)msg[1]);
//      Serial.print("     ");
//      Serial.print((int)msg[2]);
//      Serial.print("     ");
//      Serial.print((int)msg[3]);
//      Serial.print("     ");
//      Serial.print((int)msg[4]);
//      Serial.print("     ");
//      Serial.println((int)msg[5]);
//      
    
      tiva.driblar(msg);
      
      if(tiva.carregarCapacitor(msg, false)){
       PWMWrite(tiva._chutePWM, 255, DUTY, 3000);       //PWMWrite(pin, resolution, duty, frequency);
      }
      else{
        PWMWrite(tiva._chutePWM, 255, 0, 3000);       //PWMWrite(pin, resolution, duty, frequency);
      } 
      tiva.chutar(msg, true);
      tempoRadioParado = millis();
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

