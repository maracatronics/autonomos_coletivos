#include <AcoesMSP.h>

AcoesMSP msp;
//P1_1 -> RX
//P1_2 -> TX
unsigned int temp;
void setup() {
 msp.configurarMSP();  
 //Serial.begin(9600);
 temp=millis();
}

void loop() {
  msp.receberComando();
  msp.carregarCapacitor();
  msp.chutar();*/
  
  if(millis()-temp>=5){
    Serial.print(msp._mensagemRecebida[0]);
    Serial.print(" ");
    Serial.print(msp._mensagemRecebida[1]);
    Serial.print(" ");
    Serial.println(msp._mensagemRecebida[2]);
    temp=millis();
  }
}
