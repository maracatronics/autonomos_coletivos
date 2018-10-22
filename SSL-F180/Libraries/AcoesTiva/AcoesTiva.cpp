/************************************************************************************************************************
 * Biblioteca a ser utilizada na TIVA TM4C123 para o controle das ações dos robôs da equipe Maracatronics - Versão 1.0
 *
 * por Natália Souza Soares e Victor Lyra - <maracatronics@gmail.com> 
*************************************************************************************************************************/
#include "AcoesTiva.h"
//#include <wiring_analog.c>

// Construtores para a Tiva 
AcoesTiva::AcoesTiva(){                   
  this->_infrared = infrared;            
  this->_drible = drible;                 
}

// Construtores para a Tiva
AcoesTiva::AcoesTiva(uint8_t i, uint8_t dri){
  this->_infrared = i;
  this->_drible = dri;
}

void AcoesTiva::configurarTiva(){
  Serial4.begin(9600);
  pinMode(this->_infrared,INPUT);
  pinMode(this->_drible,OUTPUT);
}

void AcoesTiva::enviarComando(char protocolo[]){          // Protocolo = {'M', byteAção+ID, byteVelocMotor1, byteVelocMotor2, byteVelocMotor3, 1}
  char protocolo2[MSG_SIZE];                              // Cria um vetor de tam 3 para ser enviado para MSP
  protocolo2[0] = protocolo[0];                           // O primeiro elemento enviado será o byte de start do protocolo de comunicação ('M')

  if(protocolo[1] & CHUTE_BIT)                            // Verifica se é para chutar - AND bit a bit entre o byte de ações+id do protocolo recebido e o bit do chute
    protocolo2[1] = 'C';                                  // O segundo elemento enviado será que é para chutar
  else if(protocolo[1] & PASSE_BIT)                       // Verifica se é para passar - AND bit a bit entre o byte de ações+id do protocolo recebido e o bit do passe
    protocolo2[1] = 'P';                                  // O segundo elemento enviado será que é para passar
  else                                                    // Caso nenhum dos casos dê certo, não é para ele fazer nada
    protocolo2[1] = 'N';                                  // O segundo elemento enviado será que é para fazer nada

  if(this->possedeBola())                                 // Verifica se o robô está com posse de bola
    protocolo2[2] = '1';                                  // O último elemento enviado será que o robô está com a bola
  else                                                    // Caso contrário
    protocolo2[2] = '0';                                  // O último elemento enviado será que o robô não está com a bola

  Serial4.write(protocolo2);
}

void AcoesTiva::driblar(char protocolo[]){            // Protocolo = {'M', byteAção+ID, byteVelocMotor1, byteVelocMotor2, byteVelocMotor3, 1}
  if(protocolo[1] & DRIBLE_BIT)                       // Verifica se é para driblar - AND bit a bit entre o byte de ações+id do protocolo recebido e o bit do drible
    digitalWrite(this->_drible,HIGH);                 // Realiza o drible
  else                                                // Caso contrário
    digitalWrite(this->_drible,LOW);                  // Não dribla
}

boolean AcoesTiva::possedeBola(){
  if(digitalRead(this->_infrared) == HIGH)                // Se o sensor infrared detectar a bola
    return true;                                          // O robô está com a pose de bola
  return false;                                           // Caso contrário, ele não está
}
