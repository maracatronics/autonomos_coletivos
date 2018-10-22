/***************************************************************************************************************************
 * Biblioteca a ser utilizada na MSP430G2 para o controle do chute e passe dos robôs da equipe Maracatronics - Versão 1.0
 *
 * por Natália Souza Soares e Victor Lyra - <maracatronics@gmail.com> 
****************************************************************************************************************************/
#include "AcoesMSP.h"


// Construtoras 
AcoesMSP::AcoesMSP(){               
  this->_chutePWM = chute_PWM;               
  this->_disparo = disparo;                 
  this->_adcChute = adc_chute;               
  this->_capacitorCarregado = false;         
}

AcoesMSP::AcoesMSP(uint8_t c, uint8_t dis, uint8_t adcC){
  this->_chutePWM = c;
  this->_disparo = dis;
  this->_adcChute = adcC;
  this->_capacitorCarregado = false;
}

// Métodos
void AcoesMSP::configurarMSP(){
  Serial.begin(9600);
  analogFrequency(3000);                                    // Define a frequência do analogWrite como 3000

  pinMode(this->_chutePWM,OUTPUT);                          
  pinMode(this->_disparo,OUTPUT);
  pinMode(this->_adcChute,INPUT);
  
  digitalWrite(this->_disparo,LOW);
}

void AcoesMSP::carregarCapacitor(){               
  int valor_capacitor, tensao_capacitor;
  double carga_capacitor;
  valor_capacitor = analogRead(this->_adcChute);            // Valor atual da capacitância
  carga_capacitor = (DEN_CHUTE * valor_capacitor);          // Valor atual da carga do capacitor
  if(this->_mensagemRecebida[1] == 'C')
    tensao_capacitor = 180;                                 // Valor pretendido para a carga do capacitor (CHUTE)
  else
    tensao_capacitor = 100;                                 // Valor pretendido para a carga do capacitor (DEFAULT)
  if(carga_capacitor < tensao_capacitor){
    analogWrite(this->_chutePWM, DUTY);                     // similar ao PWMWrite(pin, resolution, duty, frequency) -> frequency definida no configurarMSP
    this->_capacitorCarregado = false;
  }
  else
    this->_capacitorCarregado = true;                       // Capacitor já está carregado
}

void AcoesMSP::receberComando(){
  byte aux[3];
  if(Serial.available()){
    unsigned long starttime = millis();

    while(Serial.available() < MSG_SIZE && millis() - starttime < 500){}          // Espera um certo tempo para sincronizar

    if(Serial.available() >= MSG_SIZE){                                            // Se o conteúdo da serial tiver pelo menos o mesmo tamanho da mensagem esperada
       for(int n = 0; n < MSG_SIZE; n++){       
           aux[n] = Serial.read();                              // Lê o conteúdo da serial até o tamanho da mensagem esperada
       }
       if(aux[0] == 'M' && (aux[1] == 'C' || aux[1] == 'P' || aux[1] == 'N') && (aux[2] == '1' || aux[2] == '0')){
        this->_mensagemRecebida[0] = aux[0];
        this->_mensagemRecebida[1] = aux[1];
        this->_mensagemRecebida[2] = aux[2];
       }
       
    }
  }
}

void AcoesMSP::chutar(){
  if(this->_capacitorCarregado && this->_mensagemRecebida[2] == '1' && this->_mensagemRecebida[1] != 'N'){  // Se o comando for chute ou passe 
    digitalWrite(this->_disparo,HIGH);            // Realiza o disparo
    this->_capacitorCarregado = false;            // Capacitor ficou descarregado
  }
  else{                                           // Caso contrário, realiza tudo o oposto
    digitalWrite(this->_disparo,LOW);
  }
}
