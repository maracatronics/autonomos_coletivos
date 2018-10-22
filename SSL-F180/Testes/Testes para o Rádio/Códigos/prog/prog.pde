/*
 *Programa para enviar informções pelo rádio e as salva em um arquivo .txt
 */

import processing.serial.*;

Serial myPort;

void setup(){
  //Lista de COM
  myPort = new Serial(this, Serial.list()[0], 38400);
}

int c1=3, mainCont=0;  //ID do robô e contador
void draw(){
  //Printa o progresso do programa
  if(mainCont<=10000){
    print(((double)mainCont/10000)*100);
    println("%");
    
    //Cria um protocolo para o envio
    byte[] msg = new byte[6];
    msg[0] = (byte) 0xff;
    msg[1] = (byte) c1;
    msg[2] = (byte) random(1, 127);
    msg[3] = (byte) random(1, 127);  
    msg[4] = (byte) random(1, 127);
    msg[5] = (byte) 0x01;
    
    //Salva o protocolo em um arquivo .txt com o nome da ID de envio
    String arq = str(msg[2])+" "+str(msg[3])+" "+str(msg[4]);
    saveStrings("id"+str(c1)+".txt", append(loadStrings("id"+str(c1)+".txt"), arq));
    
   // myPort.write(msg);
    
    //Para enviar para multiplas ID's
    c1++;
    if(c1>=5) c1=3;
    
    mainCont++;
    
    delay(10);
  }
  else println("ACABEI!!!");
} 