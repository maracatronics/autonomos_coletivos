#include <SerialCommunication.h>
#include <Radio.h>
#include <FastCRC.h>

FastCRC16 CRC16;

SerialCommunication serial(38400);
Radio radio(0, 109, "TX");            //Módulo, canal, modo

bool crc_check(char msg[SIZE_MSG]);

void setup(){
  serial.begin();
  radio.setup();
}

void loop(){
  char msg[7];
  
  if(serial.read(msg) && msg[0] == START && crc_check(msg)){       
    radio.send(true, msg_c);    // Envia mensagem recebida    
  }
  else{
    radio.send(false, msg_c); 
  }
}

// Checks if CRC is OK
bool crc_check(char msg[SIZE_MSG]){
  uint8_t msg_crc[SIZE_MSG];
  for(int i=0; i < 7; i++){
    msg_crc[i] = msg[i];
  }
  
  return (CRC16.xmodem(msg_crc, sizeof(msg_crc)) == 0);
}
