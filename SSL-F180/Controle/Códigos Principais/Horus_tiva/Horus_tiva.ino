#include <Modbus.h>

// Inclui as bibliotecas refentes ao radio
#include <Radio.h> 
#include <string.h>   

#define DEVICE_ID 1         // Modbus
#define PROTOCOL_SIZE 8     //

#define REC_PROTOCOL_SIZE 6 //-------------------------------------------------------
#define CHANNEL 2           //
#define START 'H'           //Radio
#define STOP 'M'            //
#define SPIMOD 3            //-------------------------------------------------------

Radio radio(2, "RX");
unsigned char receive_frame[PROTOCOL_SIZE];

unsigned char sendFrame[37];
int size = 0;
int i = 0;
bool state = false;


unsigned char sendFrame1[37];


enum{
    RBT1,
    RBT2,
    RBT3,
    RBT4,
    robots
};

enum{
    ID,
    BAT,
    CAP,
    POS,
    DRIBLE,
    amount
};

unsigned char HOLDING_REGS[robots][amount];
unsigned long updateTime[robots];

Modbus device(SLAVE, DEVICE_ID);

void receberDados(char receivedFrame[]);
void gravarRegistradores();

void setup() {
    Serial.begin(9600);
    radio.setup();
    
    for (int j = 0; j < robots; j++){
      for (int k = 0; k < amount; k++){
          HOLDING_REGS[j][k] = 0;
      }
    }

    //device.setNumberOfRegs(amount*robots);

}

void loop() {
    Serial.println("oi");
    char receivedFrame[REC_PROTOCOL_SIZE] = {0}; 
    if(radio.receive(receivedFrame, 6)){
      /*Serial.print((char)receivedFrame[0]);
      Serial.print(" ");
      Serial.print((int)receivedFrame[1]);
      Serial.print(" ");
      Serial.print((int)receivedFrame[2]);
      Serial.print(" ");
      Serial.print((int)receivedFrame[3]);
      Serial.print(" ");
      Serial.print((int)receivedFrame[4]);
      Serial.print(" ");
      Serial.print((int)receivedFrame[5]);
      Serial.print(" ");
      Serial.println((char)receivedFrame[6]);*/
      
      receberDados(receivedFrame);
    }

    gravarRegistradores();

    // for (int j = 0; j < 20; j++){
    //     Serial.print((int)device.getHoldingRegs(j));
    // }

    // Serial.println("");

    if(Serial.available()){
      unsigned char a = Serial.read();
      receive_frame[i] = a;
      //Serial.print((int)a);
      i++;

      

      if(i>=PROTOCOL_SIZE){
        device.handle_modbus(receive_frame, PROTOCOL_SIZE);
        size = device.getSendFrameSize();
        //Serial.println((int)size);
        //sendFrame = (unsigned char*) calloc(size, sizeof(unsigned char));

        for (int j = 0; j < size; j++){
          sendFrame[j] = device.getSendFrame(j);
          //Serial.print(sendFrame[j]);
          //Serial.write(sendFrame[j]);
        }
        i=0;
      }
   }
  
}

//-------------------------------------------------------------------------------------------------------------------

void receberDados(char receivedFrame []){
  
  if (receivedFrame[0] != START){
      return;
  }

//   else{
//      Serial.print((char)receivedFrame[0]);
//      Serial.print(" ");
//      Serial.print((int)receivedFrame[1]);
//      Serial.print(" ");
//      Serial.print((int)receivedFrame[2]);
//      Serial.print(" ");
//      Serial.print((int)receivedFrame[3]);
//      Serial.print(" ");
//      Serial.print((int)receivedFrame[4]);
//      Serial.print(" ");
//      Serial.print((int)receivedFrame[5]);
//      Serial.print(" ");
//      Serial.println((char)receivedFrame[6]);
//   }


  if (receivedFrame[1] == HOLDING_REGS[RBT1][ID]){
      for (int j = 1; j < amount; j++){
            HOLDING_REGS[RBT1][j] = receivedFrame[j+1];
        }
      updateTime[RBT1] = 0;
      //Serial.println("H1");
  }

  else if (receivedFrame[1] == HOLDING_REGS[RBT2][ID]){
      for (int j = 1; j < amount; j++){
            HOLDING_REGS[RBT2][j] = receivedFrame[j+1];
        }
      updateTime[RBT2] = 0;
      //Serial.println("H2");
  }

  else if (receivedFrame[1] == HOLDING_REGS[RBT3][ID]){
      for (int j = 1; j < amount; j++){
            HOLDING_REGS[RBT3][j] = receivedFrame[j+1];
        }
      updateTime[RBT3] = 0;
      //Serial.println("H3");
  }

  else if (receivedFrame[1] == HOLDING_REGS[RBT4][ID]){
      for (int j = 1; j < amount; j++){
            HOLDING_REGS[RBT4][j] = receivedFrame[j+1];
        }
      updateTime[RBT4] = 0;
      //Serial.println("H4");
  }


  else if ((HOLDING_REGS[RBT1][ID] == 0) || (updateTime[RBT1] == 0) || (updateTime[RBT1] == 4294967290)){
      for (int j = 0; j < amount; j++){
            HOLDING_REGS[RBT1][j] = receivedFrame[j+1];
        }
      updateTime[RBT1] = 0;
      //Serial.println("H5");
  }

  else if ((HOLDING_REGS[RBT2][ID] == 0) || (updateTime[RBT2] == 0) || (updateTime[RBT2] == 4294967290)){
      for (int j = 0; j < amount; j++){
                  HOLDING_REGS[RBT2][j] = receivedFrame[j+1];
              }
        updateTime[RBT2] = 0;
        //Serial.println("H6");
  }

  else if ((HOLDING_REGS[RBT3][ID] == 0) || (updateTime[RBT3] == 0) || (updateTime[RBT3] == 4294967290)){
      for (int j = 0; j < amount; j++){
                  HOLDING_REGS[RBT3][j] = receivedFrame[j+1];
              }
        updateTime[RBT3] = 0;
        //Serial.println("H7");
  }

  else if ((HOLDING_REGS[RBT4][ID] == 0) || (updateTime[RBT4] == 0) || (updateTime[RBT4] == 4294967290)){
      for (int j = 0; j < amount; j++){
                  HOLDING_REGS[RBT4][j] = receivedFrame[j+1];
              }
        updateTime[RBT4] = 0;
        //Serial.println("H8");
  }

    /*else{
      for (int j = 0; j < robots; j++){
      if (HOLDING_REGS[j][ID]==0){
          HOLDING_REGS[j][ID] == receivedFrame[1];
          for (int k = 1; k < amount; k++){
            HOLDING_REGS[j][k] = receivedFrame[k+1];
        }
      }
      break;
    }
  }*/

  for (int j =0; j < robots; j++){
      if (updateTime[j] >= 4294967290){
          updateTime[j] = 4294967290;
      }
      else{
          updateTime[j]++;
      }

  }
}

void gravarRegistradores(){
    int index = 0;
    for (int j = 0; j < robots; j++){
        for (int k = 0; k < amount; k++){
            device.setHoldingRegs((int)HOLDING_REGS[j][k] , index);
            //Serial.print((int)HOLDING_REGS[j][k]);
            index++;
        }
    }
    index = 0;
   // Serial.println("");
}


