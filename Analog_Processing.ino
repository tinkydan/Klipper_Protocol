
//int AnalogReadings[37][8];
//int AnalogMetaData[37][10];  // Active // PIn Num // OID  // Index // Sample Ticks // Sample Count // Rest_Ticks //Min_value  // Max_Value //  Range Check Count
//unsigned long AnalogTimmingData[37][2];
void AnalogReadTaskcode( void * parameter) {
  for (int Ch_num = 0; Ch_num < analogChannels; Ch_num++) {
    if (AnalogMetaData[Ch_num][0]==1){
      if ((micros() - AnalogTimmingData[Ch_num][0]) > AnalogMetaData[Ch_num][4]) {  //if channel is active and the time since the last sample is greater than hte sample ticks
        AnalogTimmingData[Ch_num][1] = micros();
        AnalogMetaData[Ch_num][3]++;
        if (AnalogMetaData[Ch_num][3] >= AnalogMetaData[Ch_num][5]) {  //if the sample index needed to be rolled over since it is at the total sample number
          AnalogMetaData[Ch_num][3] = 0;
        }
        AnalogReadings[Ch_num][AnalogMetaData[Ch_num][3]] = analogRead(AnalogMetaData[Ch_num][2]);
        // check the max and min input values
        //   AnalogMetaData[Ch_num][7]=IntVals[6]; // Min_value
        //   AnalogMetaData[Ch_num][8]=IntVals[7]; // Max_Value
        //   AnalogMetaData[Ch_num][9]=IntVals[8]; // Range Check Count
      }

      if (((micros() - AnalogTimmingData[Ch_num][1]) > AnalogMetaData[Ch_num][6]) && (responding == 0)) {  //if channel is active and the time since the last sample is greater than hte sample ticks
        int sample_val;
        for (int i = 0; i <= AnalogMetaData[Ch_num][5]; i++) {
          sample_val += AnalogReadings[Ch_num][i];
        }
        setup_reply();
        EncodeIntoReply(-23);                        // Function ID
        EncodeIntoReply(AnalogMetaData[Ch_num][2]);  // OID
        EncodeIntoReply(micros());                   // Clock time
        EncodeIntoReply(sample_val);                 // Analog Read Vales
        finish_reply();
      }
    }
  }
}



// -23:
//__  analog_in_state   __//
// SerialPtLnCom("analog_in_state");
// oid=IntVals[1];
//  erialPtCom("     oid=" + String(oid));
// next_clock=IntVals[2];
// SerialPtCom("     next_clock=" + String(next_clock));
// value=IntVals[3];
// SerialPtCom("     value=" + String(value));
//  SerialPtLnCom("   |");











// the general idea is to poll the analog ports fro all defined analog pins, the rate will be set by the first query connand, and polling will begin on all defined ports
// The data will be storred in an array
/*



8   CheckSumCal:37645   CheckSumComb:37645   Trailer_0:147   Trailer_1:13
analog_in_state
     oid=19     next_clock=65440000     value=7905   |
Completed Parsing Message after 1ms
5 29 69 100 126 
SERIAL 1 0 



SERIAL 1 57 2
40A
18   CheckSumCal:1034   CheckSumComb:1034   Trailer_0:4   Trailer_1:10
config_stepper
     oid=13     step_pin=4     dir_pin=6     invert_step=0     step_pulse_ticks=32   |
Completed Parsing Message after 3ms
config_digital_out
     oid=21     pin=2     value=1     default_value=1     max_duration=0   |
Completed Parsing Message after 4ms
finalize_config
     crc=1626044604   |
Completed Parsing Message after 4ms



queue_digital_out
     oid=14     clockint=40909415     on_ticks=0   |
Completed Parsing Message after 5ms
query_analog_in
     oid=19     clockint=51040000     sample_ticks=16000     sample_count=8     rest_ticks=4800000     min_value=375     max_value=8117     range_check_count=4   |
Completed Parsing Message after 7ms
queue_digital_out
     oid=20     clockint=40920892     on_ticks=0   |
Completed Parsing Message after 7ms
get_config
   |
Completed Parsing Message after 8ms
5 19 172 26 126 
SERIAL 1 0 

SERIAL 1 57 2
40A
18   CheckSumCal:1034   CheckSumComb:1034   Trailer_0:4   Trailer_1:10
config_stepper
  */



//case 31:
//__  query_analog_in   __//
/* SerialPtLnCom("query_analog_in");
   oid=IntVals[1];
   SerialPtCom("     oid=" + String(oid));
   clockint=IntVals[2];
   SerialPtCom("     clockint=" + String(clockint));
   sample_ticks=IntVals[3];
   SerialPtCom("     sample_ticks=" + String(sample_ticks));
   sample_count=IntVals[4];
   SerialPtCom("     sample_count=" + String(sample_count));
   rest_ticks=IntVals[5];
   SerialPtCom("     rest_ticks=" + String(rest_ticks));
   min_value=IntVals[6];
   SerialPtCom("     min_value=" + String(min_value));
   max_value=IntVals[7];
   SerialPtCom("     max_value=" + String(max_value));
   range_check_count=IntVals[8];
   SerialPtCom("     range_check_count=" + String(range_check_count));
   SerialPtLnCom("   |");

   break;

case 32:
   //__  config_analog_in   __//
   SerialPtLnCom("config_analog_in");
   oid=IntVals[1];
   SerialPtCom("     oid=" + String(oid));
   pin=IntVals[2];
   SerialPtCom("     pin=" + String(pin));
   SerialPtLnCom("   |");

   break;
   */
