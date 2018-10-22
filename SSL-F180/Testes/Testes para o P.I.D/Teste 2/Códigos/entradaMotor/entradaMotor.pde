import processing.serial.*;

Serial myPort;

public static final int ID = 3;

void setup(){
  myPort = new Serial(this, Serial.list()[0], 38400);
}

int velocidades[][]={{0, 25, 50, 75, 100, 125, 100, 75, 50, 25, 0},
                     {0, 25, 50, 75, 100, 125, 100, 75, 50, 25, 0},
                     {0, 25, 50, 75, 100, 125, 100, 75, 50, 25, 0}};
int cont=0;
int t1=0;
void draw(){
  byte[] msg=new byte[6];
  
  msg[0] = (byte) 0xff;
  msg[1] = (byte) ID;
  msg[2] = (byte) (0 | velocidades[0][cont]);
  msg[3] = (byte) (0 | velocidades[1][cont]);
  msg[4] = (byte) (0 | velocidades[2][cont]);
  msg[5] = (byte) 0x01;
  
  myPort.write(msg);
  
  if(millis()-t1>=2000){
      if(cont<10) cont++;
      
      t1=millis();
  }
}
