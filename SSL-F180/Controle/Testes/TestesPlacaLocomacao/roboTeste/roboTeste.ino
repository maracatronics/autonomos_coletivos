#include <Radio.h>
#include <Motor.h>

motores *robo[3];
Radio radio(0, "RX"); 

void setup() {
  Serial.begin(38400);
  
  for(int i = 0; i < 3; i++){
    robo[i] = new motores(i+1);
    robo[i]->Configurar();
  }

  radio.setup();
}

void loop() {
  char msg[6];
  
  if(radio.receive(msg)){
    Serial.println(msg);
  }
  else
    Serial.println(" ");

  for(int j = 0; j < 3; j++)
    robo[j]->Andar(msg);
}
