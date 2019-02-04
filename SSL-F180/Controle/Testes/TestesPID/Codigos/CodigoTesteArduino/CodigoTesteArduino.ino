#define HALL_1 1
#define HALL_2 2

int qntPulsosTotal[3] = {0};
boolean interruptRoda1 = true, interruptRoda2 = true, interruptRoda3 = true;
unsigned long tempoPulso1 = 0, tempoPulso2 = 0, tempoPulso3 = 0;

void contagemPulsos1();
void contagemPulsos2();

void setup() {
  //Serial.begin(9600); 
  Serial.begin(38400);
  pinMode(HALL_1, INPUT);
  pinMode(HALL_2, INPUT);
  attachInterrupt(digitalPinToInterrupt(HALL_1), contagemPulsos1 , CHANGE);
  attachInterrupt(digitalPinToInterrupt(HALL_2), contagemPulsos2 , CHANGE);

}

void loop() {
  // put your main code here, to run repeatedly:

}


void contagemPulsos1() {
  if (interruptRoda1) {
    tempoPulso1 = micros();
    interruptRoda1 = false;
  } else {
    tempoPulso1 = micros() - tempoPulso1;
    if (tempoPulso1 >= INTERVALO_MINIMO){
      qntPulsosTotal[0]++;
      interruptRoda1 = true;
    } else {
       interruptRoda1 = true;
    }
  }
}

void contagemPulsos2() {
  if (interruptRoda2) {
    tempoPulso2 = micros();
    interruptRoda2 = false;
  } else {
    tempoPulso2 = micros() - tempoPulso2;
    if (tempoPulso2 >= INTERVALO_MINIMO){
      qntPulsosTotal[1]++;
      interruptRoda2 = true;
    } else {
       interruptRoda2 = true;
    }
  }
}
