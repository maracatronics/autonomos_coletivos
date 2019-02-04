#include "wiring_analog.c" 
#include <Motor.h>
#include <Hall.h>

void contagemPulsos1();
void contagemPulsos2();
void contagemPulsos3();

int qntPulsosTotal[3] = {0};
unsigned long tempoPulso1 = 0, tempoPulso2 = 0, tempoPulso3 = 0;
boolean interruptRoda1 = true, interruptRoda2 = true, interruptRoda3 = true;
Motor *robo[3];
Hall *hallMotores[3];

void setup() {
  //Serial.begin(9600); 
  Serial.begin(38400);

  for (int i = 0; i < 3; i++) {
    robo[i] = new Motor(i + 1);
    robo[i]->configurar();
    hallMotores[i] = new Hall(robo[i]->_hall, 24);
  }

  attachInterrupt(digitalPinToInterrupt(robo[0]->_hall), contagemPulsos1 , CHANGE);
  attachInterrupt(digitalPinToInterrupt(robo[1]->_hall), contagemPulsos2 , CHANGE);
  attachInterrupt(digitalPinToInterrupt(robo[2]->_hall), contagemPulsos3 , CHANGE);


}

void loop() {
  static unsigned int tempoAtual, tempoPulso, tempoVariacao, tempoInicial;
  static boolean flagComeco = true, inicio = true;
  static double setpoint_speed = 1000;  

  tempoAtual = millis();
    if (inicio) {
      tempoPulso1 = tempoAtual;
      tempoPulso2 = tempoAtual;
      tempoPulso3 = tempoAtual;
      tempoVariacao = tempoAtual;
      for (int k = 0; k < 3; k++) {
        qntPulsosTotal[k] = 0;
        hallMotores[k]->iniciar(tempoAtual);
      }
      if(flagComeco){
        tempoInicial = tempoAtual;
        flagComeco = false;
      }
      else{
        if(tempoAtual - tempoInicial >= 2000)
          inicio = false;
      }
    }
    else {      
      for(int k = 0; k < 3; k++){
        //Serial.println("aqui");
        hallMotores[k]->atualizaTempo(tempoAtual);
        if(hallMotores[k]->_tempoContagem >= INTERVALO_MAXIMO){
          qntPulsosTotal[k] = 0;
        }
      }
    }

    for (int j = 0; j < 3; j++) {
      hallMotores[j]->calcularVelocidade(qntPulsosTotal[j]);
      /*if(hallMotores[0]->_rpm > 750){
        setpoint_speedR1 = 1000;
      }*/
      if(j == 0 || j == 1){
        robo[j]->andarPID(setpoint_speedR1, hallMotores[j]->_rpm);
       // robo[j]->andar(msg);
        PWMWrite(robo[j]->_velocidade, 127, robo[j]->_output, 1000); 
      } else{
       // robo[j]->andarPID(setpoint_speed, hallMotores[j]->_rpm);
        robo[j]->andar(msg);
        PWMWrite(robo[j]->_velocidade, 127, robo[j]->_output, 1000);          // PWMWrite(pin, resolution, duty, frequency);
      }
    }
    
    Serial.print(setpoint_speed);
    Serial.print("         ");
    Serial.print(robo[0]->_input);
    Serial.print("              ");
    Serial.print(robo[0]->_output);
    Serial.print("              ");
    Serial.print(robo[1]->_input);
    Serial.print("              ");
    Serial.println(robo[1]->_output);
}


void contagemPulsos1() {
  if (interruptRoda1) {
    tempoPulso1 = micros();
    interruptRoda1 = false;
  } else {
    tempoPulso1 = micros() - tempoPulso1;
    if (tempoPulso1 >= INTERVALO_MINIMO){
      qntPulsosTotal[0]++;
      interruptRoda1 = true;
    } else {
       interruptRoda1 = true;
    }
  }
}

void contagemPulsos2() {
  if (interruptRoda2) {
    tempoPulso2 = micros();
    interruptRoda2 = false;
  } else {
    tempoPulso2 = micros() - tempoPulso2;
    if (tempoPulso2 >= INTERVALO_MINIMO){
      qntPulsosTotal[1]++;
      interruptRoda2 = true;
    } else {
       interruptRoda2 = true;
    }
  }
}

void contagemPulsos3() {
  if (interruptRoda3) {
    tempoPulso3 = micros();
    interruptRoda3 = false;
  } else {
    tempoPulso3 = micros() - tempoPulso3;
    if (tempoPulso3 >= INTERVALO_MINIMO){
      qntPulsosTotal[2]++;
      interruptRoda3 = true;
    } else {
       interruptRoda3 = true;
    }
  }
}
