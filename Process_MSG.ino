
int64_t ProcessNextInt() {
  byte ByteComb[5];
  int VQLp = 0;
  while ((Message[MessagePOS] > 127)) {
    ByteComb[VQLp] = Message[MessagePOS];
    //Serial.println(String(ByteComb[VQLp]) + " VariableIntPos " + String(VQLp));
    VQLp++;
    MessagePOS++;
  }

  //if ((VQLp == 0)||( VQLp == 4)) {
  ByteComb[VQLp] = Message[MessagePOS];
  //  Serial.println(String(ByteComb[VQLp]) + " VariableIntPos Single " + String(VQLp));
  MessagePOS++;
  //}

  int64_t IntVal = VLQ(ByteComb, VQLp + 1);
  return IntVal;
}

void Process_MSG() {  //byte Message[], byte Trailer[],int lenh) {
  MessagePOS = 2;
  byte ByteComb[5];
  SequenceN = Message[1];
  uint16_t checkSum = calcCRC16(Message, Message[0] - 3, 0x1021, 0xFFFF, 0x0000, true, true);
  Serial.println(checkSum, HEX);
  uint16_t combined = (Trailer[0] << 8) + Trailer[1];
  Serial.println(String(SequenceN) + "   CheckSumCal:" + String(checkSum) + "   CheckSumComb:" + String(combined) + "   Trailer_0:" + String(Trailer[0]) + "   Trailer_1:" + String(Trailer[1]));

  if (checkSum == combined) {

    while (MessagePOS < Message[0] - 3) {

      //MessagePOS++;
      //ByteComb[0]=Message[MessagePOS];
      //MessagePOS++;
      int FunctionIDpos = Message[MessagePOS];  //VLQ(ByteComb,1);
      int FunctionID = ProcessNextInt();        //VLQ(ByteComb,1);
      for (int u = 0; u < firstInt[FunctionIDpos]; u++) {
        //  Serial.println(" U iter:" + String(u) + "   integer V:"+ String(IntVals[u]) + "   next byte:"+ String(Message[MessagePOS] )   +"   Number of int1: " + String(firstInt[FunctionIDpos]) );
        IntVals[u + 1] = ProcessNextInt();
      }


      for (int y = 0; y < numString[FunctionIDpos]; y++) {

        int StrLength = ProcessNextInt();
        StrVals[y + 1] = "";
        for (int t = 0; t < StrLength; t++) {
          StrVals[y + 1] += Message[MessagePOS];
          MessagePOS++;
        }
      }

      for (int u = firstInt[FunctionIDpos]; u < firstInt[FunctionIDpos] + secondInt[FunctionIDpos]; u++) {

        IntVals[u + 1] = ProcessNextInt();
      }

      Run(FunctionID);
      Serial.println("Completed Parsing Message after " + String(millis() - Serial_MSG) + "ms");
    }


    //! send AK
    setup_reply();
    finish_reply();
  } else {

    // !send NAK
    int seqHold = SequenceN;


    SequenceN = SequenceN - 2;
    if (SequenceN < 16) {
      SequenceN = SequenceN + 16;
    }
    setup_reply();
    finish_reply();
    SequenceN = seqHold;
  }
}
