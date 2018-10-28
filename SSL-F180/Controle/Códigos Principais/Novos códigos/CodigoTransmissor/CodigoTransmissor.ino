#include <SerialCommunication.h>
#include <Radio.h>

#define tempoDelay 1000
#define tempoDelay2 1090

SerialCommunication serial(38400);
Radio radio(0, 0, "TX");            //Módulo, canal, modo

void setup(){
  serial.begin();
  radio.setup();
}

void loop(){
  static unsigned long tempo = millis();
  char msg[MSG_SIZE];
      

  if(serial.read(msg)){
    if(millis() - tempo >= tempoDelay && millis() - tempo <= tempoDelay2)
      msg[1] |= 0x80;
    else if(millis() - tempo > tempoDelay2)
      tempo = millis();
    else
      msg[1] &= 0x7F;
      
    radio.send(true, msg);      
  }

  else{
    radio.send(false, msg); 
  }
}
