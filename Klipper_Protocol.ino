// 3ms is the longest time a 64byte message should take to send over the serial line


int inByte;
bool breakbreak = 0;

/*int bytv
 * There are three serial ports on the ESP known as U0UXD, U1UXD and U2UXD.
 * 
 * U0UXD is used to communicate with the ESP32 for programming and during reset/boot.
 * U1UXD is unused and can be used for your projects. Some boards use this port for SPI Flash access though
 * U2UXD is unused and can be used for your projects.
 * 
*/

//HardwareSerial Serial1(1);
//HardwareSerial Serial2(1);
//#define RXD1 7
//#define TXD1 6
//#define RXD2 5
//#define TXD2 4

// below script redefines the bitRead and bitWrite functions to be compatible with int64_t valuse so that a uint32_t value cane be properly encoded

#undef bitRead
#undef bitWrite

template<typename T> void bitWrite(T& value, byte bit, byte val);  // prototype
template<typename T> void bitWrite(T& value, byte bit, byte val) {
  if (val)
    value |= (T(1) << bit);
  else
    value &= ~(T(1) << bit);
}

template<typename T> bool bitRead(T value, byte bit);  // prototype
template<typename T> bool bitRead(T value, byte bit) {
  return (value & ((T)1 << bit)) != 0;
}


void setup() {
  // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  Serial.begin(250000); 

  //  Serial1.begin(250000, SERIAL_8N1, RXD1, TXD1);
  //  Serial2.begin(250000, SERIAL_8N1, RXD2, TXD2);
  // Serial.println("Begun");
}

void loop() {  //Choose Serial1 or Serial2 as required
  //Serial_Parse(); 

}