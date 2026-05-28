
//.. uppdated for  non blocking

void Serial_Parse() {
  int inByte1;
  //.   byte ByteMSG[64 - 3];
  //  byte ByteTrail[3];
  if (MySerial0.available()) {
    if ((millis() - Serial_MSG) > MSG_Timeout) {
      first_Byte = 1;
    }
    if (first_Byte) {
      bytePOS1 = 0;
      first_Byte = 0;
      inByte = MySerial0.read();
      Serial_MSG = millis();
      breakbreak = 0;
      if ((inByte < 5) || (inByte == 126)) {
        first_Byte = 1;  // not an acceptable length
      }
      if ((inByte > 64) && (inByte != 126)) {

        while (MySerial0.available()) {
          inByte = MySerial0.read();
          if (inByte == 126) {
            first_Byte = 1;
            break;
          }
        }
        // Read until 126 is encountered or serial is not avalible
      }
      Message1[bytePOS1] = inByte;
    } else if ((millis() - Serial_MSG) > MSG_Timeout) {
      // Read timmed out
      first_Byte = 1;
      Process_MSG1();  //ByteMSG, ByteTrail, inByte1);
                       //@////p//SerialPtLnDebug(//@//Bytesall);
    } else {

      while (MySerial0.available() && !first_Byte) {  // Removed for redundancy  && ((millis() - Serial_MSG) > MSG_Timeout) && !first_Byte   timeout probably not need since serial is avalble in the buffer
        bytePOS1++;
        if (bytePOS1 <= (inByte - 4)) {
          Message1[bytePOS1] = MySerial0.read();
        } else {
          Trailer1[bytePOS1 - inByte + 3] = MySerial0.read();
        }
        if (bytePOS1 >= (inByte - 1)) {
          first_Byte = 1;

          Process_MSG1();  //ByteMSG, ByteTrail, inByte1);
          if (Trailer1[bytePOS1 - inByte + 3] != 126) {
            while (MySerial0.available()) {
              inByte = MySerial0.read();
              //p//SerialPtDebug(String(inByte) + " ");
              if (inByte == 126) {
                break;
              }
            }
            //p//SerialPtLnDebug();
            // Read until 126 is encountered or serial is not avalible
          }
        }
      }
    }
  }
}





//.. uppdated for  non blocking

void Serial_Parse2() {
  int inByte2;
  if (MySerial1.available()) {
    if ((millis() - Serial_MSG2) > MSG_Timeout) {
      first_Byte2 = 1;
      //  Serial.println("settign new serial2 ");
    }
    if (first_Byte2) {
      bytePOS2 = 0;
      first_Byte2 = 0;
      inBytet = MySerial1.read();
      Serial_MSG2 = millis();
      breakbreak = 0;
      if ((inBytet < 5) || (inBytet == 126)) {
        first_Byte2 = 1;  // not an acceptable length
      }
      if ((inBytet > 64) && (inBytet != 126)) {
        while (MySerial1.available()) {
          inBytet = MySerial1.read();
          if (inBytet == 126) {
            first_Byte = 1;
            break;
          }
        }
        // Read until 126 is encountered or serial is not avalible
      }
      Message2[bytePOS2] = inBytet;
    } else if ((millis() - Serial_MSG2) > MSG_Timeout) {
      // Read timmed out
      first_Byte2 = 1;
      Process_MSG2();  //ByteMSG, ByteTrail, inBytet1);
    } else {
      while (MySerial1.available() && !first_Byte2) {  // Removed for redundancy  && ((millis() - Serial_MSG) > MSG_Timeout) && !first_Byte   timeout probably not need since serial is avalble in the buffer
        bytePOS2++;
        if (bytePOS2 <= (inBytet - 4)) {
          Message2[bytePOS2] = MySerial1.read();
        } else {
          Trailer2[bytePOS2 - inBytet + 3] = MySerial1.read();
        }

        if (bytePOS2 >= (inBytet - 1)) {
          first_Byte2 = 1;
          Process_MSG2();  //ByteMSG, ByteTrail, inByte1);
          if (Trailer[bytePOS2 - inBytet + 3] != 126) {
            while (MySerial1.available()) {
              inBytet = MySerial1.read();
              if (inBytet == 126) {
                break;
              }
            }
          }
        }
      }
    }
  }
}
