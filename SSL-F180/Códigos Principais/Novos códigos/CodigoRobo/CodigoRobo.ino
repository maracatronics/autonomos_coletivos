#include <Radio.h>
#include <Motor.h>
#include <AcoesTiva.h>

#define ID 0x03

Motor *robo[3];
Radio radio(0, "RX"); 
AcoesTiva tiva;


void setup() {
  Serial.begin(38400);
  
  for(int i = 0; i < 3; i++){
    robo[i] = new Motor(i+1);
    robo[i]->configurar();
  }

  tiva.configurarTiva();  
  
  radio.setup();

  digitalWrite(PB_7, LOW);

  parar();
}

void loop() {
  char msg[6];
  static unsigned int tempo = millis();

  digitalWrite(PB_7, LOW);

  if(radio.receive(msg)){
    Serial.println((byte)msg[3]);
    if((msg[0] == 'M') && (msg[1] & ID)){
      for(int j = 0; j < 3; j++)
        robo[j]->andar(msg);
  
      tiva.driblar(msg);
      tiva.enviarComando(msg);
      tempo = millis();
    }
  }
  else{
    if(millis() - tempo >= 500)
      parar();  
  }
  
}

void parar(){
  char protocol[6] = {'M', ID, 0, 0, 0, 1};
  for(int j = 0; j < 3; j++)
    robo[j]->andar(protocol);

  tiva.driblar(protocol);
  tiva.enviarComando(protocol);

}

