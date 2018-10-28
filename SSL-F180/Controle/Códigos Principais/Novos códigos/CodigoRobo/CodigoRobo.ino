#include <Radio.h>
//#include "wiring_analog.c"    // Necessário para o PWMWrite
#include <AcoesTiva.h>
#include <Motor.h>


//PC_4 - RX
//PC_5 - TX

#define ID 0x03

Motor *robo[3];
Radio radio(0, "RX"); 
AcoesTiva tiva;


void setup() {  
  //Serial.begin(9600);
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
  char sendFrame[7];
  static unsigned int tempoRadioParado = millis(), tempoHorus;
  static boolean flagHorus = false;
  
  //tiva.receberComando();
  if(radio.receive(msg, 6)){
    if((msg[0] == 'M') && (msg[1] & ID)){
      for(int j = 0; j < 3; j++)
        robo[j]->andar(msg);
      for(int k = 2; k < 5; k++){
        Serial.print((int)msg[k]);
        Serial.print(" ");
      }
      Serial.println();
  
      tiva.driblar(msg);
      tiva.enviarComando(msg, false);
      tempoRadioParado = millis();
    }
   /*   // Horus
    if(msg[1] & 0x80 && !flagHorus){
      tempoHorus = millis();
      flagHorus = true;
    }
    if(flagHorus && millis() - tempoHorus >= ID * 100){
      tiva.horus(sendFrame, msg[1]);
      radio.sendHorus(sendFrame);
      flagHorus = false;
    }
    */
  }
  else{
    if(millis() - tempoRadioParado >= 500)
      parar();  
  }  
}

void parar(){
  char protocol[6] = {'M', ID, 0, 0, 0, 1};
  for(int j = 0; j < 3; j++)
    robo[j]->andar(protocol);

  tiva.driblar(protocol);
  tiva.enviarComando(protocol, true);
}

