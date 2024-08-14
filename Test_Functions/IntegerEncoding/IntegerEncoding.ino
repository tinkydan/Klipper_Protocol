/*
  Reading a serial ASCII-encoded string.

  This sketch demonstrates the Serial parseInt() function.
  It looks for an ASCII string of comma-separated values.
  It parses them into ints, and uses those to fade an RGB LED.

  Circuit: Common-Cathode RGB LED wired like so:
  - red anode: digital pin 3 through 220 ohm resistor
  - green anode: digital pin 5 through 220 ohm resistor
  - blue anode: digital pin 6 through 220 ohm resistor
  - cathode: GND

  created 13 Apr 2012
  by Tom Igoe
  modified 14 Mar 2016
  by Arturo Guadalupi

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/ReadASCIIString
*/
int VQL_len=0;
  byte Encoded[5];
// pins for the LEDs:

//Klipper protocol decoder
int64_t max_int[5] = { 95, 12287, 1572863, 201326591, 4294967295 };    // 25769803775, 3298534883327, 422212465065983};
int64_t min_int[7] = { -32, -4096, -524288, -67108864, -2147483648 };  // -17179869184, -2199023255552 };
int64_t VLQ(byte inBytes[5], int length) {
  bool bitvec[64];

  for (int i = 0; i < length; i++) {
    for (int j = 0; j < 7; j++) {
      bitvec[i * 7 + j] = bitRead(inBytes[length - 1 - i], j);
      Serial.print(String(bitvec[i * 7 + j]) + " " );
    }
  }
  int64_t stand_I = 0;
  for (int k = 0; k < (length * 7); k++) {
   // bitSet(stand_I, k) = bitvec[k];
    bitWrite(stand_I, k,  bitvec[k]);
  }

  if (max_int[length - 1] < stand_I) {
    stand_I = stand_I - max_int[length - 1] - 1 + min_int[length - 1];
  }
  //  -32 .. 95	1
  //-4096 .. 12287	2
  //-524288 .. 1572863	3
  //-67108864 .. 201326591	4
  //-2147483648 .. 4294967295	5
  return stand_I;
}

void EncodeVLQ(int64_t Value) {
  Serial.println("Encoding " +String(Value));
 bool first=1;
  int num_byte;
  byte holdb;
  uint64_t Unsinged_Val;

  for (int i = 0; i < 5; i++) {
    Serial.println("Looping I " +String(i));
    if ((Value <= max_int[i]) && (Value >= min_int[i])&&first) {
      //byte Encoded[i + 1];
      first=0;
      num_byte = i + 1;
      VQL_len=num_byte;
    Serial.println("Encoding " +String(num_byte));
      if (Value < 0) {
        Value = Value - min_int[num_byte - 1] + 1 + max_int[num_byte - 1];
      }
 Serial.println("Unsigned Value " +String(Value));
 Unsinged_Val=Value;
      for (int t = num_byte -1 ; t >= 0; t--) {
        Serial.println("Looping t " +String(t));
        holdb=Encoded[t];
        //bitSet(holdb, 7) = 1;
        bitWrite(holdb, 7,1);
        for (int u = 0; u < 7; u++) {
          bool bitval = bitRead(Unsinged_Val, (num_byte-1-t) * 7 + u);
          Serial.print(String(u) + "_" +String(bitval) +" ");
        //  bitSet(holdb, u) = bitval;
          bitWrite(holdb, u, bitval);
          Serial.print(holdb,HEX);
          Serial.print(" < ");
        }
        Encoded[t]=holdb;
      }
    }
  }
  holdb=Encoded[num_byte];
 // bitSet( holdb, 7) = 0;
  bitWrite(holdb, 7, 0);
  Encoded[num_byte]=holdb;
  //holdb
 // return Encoded;
}


void setup() {
  // initialize serial:
  Serial.begin(250000);
  // make the pins outputs:
Serial.println("working");
}

void loop() {

  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    int32_t Value = Serial.parseInt();
    // do it again:

Serial.println("Received: " + String(Value));
    // look for the newline. That's the end of your sentence:
    if (Serial.read() == '\n') {
      // constrain the values to 0 - 255 and invert
      // if you're using a common-cathode LED, just use "constrain(color, 0, 255);"
Serial.println("Encoding: ");

      // print the three numbers in one string as hexadecimal:
      EncodeVLQ(Value) ;
      for (int j = 0; j < VQL_len ; j++){
      Serial.println(Encoded[j],HEX);
      }
      Serial.println("Transformedbacl  " + String(VLQ(Encoded,VQL_len )) );
    }
  }
}
