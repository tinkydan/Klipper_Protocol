int MSG_Timeout=3; // miliseconds for the 64byte (max time to read the message)
bool first_Byte = 1;
int bytePOS=0;

.. uppdated for  non blocking 




 if (Serial.available()) {
    
   if (first_Byte){
     bytePOS=0;     
      inByte = Serial.read();
      //Bytesall="SERIAL 1 " + String(inByte) + " ";
      Serial_MSG = millis();
      breakbreak = 0;
      int inByte1=inByte;
     if (inByte1>64){inByte1=64;}
      byte ByteMSG[inByte1];
      ByteMSG[bytePOS]=inByte;
     
   }
     else if (millis() - Serial_MSG) > MSG_Timeout){
           // Read timmed out
            first_Byte=0;
            Process_MSG(ByteMSG);
     } 
   else{
      while (Serial.available()==0 ) {  // Removed for redundancy  && ((millis() - Serial_MSG) > MSG_Timeout) && !first_Byte   timeout probably not need since serial is avalble in the buffer
          bytePOS++;
          ByteMSG[bytePO]=Serial.read();
          //Bytesall+=String(ByteMSG[bytePO]) + " ";
        
        if (bytePOS >= (inByte1-1)){
            first_Byte=0;
            Process_MSG(ByteMSG);
          // Serial.println(Bytesall);
    }
   
        }
      }
   }

   
    
