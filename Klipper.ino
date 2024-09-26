


//#define DEBUG_Command


#ifdef DEBUG_Command_VQL
#define SerialPtVQL(x) Serial2.print(x)
#define SerialPtLnVQL(x) Serial2.println(x)
#else
#define SerialPtVQL(x)
#define SerialPtLnVQL(x)
#endif





// Decode the VLQ value to an int64_t (generally donconverted to a int32 or a uint32)
int64_t VLQ(byte inBytes[5], int length) {
  bool bitvec[64];

  for (int i = 0; i < length; i++) {
    for (int j = 0; j < 7; j++) {
      bitvec[i * 7 + j] = bitRead(inBytes[length - 1 - i], j);
      SerialPtVQL(String(bitvec[i * 7 + j]) + " ");
    }
  }
  int64_t stand_I = 0;
  for (int k = 0; k < (length * 7); k++) {
    // bitSet(stand_I, k) = bitvec[k];
    bitWrite(stand_I, k, bitvec[k]);
  }

  if (max_int[length - 1] < stand_I) {
    stand_I = stand_I - max_int[length - 1] - 1 + min_int[length - 1];
  }
  //  -32 .. 95	1
  //-4096 .. 12287	2
  //-524288 .. 1572863	3
  //-67108864 .. 201326591	4
  //-2147483648 .. 4294967295	5
  SerialPtLnVQL("Integer Value " + String(stand_I));
  return stand_I;
}

// Encode and integer (int64_t) into a byte VQL
void EncodeVLQ(int64_t Value) {
  SerialPtLnVQL("Encoding " + String(Value));
  bool first = 1;
  int num_byte;
  byte holdb;
  uint64_t Unsinged_Val;

  for (int i = 0; i < 7; i++) {
    SerialPtLnVQL("Looping I " + String(i));
    if ((Value <= max_int[i]) && (Value >= min_int[i]) && first) {
      //byte Encoded[i + 1];
      first = 0;
      num_byte = i + 1;
      VQL_len = num_byte;
      SerialPtLnVQL("Encoding " + String(num_byte));
      if (Value < 0) {
        Value = Value - min_int[num_byte - 1] + 1 + max_int[num_byte - 1];
      }
      SerialPtLnVQL("Unsigned Value " + String(Value));
      Unsinged_Val = Value;
      for (int t = num_byte - 1; t >= 0; t--) {
        SerialPtLnVQL("Looping t " + String(t));
        holdb = Encoded[t];
        //bitSet(holdb, 7) = 1;
        bitWrite(holdb, 7, 1);
        for (int u = 0; u < 7; u++) {
          bool bitval = bitRead(Unsinged_Val, (num_byte - 1 - t) * 7 + u);
          SerialPtVQL(String(u) + "_" + String(bitval) + " ");
          //  bitSet(holdb, u) = bitval;
          bitWrite(holdb, u, bitval);
          SerialPtVQL(holdb);
          SerialPtVQL(" < ");
        }
        Encoded[t] = holdb;
      }
    }
  }
  holdb = Encoded[num_byte - 1];
  // bitSet( holdb, 7) = 0;
  bitWrite(holdb, 7, 0);
  Encoded[num_byte - 1] = holdb;

  //holdb
  // return Encoded;
}

void EncodeIntoReply(int64_t Value){
  EncodeVLQ(Value);
  //SerialPtDebug("Int:" + String(Value) +" Was Encoded as follows -> ") ;
  for (int ui=0; ui<VQL_len ; ui++){
    reply[rpl_j]=Encoded[ui];
    //SerialPtDebug(" " + String(reply[rpl_j]));
    rpl_j++;
  }
 // SerialPtLnDebug() ;
}






void setup_reply() {
int indc=0;
  while((responding==1)&&(indc<2000)){
    indc++;
  }
  if (indc==2000){
    finish_reply(); // response hanging will be terminated
  }

  responding=1;
  rpl_j = 2;
  
  reply[1] = SequenceN + 1;
  if (reply[1] >= 32) {
     reply[1] = 16;

  }

}





void finish_reply() {
  reply[0] = rpl_j + 3;
  CRCV = calcCRC16(reply, rpl_j, 0x1021, 0xFFFF, 0x0000, true, true);
  reply[rpl_j] = highByte(CRCV);
  rpl_j++;
  reply[rpl_j] = lowByte(CRCV);
  rpl_j++;
  reply[rpl_j] = 126;
  rpl_j++;

  for (int i = 0; i < rpl_j; i++) {
        SerialPtCom(String(reply[i]) + " ");
  #ifdef StringDebug
    Serial.print(String(reply[i]) + " ");
  #else
    Serial.write(reply[i]);
  #endif
  }
  #ifdef StringDebug
  Serial.println("");
  #endif
   SerialPtLnCom("");
  responding=0;
}