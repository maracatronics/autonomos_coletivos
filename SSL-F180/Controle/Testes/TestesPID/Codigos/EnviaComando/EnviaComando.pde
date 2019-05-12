//***********************************************funciona na versao 3.3.6 *******************************************
import processing.serial.*;

 
int velocidade1 = 100, velocidade2 = 100, velocidade3 = 100;
int ID = 3;
int DRIBLE = 16, CHUTE = 64, PASSE = 32;

Serial myPort;

void setup(){
 myPort = new Serial(this, Serial.list()[0], 38400);
}

long t1 = 0, tempo = millis();
int contador = 0, INTERVALO=60000;
int estado = 0;

//int velocidades[]={0, 25, 50, 75, 100, 125, 100, 75, 50, 25, 0};
boolean enviar = true, control = true;  
void draw(){
  if(enviar){
    if(millis() - t1 >= INTERVALO){
      enviar = !enviar;
    }
    
    //println(velocidades[contador]);
    
    byte[] msg = new byte[7];
  
    msg[0] = (byte) 'M';   
    msg[1] = (byte) (ID);
    msg[2] = (byte) velocidade1;
    msg[3] = (byte) velocidade2;  
    msg[4] = (byte) velocidade3;
    msg[5] = (byte) 'F';
    msg[6] = (byte) (msg[0] ^ msg[1] ^ msg[2] ^ msg[3] ^ msg[4] ^ msg[5]);
   
    myPort.write(msg);
    
    if(estado == 0){
      velocidade1 = 127;
      velocidade2 = 127;
      velocidade3 = 127;
      if(millis() - tempo >= 5000){
        estado = 1;
        tempo = millis();
      }
     }
     else if(estado == 1){
       velocidade1 = 1;
       velocidade2 = 1;
       velocidade3 = 1;
       if(millis() - tempo >= 5000){
         estado = 0;
         tempo = millis();
       }
     }
    
    delay(10);  
 
  
  }
  //ID++;
  //if(ID == 4)
   //ID = 2;
   
  /* if((key == 'a' || key == 'A') && keyPressed && control){
     enviar = !enviar;
     control = false;
   }
   control = !keyPressed;*/
   
   //println(enviar);
} 