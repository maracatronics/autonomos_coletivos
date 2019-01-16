/*********************************************************************************************************************************
 * Biblioteca a ser utilizada na TIVA TM4C123 para o controle dos motoreses maxons dos robôs da equipe Maracatronics - Versão 1.0
 *
 * por Natália Souza Soares e Victor Lyra - <maracatronics@gmail.com> 
**********************************************************************************************************************************/
#include "Motor.h"
//#include "wiring_analog.c"    // Necessário para o PWMWrite

// Construtores 
Motor::Motor(int id){ // Básico
  this->_id = id;
  this->_velocidade = motores_pins[0][id-1];
  this->_sentido = motores_pins[1][id-1];
  this->_hall = motores_pins[2][id-1];
  this->_kp = 1;
  this->_ki = 1;
  this->_kd = 1;
  this->_input = 0;
  this->_setpoint = 0;
  this->_output = 0;
  this->_status = false;
  this->_tacometro = tacometro_pins[id - 1];
}

Motor::Motor(double kp, double ki, double kd, int id){ // Básico com PID
  this->_kp = kp;
  this->_ki = ki;
  this->_kd = kp;
  this->_input = 0;
  this->_setpoint = 0;
  this->_output = 0;
  this->_id = id;
  this->_velocidade = motores_pins[0][id-1];
  this->_sentido = motores_pins[1][id-1];
  this->_hall = motores_pins[2][id-1];
  this->_status = false;
  this->_tacometro = tacometro_pins[id - 1];
}


// Métodos 
void Motor::configurar(){                          
  pinMode(_velocidade,OUTPUT);                  
  pinMode(_sentido,OUTPUT);
  pinMode(_hall,INPUT);
  pinMode(_tacometro, INPUT);
}

double Motor::PWMtoSpeed(byte setpoint_pwm){
  // TODO
}

void Motor::andarPID(double setpoint_speed){
  // TODO
  /*if(!_status){
    PID motorPID(&(_input), &(t_output), &(_setpoint), _kp, _ki, _kd, 0);         // Inicializa o controlador PID do motor
    motorPID.SetMode(AUTOMATIC);

    Hall hallMotor(_hall,48);                                                                      // Inicializa o sensor Hall

    _status = true; 
  }

  _input = analogRead(_hall);
  _setpoint = setpoint_speed;

  //motorPID.Compute();
  analogWrite(_velocidade, _output);*/
}

void Motor::andar(char protocolo[]){                              // Protocolo = {'M', byteAção+ID, byteVelocMotor1, byteVelocMotor2, byteVelocMotor3, 1}
  if(protocolo[_id + 1] <= ANTI_HORARIO){                 // Se o pwm do motor <= 127 
    digitalWrite(_sentido, LOW);                            // Rotação no sentido horário 
    _output = protocolo[_id + 1];                   // Output recebe o pwm contido no byte de velocidade do motor específico (1,2 ou 3)
  }
  else{                                                           // Se o pwm > 127 - rotação no sentido anti-horário
    digitalWrite(_sentido, HIGH);
    _output = (protocolo[_id + 1] & ANTI_HORARIO);  // Módulo 127
  }
 }


