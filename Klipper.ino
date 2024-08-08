Klipper protocol decoder
signed long max_int[5]={95, 12287, 1572863, 201326591, 4294967295};
signed long min_int[5]={-32, -4096, -524288, -67108864, -2147483648};
int64_t VLQ(Byte* inBytes int length){
bool bitvec[];

for (int i = 0; i < length; i++) {
  for (int j = 0; j < 7 ; j++){
    bitvec[i*7+j]=bitRead(inBytes[length-1-i], j);  
  }
}
int64_t stand_I=0;
  for (int k = 0 ; k < (length*7) ; k++){
    bitSet(stand_I, k)=bitvec[k];}

if (max_int[length-1]<stand_I){

  stand_I=stand_I-max_int[length-1]-1+min_int[length-1];
}
//  -32 .. 95	1
//-4096 .. 12287	2
//-524288 .. 1572863	3
//-67108864 .. 201326591	4
//-2147483648 .. 4294967295	5
  
}
