#include <SerialCommunication.h>
#include <Radio.h>

SerialCommunication serial(38400);
Radio radio(0, 0, "TX");

void setup(){
  serial.begin();
  radio.setup();
}

void loop(){
  char msg[MSG_SIZE] = {'M', 3, 100, 100, 100, 1};
    
  radio.send(true, msg);
}
