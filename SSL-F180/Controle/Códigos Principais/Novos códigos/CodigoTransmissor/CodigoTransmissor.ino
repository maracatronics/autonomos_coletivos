#include <SerialCommunication.h>
#include <Radio.h>
#include <FastCRC.h>


#define tempoDelay 1000
#define tempoDelay2 1090

FastCRC16 CRC16;

SerialCommunication serial(38400);
Radio radio(0, 109, "TX");            //Módulo, canal, modo

void setup(){
  serial.begin();
  radio.setup();
}

bool isChecksumOk(char msg[]) {
  return (msg[6] == (msg[0] ^ msg[1] ^ msg[2] ^ msg[3] ^ msg[4] ^ msg[5]));
}

void loop(){
  uint8_t crc;
  static unsigned long tempo = millis();
  uint8_t msg[7]; // message size  + 1 (checksum) 
  char msg_c[9];

  for(int i; i<sizeof(msg); i++){ //Copiamos a mensagem para um vetor char.
      msg_c[i] = msg[i];
  }

  crc = CRC16.xmodem(msg, sizeof(msg));

  msg_c[7] = crc/256;
  msg_c[8] = crc%256;
  
  if(serial.read(msg_c)){
    //if(millis() - tempo >= tempoDelay && millis() - tempo <= tempoDelay2)
    //  msg[1] |= 0x80;
    //else if(millis() - tempo > tempoDelay2)
    //  tempo = millis();
    //else
    //  msg[1] &= 0x7F; 
    if(msg_c[0] == START && msg_c[5] == FINAL && isChecksumOk(msg_c)) {
      radio.send(true, msg_c);
    }      
  }

  else{
    radio.send(false, msg_c); 
  }
}
