#ifndef AcoesTiva_h					   // Guarda de inclusão (evita problemas de compilação caso o usuário inclua a biblioteca mais de uma vez)
#define AcoesTiva_h

#include "Arduino.h"

#define MSG_SIZE 3
#define DRIBLE_BIT 0x10                // Valor, em hexa, do bit de drible
#define CHUTE_BIT 0x40                 // Valor, em hexa, do bit de chute
#define PASSE_BIT 0x20                 // Valor, em hexa, do bit de passe


const uint8_t infrared = PE_4;         // Leitura do led infravermelho - verificar posse de bola
const uint8_t drible = PE_5;           // Controle do drible

class AcoesTiva{
public:
  // Construtores
  AcoesTiva();                       // Inicialização dos atributos com os valores default
  AcoesTiva(uint8_t, uint8_t);       // Inicialização dos pinos do infrared e do controle do drible manualmente

  // Métodos
  boolean possedeBola();			       // Verifica se o robô está ou não com a posse de bola
  void enviarComando(char []);		   // Envia o comando de chutar, passar ou nada para a MSP
  void configurarTiva();			       // Realiza a inicialização dos pinos como entrada ou saída e da serial 
  void driblar(char []);			       // Comando para o drible

private:
  // Atributos
  uint8_t _infrared, _drible;		     // Pinos do LED infravermelho e do controle do drible
};
#endif
