byte SequenceN = 0;
int firstInt[116] = { 2, 0, 0, 0, 0, 1, 0, 1, 0, 0, 3, 2, 2, 2, 3, 2, 5, 2, 1, 2, 2, 4, 5, 1, 8, 3, 2, 2, 4, 1, 8, 2, 2, 1, 1, 4, 1, 3, 1, 1, 1, 4, 1, 3, 3, 6, 2, 5, 4, 2, 1, 5, 1, 2, 5, 4, 3, 1, 1, 6, 1, 1, 8, 6, 5, 6, 3, 1, 2, 2, 1, 4, 3, 1, 2, 2, 1, 2, 2, 1, 2, 1, 6, 3, 2, 1, 2, 4, 1, 2, 3, 0, 0, 1, 2, 3, 2, 1, 4, 0, 1, 2, 4, 4, 3, 1, 1, 2, 1, 2, 4, 4, 2, 3, 6, 2 };
int numString[116] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 };
int secondInt[116] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

//int MessagePOS;
//byte Message[5];

int64_t IntVals[8];
String StrVals[2];

#include <FastCRC.h>
FastCRC16 CRC16;

int64_t ProcessNextInt() {
  byte ByteComb[5];
  int VQLp = 0;


  while ((Message[MessagePOS] > 127 )||( VQLp >= 5)) {
    ByteComb[VQLp] = Message[MessagePOS];
    VQLp++;
    MessagePOS++;
  }

  if (VQLp < 5) {
    ByteComb[VQLp] = Message[MessagePOS];
    MessagePOS++;
  }


  return VLQ(ByteComb, VQLp);
}

void Process_MSG(byte Message[], byte Trailer[]) {
  int MessagePOS = 2;
  SequenceN = Message[1];
  unit16_t checkSum = CRC16.ccitt(Message, sizeof(Message));
  uint16_t combined = (Trailer[0] << 8) + Trailer[1];
  if (checkSum == combined) {

    while (MessagePOS < sizeof(Message)) {
      MessagePOS++;
      int FunctionID = Message[MessagePOS];
      for (int u = 0; u < firstInt[FunctionID]; u++;) {
        IntVals[u] = ProcessNextInt();
      }
      for (int y = 0; y < numString[FunctionID]; y++;) {
        int StrLength = ProcessNextInt();
        StrVals[y] = "";
        for (int t = 0; t < StrLength; t++) {
          StrVals[y] += = Message[MessagePOS];
          MessagePOS++;
        }
      }
      for (int u = firstInt[FunctionID]; u < firstInt[FunctionID] + secondInt[FunctionID]; u++;) {
        IntVals[u] = ProcessNextInt();
      }
    }

//! send AK
  } else {

   // !send NAK
  }

