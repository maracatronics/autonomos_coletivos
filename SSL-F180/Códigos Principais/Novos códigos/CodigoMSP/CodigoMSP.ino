#include <AcoesMSP.h>

// Set clock para 16MHz
BCSCTL1 = CALBC1_16MHZ;        // Set DCO to 16MHz
DCOCTL =  CALDCO_16MHZ;

AcoesMSP msp;
//P1_1 -> RX
//P1_2 -> TX

void setup() {
  msp.configurarMSP();
}

void loop() {
  digitalWrite(P1_6, HIGH);
  msp.receberComando(); 
  msp.carregarCapacitor();
  msp.chutar();
  msp.enviarInfo();
    
    
}

