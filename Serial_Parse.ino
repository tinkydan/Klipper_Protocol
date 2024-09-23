
//.. uppdated for  non blocking

void Serial_Parse(){
  int inByte1;
  

     //.   byte ByteMSG[64 - 3];
    //  byte ByteTrail[3];
  if (Serial.available()) {
    if  ((millis() - Serial_MSG) > MSG_Timeout){
    first_Byte = 1;
   
   // Serial.println("settign new serial ");
}
    if (first_Byte) {
      bytePOS = 0;
      first_Byte=0;
      #ifdef StringDebug
        inByte = Serial.parseInt();
      #else
        inByte = Serial.read();
      #endif
      
      Bytesall="SERIAL 1 first byte " + String(inByte) + " ";
      Serial_MSG = millis();
      breakbreak = 0;
      //int inByte1 = inByte;

      if (inByte > 64) { inByte = 64; }
      if (inByte <5){
        first_Byte=1;// not an acceptable length
      }
      //byte ByteMSG[inByte1 - 3];
      //byte ByteTrail[3];
      Message[bytePOS] = inByte;
      SerialPtLnDebug(Bytesall);
 

    } 
    else if ((millis() - Serial_MSG) > MSG_Timeout){
        // Read timmed out
      first_Byte = 1;
        Process_MSG();//ByteMSG, ByteTrail, inByte1);
         SerialPtLnDebug(Bytesall);
      }
    else {
       
      while (Serial.available()&&!first_Byte) {  // Removed for redundancy  && ((millis() - Serial_MSG) > MSG_Timeout) && !first_Byte   timeout probably not need since serial is avalble in the buffer
        bytePOS++;
        //Serial.println(String(Serial_MSG) + "  Serial Message Time  " + String(millis()));
        if (bytePOS <= (inByte - 4)) {

         // Message[bytePOS] = Serial.read();
          #ifdef StringDebug
          Message[bytePOS] = Serial.parseInt();
          #else
          Message[bytePOS] = Serial.read();
          #endif

          //Serial.println(String(Message[bytePOS]));
          Bytesall+=String(Message[bytePOS]) + " ";
        } else {
         // Trailer[bytePOS] = Serial.read();
          #ifdef StringDebug
          Trailer[bytePOS-inByte+3] = Serial.parseInt();
           #else
           Trailer[bytePOS-inByte+3] = Serial.read();
           #endif
          //Serial.println(String(Trailer[bytePOS-inByte+3])+ "in byte " + String(bytePOS));
          Bytesall+=String( Trailer[bytePOS-inByte+3]) + " ";
        }

        if (bytePOS >= (inByte - 1)) {
          first_Byte = 1;
           SerialPtLnDebug(Bytesall);
           
//Serial.println(String(Message[0]) );
          Process_MSG();//ByteMSG, ByteTrail, inByte1);
         
        }
      }
    }
  }
}
