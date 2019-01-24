import processing.serial.*;
 
// The serial port:
Serial myPort;
String dataReading = "";
String [] dataOutput = {};
 
void setup() {
size(500,500);
 
// Open the port you are using at the rate you want:
myPort = new Serial(this, Serial.list()[0], 38400);
//in my case,the Serial port the Arduino is connected to is 9th on the serial list, hence the [8]
//to get access to the serial list you can use >> println(Serial.list());
myPort.bufferUntil('\n');
 
}
 
void draw() {

}
 
void serialEvent(Serial myPort) {
 dataReading = myPort.readString();
 if(dataReading!=null){
   String[] newDataReading=split(dataReading, '\n');
    println(newDataReading[0]);
    dataOutput = append(dataOutput, newDataReading[0]);
    saveData(); 
  } 
}
 
 
void saveData() {
  saveStrings("PID/calibracao(1).txt", dataOutput); 
}