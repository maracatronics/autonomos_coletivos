#include "Hall.h"

Hall::Hall(int pin, int qtdPulsos){
  this->_val=0;
  this->_estado=0;
  this->_contador=0;
  this->_t1=0;
  this->_pin=pin;
  this->_qtdPulsos=qtdPulsos;
}

int Hall::returnHall(){
 /* switch(_estado){                                //Compara o estado de leitura do sensor 
      case 0:
        if(digitalRead(_pin)==HIGH) _estado=1;       // e conta a quantidade de varia��es (pulsos)                    
      break;
      case 1:
        if(digitalRead(_pin)==LOW){
          _estado=0;
  
          _contador++;                              //Vari�vel que recebe essa contagem
        }
      break;
    }*/
                                                              //|----------------------------------------------------------------------------|
    //if(millis()-_t1>=INTERVALO){                               //| Para cada intervalo de 100 milissegundos                                   |
                                                              //|(por defini��o intervalo = 100) vai facilitar para calcular os ciclos       |
      _val=(((double)_contador/_qtdPulsos)/INTERVALO)*1000*60;   //| usa a quantidade de pulsos para calcular a quantidade de ciclos por minuto |
                                                              //|____________________________________________________________________________|
      _contador=0;
  
      _t1=millis();                                            // reinicia a contagem de tempo
    //}

    return _val;                                               // essa � a vari�vel de retorno da fun��o em forma de ciclos por minuto
}