


// 3ms is the longest time a 64byte message should take to send over the serial line

/* 
int inByte;
bool breakbreak = 0;
*/
/*int bytv
 * There are three serial ports on the ESP known as U0UXD, U1UXD and U2UXD.
 * 
 * U0UXD is used to communicate with the ESP32 for programming and during reset/boot.
 * U1UXD is unused and can be used for your projects. Some boards use this port for SPI Flash access though
 * U2UXD is unused and can be used for your projects.
 * 
*/
/*
String Bytesall;

unsigned long Serial1_MSG;
unsigned long Serial2_MSG;
//HardwareSerial Serial1(1);
//HardwareSerial Serial2(1);
//#define RXD1 7
//#define TXD1 6
//#define RXD2 5
//#define TXD2 4

void setup() {
  // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  Serial.begin(250000); 
  Serial1.begin(28800);
  Serial2.begin(28800);
  //  Serial1.begin(250000, SERIAL_8N1, RXD1, TXD1);
  //  Serial2.begin(250000, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Begun");
}

void loop() {  //Choose Serial1 or Serial2 as required




 if (Serial1.available()) {
    inByte = Serial1.read();
    //Serial.print("SERIAL 1: " + String(inByte) + " ");
    Bytesall="SERIAL 1 " + String(inByte) + " ";
    Serial1_MSG = millis();
    breakbreak = 0;
    int inByte1=inByte;
    if (inByte1>64){inByte1=64;}
    for (int i = 1; i < inByte1; i++) {
      while (Serial1.available()==0) {
        if ((millis() - Serial1_MSG) > 30) {
          breakbreak = 1;
         break;
        }
      }
      if (breakbreak) {
        //Serial.print("  __TIMEOUT");
         Bytesall+="  __TIMEOUT";
       break;
      
      }
      inByte = Serial1.read();
      //Serial.print(String(inByte) + " ");
      Bytesall+=String(inByte) + " ";
    }
    Serial.println(Bytesall);
  }

if (Serial2.available()) {

    inByte = Serial2.read();
    //Serial.print("SERIAL 2: " + String(inByte) + " ");
    Bytesall="SERIAL 2: " + String(inByte) + " ";
    Serial2_MSG = millis();
    breakbreak = 0;
      int inByte1=inByte;
      if (inByte1>64){inByte1=64;}
       for (int i = 1; i < inByte1; i++) {
     while (Serial2.available()==0) {
        if ((millis() - Serial2_MSG) > 30) {
          breakbreak = 1;
         break;
        }
      }
      if (breakbreak) {
        //Serial.print("  __TIMEOUT");
        Bytesall+="  __TIMEOUT";
        break;
        
      }
      inByte = Serial2.read();
      //Serial.print(String(inByte) + " ");
      Bytesall+=String(inByte) + " ";
    }
    Serial.println(Bytesall);
  }
}

*/