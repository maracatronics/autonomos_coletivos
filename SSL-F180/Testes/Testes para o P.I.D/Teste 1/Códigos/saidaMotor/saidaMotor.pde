/*
  Programa para salvar em .txt informações printadas na Serial da COM  
*/

import processing.serial.*;
Serial myPort;

void setup(){
  //Lista de COM
  myPort = new Serial(this, Serial.list()[0], 38400);
}

void draw(){
  //Verifica se algo é printado na Serial e salva em um arquivo .txt
  if(myPort.available()>0){
    String msg = myPort.readString();
    saveStrings("frequencias.txt", append(loadStrings("frequencias.txt"), msg));
  }
}