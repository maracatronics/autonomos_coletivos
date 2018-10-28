#include <SerialCommunication.h>
#include <Radio.h>

SerialCommunication serial(38400);
Radio radio(3, 3, "TX"); //(Módulo, Canal, Modo(TX/RX))

void setup(){
  radio.setup();
  serial.begin();
}

void loop(){
  char msg[MSG_SIZE];

  boolean msgOk = serial.read(msg);

  radio.send(msgOk, msg);
}
