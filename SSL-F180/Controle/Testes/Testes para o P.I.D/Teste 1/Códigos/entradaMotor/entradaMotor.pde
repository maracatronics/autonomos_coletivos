/*
  Programa para passar para o rádio uma sequência de velocidades
  em intervalos de tempo.
*/

import processing.serial.*;
Serial myPort;

void setup(){
  //lista de COM
  myPort = new Serial(this, Serial.list()[0], 38400);
}

//Sequência de velocidades
int velocidades[]={0, 25, 50, 75, 100, 125, 100, 75, 50, 25, 0};

int cont=0;     //Iterador das velocidades
int t1=0;       //Contador de tempo

void draw(){
  byte[] msg=new byte[6];
  
  msg[0] = (byte) 0xff;                        //byte de início
  msg[1] = (byte) 3;                           //ID do robô
  msg[2] = (byte) (0 | 100);     //Velocidade da roda 1
  msg[3] = (byte) (0 | 0);     //Velocidade da roda 2
  msg[4] = (byte) (0 | 100);     //Velocidade da roda 3
  msg[5] = (byte) 0x01;                        //byte de fim
  
  println(velocidades[cont]);
  
  //Mandar protocolo para a COM
  myPort.write(msg);  
  
  //Contador
  if(millis()-t1>=2000){
      if(cont<10) cont++;    //próxima iteração
      t1=millis();
  }
}
