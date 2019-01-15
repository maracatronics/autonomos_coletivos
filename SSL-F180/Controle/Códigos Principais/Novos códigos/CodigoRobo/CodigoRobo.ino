#include <Radio.h>
#include "wiring_analog.c"    // Necessário para o PWMWrite
#include <AcoesTiva2.h>
#include <Motor.h>
#include <Hall.h>

#define ID_ROBO 0x03
#define INTERVALO_MINIMO 700
#define INTERVALO_MAXIMO 500

void parar();
bool isChecksumOk(char);
void contagemPulsos1();
void contagemPulsos2();
void contagemPulsos3();


//void contagemSubida1();
//void contagemDescida1();
//void contagemSubida2();
//void contagemDescida2();
//void contagemSubida3();
//void contagemDescida3();



int valorRoda1, valorRoda2, valorRoda3, qntPulsosTotal[3] = {0};
unsigned long tempoRadioParado = millis(), tempoPulso1 = 0, tempoPulso2 = 0, tempoPulso3 = 0;
boolean radioParou = true, interruptRoda1 = true, interruptRoda2 = true, interruptRoda3 = true;


Motor *robo[3];
Hall *hallMotores[3];
Radio radio(109, "RX");
AcoesTiva2 tiva;

void setup() {
  //Serial.begin(38400);
  Serial.begin(9600);
  for (int i = 0; i < 3; i++) {
    robo[i] = new Motor(i + 1);
    robo[i]->configurar();
    hallMotores[i] = new Hall(robo[i]->_hall, 8);
  }


  attachInterrupt(digitalPinToInterrupt(robo[0]->_hall), contagemPulsos1 , CHANGE);
  attachInterrupt(digitalPinToInterrupt(robo[1]->_hall), contagemPulsos2 , CHANGE);
  attachInterrupt(digitalPinToInterrupt(robo[2]->_hall), contagemPulsos3 , CHANGE);

  tiva.configurarTiva();
  radio.setup();

  parar();
}



void loop() {
  char msg[7];
  char sendFrame[6];
  static unsigned int tempoHorus, tempoTotal, tempoInicial, tempoAtual, tempoPulso, tempoContagem, tempoAuxiliar;
  static boolean flagHorus = false, inicio = true;
  static double rpm[3] = {0};

  // PRINTS PARA TESTES DA RODA GIRANDO NA MÃO
  /*  Serial.print("  pul1: ");
    Serial.print(qntPulsosTotal[0]);
    Serial.print("  pul2: ");
    Serial.print(qntPulsosTotal[1]);
    Serial.print("  pul3: ");
    Serial.println(qntPulsosTotal[2]);
*/

  if (radio.receive(msg, 7) && isChecksumOk(msg) && ((msg[0] == 'M') && ((msg[1] & 0x07) == ID_ROBO))) {
    //Serial.println("recebeu");
    if (inicio) {
      tempoInicial = millis();
      tempoRadioParado = tempoInicial;
      tempoContagem = tempoInicial;
      tempoAuxiliar = tempoInicial;
      tempoPulso1 = tempoInicial;
      tempoPulso2 = tempoInicial;
      tempoPulso3 = tempoInicial;
      for (int k = 0; k < 3; k++) {
        qntPulsosTotal[k] = 0;
      }
      inicio = false;
      Serial.print("PWM");
      Serial.print("    RPM R1");
      Serial.print("    RPM R2");
      Serial.println("    RPM R3");
    }
    else {
      tempoAtual = millis();
      tempoTotal = tempoAtual - tempoInicial;
      tempoContagem = tempoAtual - tempoAuxiliar;
      if (tempoContagem >= INTERVALO_MAXIMO){
        for (int k = 0; k < 3; k++) {
          qntPulsosTotal[k] = 0;
        }
        tempoAuxiliar = tempoAtual;
      }
    }

    for (int j = 0; j < 3; j++) {
      robo[j]->andar(msg);
      PWMWrite(robo[j]->_velocidade, 127, robo[j]->_output, 1000);          // PWMWrite(pin, resolution, duty, frequency);
    }

    // PRINTS PARA TESTES DA RODA GIRANDO RECEBENDO PELO RÁDIO
   /* Serial.print("tempo 1: ");
    Serial.print(tempoPulso1);
    Serial.print("tempo 2: ");
    Serial.print(tempoPulso2);
    Serial.print("tempo 3: ");
    Serial.println(tempoPulso3);*/
    for ( int i = 0; i < 3; i ++){
      rpm[i] = (((double)qntPulsosTotal[i]/24)/tempoContagem)*1000*60;
    }
   //Serial.print("  rpm1: ");
   Serial.print((int) msg[3]);
   Serial.print("    ");
    Serial.print(rpm[0]);
    Serial.print("    ");
    //Serial.print("  rpm2: ");
    Serial.print(rpm[1]);
    Serial.print("    ");
    //Serial.print("  rpm3: ");
    Serial.println(rpm[2]);



    tiva.driblar(msg);
    if (tiva.carregarCapacitor(msg, false))
      PWMWrite(tiva._chutePWM, 255, DUTY, 3000);       //PWMWrite(pin, resolution, duty, frequency);
    else
      PWMWrite(tiva._chutePWM, 255, 0, 3000);       //PWMWrite(pin, resolution, duty, frequency);
    tiva.chutar(msg, true);

    //tempoRadioParado = millis();
    tempoRadioParado = tempoAtual;
    radioParou = false;

    // Horus
    /* if(msg[1] & 0x80 && !flagHorus){
       tempoHorus = millis();
       flagHorus = true;
      }
      if(flagHorus && millis() - tempoHorus >= ID_ROBO * 100){
       PWMWrite(tiva._chutePWM, 255, 0, 3000);       //PWMWrite(pin, resolution, duty, frequency);
       tiva.horus(sendFrame, msg[1]);
       radio.sendHorus(sendFrame);
       flagHorus = false;
      }*/
    //}

  }
  else {
    //Serial.println("nao recebeu");
    delay(1);
    if (millis() - tempoRadioParado >= 500)
      parar();
  }
}


void parar() {
  char protocol[6] = {'M', ID_ROBO, 1, 1, 1, 1};
  for (int j = 0; j < 3; j++) {
    robo[j]->andar(protocol);
    PWMWrite(robo[j]->_velocidade, 127, robo[j]->_output, 1000);          // PWMWrite(pin, resolution, duty, frequency);
  }
  if (millis() - tempoRadioParado >= 3000) {
    PWMWrite(tiva._chutePWM, 255, 0, 3000);       //PWMWrite(pin, resolution, duty, frequency);
    tiva.chutar(protocol, radioParou);
    radioParou = true;
  }
  tiva.driblar(protocol);
}

bool isChecksumOk(char msg[]) {
  return (msg[6] == (msg[0] ^ msg[1] ^ msg[2] ^ msg[3] ^ msg[4] ^ msg[5]));
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
