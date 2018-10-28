#ifndef SerialCommunication_h
#define SerialCommunication_h

#define MSG_SIZE 6
#define START 0x4D      //byte de start 'M'
#define FINAL 0x1

class SerialCommunication{
public:
	SerialCommunication(int);
	bool read(char []);
	void begin();
	void ajustArray(char []);

private:
	int _baud;
};

#endif