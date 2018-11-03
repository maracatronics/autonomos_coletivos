#include <Radio.h>
#include "wiring_analog.c"    // Necessário para o PWMWrite
#include <AcoesTiva2.h>
#include <Motor.h>


//PC_4 - RX
//PC_5 - TX

#define ID_ROBO 0x03 

void parar();

Motor *robo[3];
Radio radio(0, "RX"); 
AcoesTiva2 tiva;

boolean radioParou = true;

void setup() {  
  for(int i = 0; i < 3; i++){
    robo[i] = new Motor(i+1);
    robo[i]->configurar();
  }

  tiva.configurarTiva();  
  
  radio.setup();

  parar();
}

void loop() {
  char msg[6];
  char sendFrame[6];
  static unsigned int tempoRadioParado = millis(), tempoHorus, tempinho;
  static boolean flagHorus = false;
  
  if(radio.receive(msg, 6)){
    Serial.println("recebeu");
    if((msg[0] == 'M') && ((msg[1] & 0x07) == ID_ROBO)){
      
      for(int j = 0; j < 3; j++){
         robo[j]->andar(msg);
         PWMWrite(robo[j]->_velocidade, 127, robo[j]->_output, 1000);          // PWMWrite(pin, resolution, duty, frequency);
      }
    
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
      if(msg[1] & 0x80 && !flagHorus){
        tempoHorus = millis();
        flagHorus = true;
      }
      if(flagHorus && millis() - tempoHorus >= ID_ROBO * 100){
        PWMWrite(tiva._chutePWM, 255, 0, 3000);       //PWMWrite(pin, resolution, duty, frequency);
        tiva.horus(sendFrame, msg[1]);
        radio.sendHorus(sendFrame);
        flagHorus = false;
      }
    }
    
  }
  else{
    Serial.println("nao recebeu");
    if(millis() - tempoRadioParado >= 500)
      parar();  
  }  
}

void parar(){
  char protocol[6] = {'M', ID_ROBO, 0, 0, 0, 1};
  for(int j = 0; j < 3; j++){
    robo[j]->andar(protocol);
    PWMWrite(robo[j]->_velocidade, 127, robo[j]->_output, 1000);          // PWMWrite(pin, resolution, duty, frequency);
  }
    
  PWMWrite(tiva._chutePWM, 255, 0, 3000);       //PWMWrite(pin, resolution, duty, frequency);
  tiva.chutar(protocol, radioParou);
  tiva.driblar(protocol);
  radioParou = true;
}

