#ifndef motores_h  				// Guarda de inclusão (evita problemas de compilação caso o usuário inclua a biblioteca mais de uma vez)
#define motores_h

// Inclusão de bibliotecas necessárias
#include "Hall.h"
#include "PID_v1.h"

#define ANTI_HORARIO 0x7F		// 127 em hexa

// Pinos do microcontrolador que estão sendo utilizados para as rodas 1, 2 e 3
const uint8_t motores_pins[3][3] = {
  {PB_5, PC_6, PC_7},     						// Velocidade roda 1,2 e 3 respectivamente
  {PB_0, PA_4, PA_3},     						// Sentido da rotação do Motor 1,2 e 3 respectivamente
  {PB_2, PE_0, PF_0}      						// Sensor Hall Motor 1,2 e 3 respectivamente
};

class Motor
{
	public:
	  	// Construtores 
	  	Motor(int); 							// Recebe o id do Motor e inicializa o resto com valores default
	  	Motor(double, double, double, int);		// Recebe kp, ki, kd e o id da roda e inicializa o resto com valores default
	  
	  	// Métodos Implementados 
	  	void configurar();						// Realiza as inicializações dos pinos como entrada ou saída
	  	void andar(char []);					// Recebe o protocolo de comunicação e realiza a ação de andar
	  
	  	// Métodos ainda não Implementados 
	  	void andarPID(double);					// Recebe um setpoint e realiza a ação de andar com o controle PID da velocidade dos motores
	  	double PWMtoSpeed(byte);				// Recebe o valor de pwm pretendido e transforma num setpoint da velocidade do Motor

	private:
	  	// Atributos
	  	int _id;									// id = 1, 2 ou 3 (o id da Motor deve ser igual ao da roda que ele está acoplado) 
	  	double _kp, _ki, _kd;						// kp = constante proporcional; ki = constante integrativa; kd = constante derivativa (constantes do PID)
	  	double _setpoint, _input, _output;			// setpoint = velocidade pretendida do Motor; input = velocidade atual do Motor; output = valor do pwm de saída (PID)
	  	uint8_t _velocidade, _sentido, _hall;		// Pinos para saída do pwm da roda (velocidade), para o sentido da rotação do Motor e para a leitura da velocidade atual do Motor (hall)
	  	boolean _status;							// Se o controlador e o sensor já foram atualizados (status = 1) ou não (status = 0)	  	
};
#endif
