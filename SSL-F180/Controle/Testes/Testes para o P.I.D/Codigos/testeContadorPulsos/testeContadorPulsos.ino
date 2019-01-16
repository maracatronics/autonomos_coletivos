uint8_t pinsHall[3] = {PB_2, PE_0, PF_0};        
unsigned long tempo;
int qntPulsos = 0;


void setup() {
  Serial.begin(9600);
  for(int i = 0; i < 3; i++)
    pinMode(pinsHall[i], INPUT);
}

void loop() {
  tempo = pulseIn(pinsHall[0], HIGH);
  if(tempo > 0){
    qntPulsos++;
    Serial.println(qntPulsos);
  }
}
