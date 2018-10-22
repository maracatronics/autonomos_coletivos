#define INTERVALO 100       // intervalo definido para a contagem de milissegundos

#ifndef Hall_h
#define Hall_h

#include "Arduino.h"

class Hall{
  private: int _pin, _qtdPulsos, _val;
           byte _estado;                          //    contador de pulso do sensor hall 
           int _contador;
           int _t1;

  public:
  Hall(int pin, int qtdPulsos);
  
  int returnHall();
};//***************  Fim da class Hall  ****************************

#endif