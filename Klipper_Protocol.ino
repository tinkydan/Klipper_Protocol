#define DEBUG_Command
#define DEBUG_serial
//#define StringDebug

#ifdef DEBUG_serial
#define SerialPtDebug(x)  Serial2.print (x)
#define SerialPtLnDebug(x)  Serial2.println (x)
#define SerialPtehco(x)  Serial2.print(x)
#define SerialPtLnehco(x)  Serial2.println(x)
#else
#define SerialPtDebug(x) //
#define SerialPtLnDebug(x) //
#endif

#define RXD2 16
#define TXD2 17

// Uptime Library
#include <Uptime.h>                                          // Library To Calculate Uptime
Uptime uptime; 


// 3ms is the longest time a 64byte message should take to send over the serial line

int MSG_Timeout = 25;  // miliseconds for the 64byte (max time to read the message)
bool first_Byte = 1;
int bytePOS = 0;
int MessagePOS;
byte SequenceN = 0;
byte Message[61]; byte Trailer[3];
int rpl_j=0;
byte reply[64];
  String Bytesall;
uint16_t CRCV;
int holdi;

int firstInt[117] = {0, 2, 0, 0, 0, 0, 1, 0, 1, 0, 0, 3, 2, 2, 2, 3, 2, 5, 2, 1, 2, 2, 4, 5, 1, 8, 3, 2, 2, 4, 1, 8, 2, 2, 1, 1, 4, 1, 3, 1, 1, 1, 4, 1, 3, 3, 6, 2, 5, 4, 2, 1, 5, 1, 2, 5, 4, 3, 1, 1, 6, 1, 1, 8, 6, 5, 6, 3, 1, 2, 2, 1, 4, 3, 1, 2, 2, 1, 2, 2, 1, 2, 1, 6, 3, 2, 1, 2, 4, 1, 2, 3, 0, 0, 1, 2, 3, 2, 1, 4, 0, 1, 2, 4, 4, 3, 1, 1, 2, 1, 2, 4, 4, 2, 3, 6, 2 };
int numString[117] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 };
int secondInt[117] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

//int MessagePOS;
//byte Message[5];

int64_t IntVals[9];
String StrVals[3];

//#include <FastCRC.h>
//FastCRC16 CRC16;

#ifdef PIN_NEOPIXEL
#define BUILTIN_RGBLED_PIN PIN_NEOPIXEL
#else
#define BUILTIN_RGBLED_PIN 8  // ESP32 has no builtin RGB LED (PIN_NEOPIXEL)
#endif

#define NR_OF_LEDS     8 *4
#define NR_OF_ALL_BITS 24 * NR_OF_LEDS

#include "CRC16.h"
#include "CRC.h"


CRC16 crc_c;

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

int inByte;
bool breakbreak = 0;

volatile bool responding=0;

int VQL_len = 0;
byte Encoded[7];
// pins for the LEDs:

//Klipper protocol decoder
int64_t max_int[8] = { 95, 12287, 1572863, 201326591, 4294967295, 25769803775, 3298534883327, 422212465065983 };

int64_t min_int[7] = { -32, -4096, -524288, -67108864, -2147483648, -17179869184, -2199023255552 };

 int AnalogReadings[37][8];
 int AnalogMetaData[37][10];  // Active // PIn Num // OID  // Index // Sample Ticks // Sample Count // Rest_Ticks //Min_value  // Max_Value //  Range Check Count
 unsigned long AnalogTimmingData[37][2];
 unsigned long SampleTicks;
 unsigned long ReportTicks;
 int analogChannels; // Number of analog channels active  Poll is greater than 0;
 bool analogChannels_active; 

   int64_t offset;
   int64_t count;
   int64_t crc;
   int64_t order;
   int64_t addr;
   int64_t val;
   int64_t pin;
   int64_t value;
   int64_t oid;
 
   //unsigned long
   uint32_t  clockint;
   int64_t on_ticks;
   int64_t cycle_ticks;
   int64_t default_value;
   int64_t max_duration;
   int64_t trsync_oid;
   int64_t dir;
   int64_t interval;
   int64_t add;
   int64_t step_pin;
   int64_t dir_pin;
   int64_t invert_step;
   int64_t step_pulse_ticks;
   int64_t sample_ticks;
   int64_t sample_count;
   int64_t rest_ticks;
   int64_t pin_value;
   int64_t trigger_reason;
   int64_t pull_up;
   int64_t reason;
   int64_t report_clock;
   int64_t report_ticks;
   int64_t expire_reason;
   int64_t min_value;
   int64_t max_value;
   int64_t range_check_count;
   int64_t spi_oid;
   int64_t spi_bus;
   int64_t mode;
   int64_t rate;
   int64_t cs_active_high;
   int64_t read_len;
   int64_t i2c_bus;
   int64_t address;
   int64_t retransmit_count;
   int64_t invert;
   int64_t pos;
   int64_t button_count;
   int64_t readint;
   int64_t rx_pin;
   int64_t tx_pin;
   int64_t bit_time;
   int64_t data_size;
   int64_t bit_max_ticks;
   int64_t reset_min_ticks;
   int64_t poll_ticks;
   int64_t cs_pin;
   int64_t sclk_pin;
   int64_t sid_pin;
   int64_t sync_delay_ticks;
   int64_t cmd_delay_ticks;
   int64_t rs_pin;
   int64_t e_pin;
   int64_t d4_pin;
   int64_t d5_pin;
   int64_t d6_pin;
   int64_t d7_pin;
   int64_t delay_ticks;
   int64_t miso_pin;
   int64_t mosi_pin;
   int64_t scl_pin;
   int64_t sda_pin;
   int64_t max_invalid_count;
   int64_t thermocouple_type;
   int64_t time_shift;
   int64_t spi_angle_type;
   int64_t i2c_oid;
   int64_t threshold;
   int64_t error_reason;
   int64_t intb_pin;
   int64_t gain_channel;
   int64_t dout_pin;
   int64_t data_ready_pin;
   int64_t static_string_id;
   int64_t sum;
   int64_t sumsq;
   int64_t high;
   int64_t is_config;
   int64_t is_shutdown;
   int64_t move_count;
   int64_t homing;
   int64_t next_clock;
   int64_t can_trigger;
   int64_t ack_count;
   int64_t success;
   int64_t count_clock;
   int64_t fault;
   int64_t trigger_clock;
   int64_t query_ticks;
   int64_t next_sequence;
   int64_t buffered;
   int64_t possible_overflows;
   int64_t sequence;

   String data;
   String shutdown_msg;
   String reg;
    String clear_set_bits;
    String writestr;
    String cmds;
    String response;
    String state;
   String readstr;


// PWM function data 
unsigned long pwmdata[16][8];// oid || pin || value || default_value || max_duration || clock || change at tick || Cycle_ticks
unsigned long ZeroCrossdata[10][7];// oid || clock || value || default_value || max_duration ||  change at tick || Cycle_ticks
unsigned long DpinOut[50][8];// oid || pin || value || default_value || max_duration || Change time ||  Flag for software PWM ||  ticks last pwm
int pwmChannelCur;
int DigitalPin;


///___________________________________________________
// zero Cross 
//+++++++++++++++++++++++++++++++++++++++++++++++++++
int Nchan = 0;
int BrightSet[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int PinSet[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int PinSethold[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

int ZN = 0;
int divS[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
double RES[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
double Input[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
double Output[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
double Bright[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

double BrightSetD[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
double BrightSetDs[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };




  // Writes the current settings
volatile float correction=0;
signed long long drift=0;
signed long long ch;
signed long long chac;

volatile int Pin[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

volatile int PIN_LAST[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
volatile int GATE[] ={ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
volatile int GATE_MAP[] = { 23, 16, 17, 18, 19, 4, 13, 12, 27, 5 };
//int THERM[] = {36, 39, 34, 35, 32, 33, 25, 26, 14, 15};
volatile int CUR_CHAN = 0;

        // arrays will be created that tell the interupt functions how long to set the timmer and if mutliple valuse are to be set simtoniouly
volatile int Nchan_on=0; // Number of zero cross shannels that are on (excludes the channels under 50 brightness)
volatile int Nchan_full=0; // number of channels at or above 8160 brightness
volatile int timmer_width[11]; // Number of micros scenond untill the next function trriger is required
volatile int timmer_width_temp[11]; // Number of micros scenond untill the next function trriger is required
volatile bool next_same[10]={0,0,0,0,0,0,0,0,0,0}; // boolian to determin if the next channel is at the same brightness setting

volatile unsigned long TT=0;

volatile unsigned long ZX=0;
volatile unsigned long ZXV=0;
volatile int TC=0;
int brightnessach = 85;
volatile int brightness = 5000;
volatile int refire_count = 0;
int timer1_write_val;
float brightnessF = 5000;
int lst_t_set;
unsigned long trec;
unsigned long tstart;

///___________________________________________________
//+++++++++++++++++++++++++++++++++++++++++++++++++++
   unsigned long Time_NPT_ms3 = 1000; // NPT read /every 100mins
unsigned long Time_NPT_LAST3 = 0;
   unsigned long Time_NPT_ms2 = 2000; // NPT read /every 100mins
unsigned long Time_NPT_LAST2 = 0;
   unsigned long Time_NPT_ms1 = 3000; // NPT read /every 100mins
unsigned long Time_NPT_LAST1 = 0;
   unsigned long Time_NPT_ms = 4000; // NPT read /every 100mins
unsigned long Time_NPT_LAST = 0;
unsigned long M_off=0;
long fm;
/*int bytv
 * There are three serial ports on the ESP known as U0UXD, U1UXD and U2UXD.
 * 
 * U0UXD is used to communicate with the ESP32 for programming and during reset/boot.
 * U1UXD is unused and can be used for your projects. Some boards use this port for SPI Flash access though
 * U2UXD is unused and can be used for your projects.
 * 
*/
int64_t Serial_MSG;
unsigned long ST=0;
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

hw_timer_t* timer1 = NULL;
portMUX_TYPE timerMux1 = portMUX_INITIALIZER_UNLOCKED;

int b1,b2,b3;

//HardwareSerial Serial1(1);
//HardwareSerial Serial2(1);
//#define RXD1 7
//#define TXD1 6
//#define RXD2 5
//#define TXD2 4

// below script redefines the bitRead and bitWrite functions to be compatible with int64_t valuse so that a uint64_t value cane be properly encoded
TaskHandle_t AnalogReadTask;


#undef bitRead
#undef bitWrite

template<typename T> void bitWrite(T& value, byte bit, byte val);  // prototype
template<typename T> void bitWrite(T& value, byte bit, byte val) {
  if (val)
    value |= (T(1) << bit);
  else
    value &= ~(T(1) << bit);
}

template<typename T> bool bitRead(T value, byte bit);  // prototype
template<typename T> bool bitRead(T value, byte bit) {
  return (value & ((T)1 << bit)) != 0;
}

rmt_data_t led_data[NR_OF_ALL_BITS];

uint32_t Offsey_micros(void ){
  return micros()+M_off;
}

void setup() {
  // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);


     Serial2.begin(500000, SERIAL_8N1, RXD2, TXD2);
    Serial2.println("Started");
  Serial.begin(115200); 
  Serial.setTimeout(25);
first_Byte=1;
for (int i=0;i<10;i++){
  AnalogMetaData[i][2]=-1; /// since OIOD can be zero need to set to negative 1
}
  //  Serial1.begin(250000, SERIAL_8N1, RXD1, TXD1);
  //  Serial2.begin(250000, SERIAL_8N1, RXD2, TXD2);
  //@////p//SerialPtLnDebug("Begun");

 
  //@////p//SerialPtLnDebug("loop");
  //@////p//SerialPtDebug("setup() running on core ");
  //@////p//SerialPtLnDebug(xPortGetCoreID());

  xTaskCreatePinnedToCore(
      AnalogReadTaskcode, // Function to implement the task //
      "AnalogReadTask", // Name of the task //
      100000,  // Stack size in words //
      NULL,  // Task input parameter //
      0,  // Priority of the task //
      &AnalogReadTask,  // Task handle. //
      0); // Core where the task should run //


  //@////p//SerialPtLnDebug("task pinned to core 0");
    ST=millis();
delay(10);

    attachInterrupt(21, ZCISR, FALLING);
     //@////p//SerialPtLnDebug("attaching timmers");
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &onTimerISR, false);
    //timerAlarmWrite(timer, 1000000, false);
    //timerAlarmEnable(timer);
 //@////p//SerialPtLnDebug("timmer started");
    timer1 = timerBegin(1, 80, true);
    timerAttachInterrupt(timer1, &ZXA, false);
   // timerAlarmWrite(timer1, 1000000, false);
    //timerAlarmEnable(timer);




}
unsigned long loop_last, loop_time;
float rolling_average=0;


void loop() {  //Choose Serial1 or Serial2 as required
//Serial.println("loop");
#ifdef DEBUG_serial
  // protocols for debugging
  loop_last=Offsey_micros()-loop_time;
  loop_time=Offsey_micros();
  rolling_average=rolling_average*99/100+float(loop_last)*1/100;
#endif

  Serial_Parse(); //~ 6uS


//queloop

for (int pwm_c = 0; pwm_c < pwmChannelCur; pwm_c++) {
  if (Offsey_micros() > pwmdata[pwm_c][6]) {
    ledcWrite(pwm_c, pwmdata[pwm_c][2]);               // set the PWM of the channel
    pwmdata[pwm_c][2] = pwmdata[pwm_c][3];             // Set value to the default value
    pwmdata[pwm_c][6] = Offsey_micros() + pwmdata[pwm_c][4];  // sent the change time to the current time plus the max time
  }
}
for (int zc_c = 0; zc_c < Nchan; zc_c++) {
  if (Offsey_micros() > ZeroCrossdata[zc_c][5]) {
    BrightSetD[zc_c] = double(ZeroCrossdata[zc_c][2])*double(8160)/double(256);
    ZeroCrossdata[zc_c][2] = ZeroCrossdata[zc_c][3];
    ZeroCrossdata[zc_c][5] = Offsey_micros() + ZeroCrossdata[zc_c][4];
   
    //p//SerialPtLnDebug("Ch Num: " + String(zc_c) + " OID: " + String(ZeroCrossdata[zc_c][0]) + " Brightness: " +String(BrightSetD[zc_c]) + "  Next Val: " + String(ZeroCrossdata[zc_c][2]) + "  next time: " + String(ZeroCrossdata[zc_c][5] ));
 sort_vals();


  }
}


/*
DpinOut
// oid || pin || value || default_value || max_duration || Change time ||  Flag for software PWM ||  ticks last pwm || Update Time
for (int dig_c=0;dig_c<DigitalPin;dig_c++){
  if (Offsey_micros()>pwmdata[pwm_c][5]){
      if (pwmdata[pwm_c][5]==1){// Software PWM
        if (Offsey_micros()>pwmdata[pwm_c][8])

          value=default_value;




      }



    ledcWrite(pwm_c,pwmdata[pwm_c][2]); // set the PWM of the channel
    pwmdata[dig_c][2]=pwmdata[pwm_c][3];// Set value to the default value
    pwmdata[pwm_c][6]=Offsey_micros()+pwmdata[pwm_c][4]; // sent the change time to the current time plus the max time
  }
}
*/

 if ((millis() - Time_NPT_LAST1 >= Time_NPT_ms1) ){
Time_NPT_LAST1=millis();

     uptime.calculateUptime();    
     Time_NPT_LAST=millis();
     //@////p//SerialPtLnDebug(" Loop Timming last: " + String(loop_last) + "us  Average: " + String(rolling_average)  + "us  Uptime: " + String(uptime.getTotalSeconds()) + "sec" + "timmer recal " + String(trec));
     // for (int i = 0; i < Nchan; i++) {
     //@////p//SerialPtLnDebug("Zero Cross  peak 2peal " +String(chac)+ " Drift " + String(drift) + " Correct: " + String(correction)+" pin: " +String(Pin[i]) + "  Bright: " + String(Bright[i]) + "  BrightSet: " + String(BrightSet[i]) + "  BrightSetD: " + String(BrightSetD[i]) + "  BrightSetDs: " + String(BrightSetDs[i]) );
     //}
  }
}
