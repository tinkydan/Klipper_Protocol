//Klipper protocol decoder
signed long max_int[5] = { 95, 12287, 1572863, 201326591, 4294967295 };    // 25769803775, 3298534883327, 422212465065983};
signed long min_int[7] = { -32, -4096, -524288, -67108864, -2147483648 };  // -17179869184, -2199023255552 };
int64_t VLQ(byte inBytes[], int length) {
  bool bitvec[];

  for (int i = 0; i < length; i++) {
    for (int j = 0; j < 7; j++) {
      bitvec[i * 7 + j] = bitRead(inBytes[length - 1 - i], j);
    }
  }
  int64_t stand_I = 0;
  for (int k = 0; k < (length * 7); k++) {
    bitSet(stand_I, k) = bitvec[k];
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

byte EncodeVLQ(int64_t Value) {


  for (int i = 0; i < 5; i++) {
    if ((Value <= max_int[i]) && (Value >= min_int[i])) {
      byte Encoded[i + 1] int num_byte = i + 1;

      if (Value < 0) {
        Value = Value - min_int[num_byte - 1] + 1 + max_int[num_byte - 1]
      }

      for (int t = num_byte - 1; t > 0; t--)
        bitSet(Encoded[t], 7) = 1;
      for (int u = 0; u < 7; u++) {
        bitSet(Encoded[t], u) = bitRead(Value, t * 7 + u);
        ;
      }
    }
  }
  bitSet(Encoded[num_byte], 7) = 0;
  return Encoded;
}
