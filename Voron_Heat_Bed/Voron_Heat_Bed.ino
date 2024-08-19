/***************************************************
  Adafruit MQTT Library ESP8266 Example

  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino

  Works great with Adafruit's Huzzah ESP board & Feather
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/products/2821

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <Ticker.h>




int Vo;
float R1 = 4700;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
// fit coefficients
float a = 283786.2;
float b = 0.06593;
float c = 49886.0;


volatile unsigned long TT = 0;
unsigned long ST = 0;
volatile unsigned long ZX = 0;
volatile unsigned long ZXV = 0;
volatile double PWM1 = 0;
volatile unsigned long PWM1_R = 0;
volatile double PWM2 = 0;
volatile unsigned long PWM2_R = 0;
volatile unsigned long PWM1_P = 1;
volatile unsigned long PWM2_P = 1;
volatile unsigned long PWM1_H = 0;
volatile unsigned long PWM1_H2 = 0;
volatile unsigned long PWM2_H2 = 0;

volatile unsigned long PWM1_L = 0;
volatile unsigned long PWM2_L = 0;
volatile int ZCCr = 0;
volatile unsigned long PWM2_H = 0;
volatile bool ZeroCross = 0;
volatile int TC = 0;
uint8_t  MAC_softAP[]          = {0, 0, 0, 0, 0, 0};                 //not sure why we have to pass a MAC address to get a MAC address.
uint8_t  MAC_STA[]                = {0, 0, 0, 0, 0, 0};

const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data

int timer1_write_val;
const int numReadings = 1500;
float readings_SP[numReadings];      // the readings from the analog input
float readings_BRIGHT[numReadings];







boolean newData = false;

unsigned long CNTR_ms = 100;
unsigned long CNTR1_LAST = 0;
unsigned long currentMillis = 0;
unsigned long EEPROM_Upload_ms = 2000; //Min time between EEPROM Updates
unsigned long EEPROM_Upload_LAST = 0;
unsigned long Display_ms = 2000; //Min time between EEPROM Updates
unsigned long Display_LAST = 0;

//PID constants

#define TIMEOUT 5000000 // (microseconds)  Timeout for the PWM not measured, can happen if set to high or low on the channel 


double kp = 100;//.925
double ki = 0.02;//0.0002
double kd = .5;
double SET_TEMP = 70;
float average;
#define NUMSAMPLES 100
#define PWM1Pin 15 //to be 15
#define PWM2Pin 13 //to be 13
#define Relay 16 //to be 13
int samples[NUMSAMPLES];
int LP = 0;
int LPS = 0;

double amb = 0;


double gap = 0;
double gap_set = 5;

unsigned long currentTime, previousTime;
double elapsedTime;
double error;
double lastError;

int lst_t_set;
char* ssid = "TheWhitneys";
char* password = "icantremember";
char* ssidAP = "HeatBed";

unsigned long time_now = 0;
int period = 50000;


String HTML = "";
String HTML2 = "";

int Nchan = 2;
int ZN = 0;
int divS[] = {0, 0};
double  RES[] = {0, 0};
double Input[]  = {0, 0};
double Output[]  = {0, 0};
double Bright[]  = {0, 0};
double BrightSetD[]  = {0, 0};    ; // Writes the current settings
int BrightSet[]  = {0, 0};
int Pin[]  = {0, 0};
int PinSet[]  = {0, 0};
int PIN_LAST[]  = {0, 0};
int GATE[] = {2, 12};

void PWM1_Ff();
void PWM2_Ff();
void PWM1_Rf();
void PWM2_Rf();



int CUR_CHAN = 0;
bool WIFION = 0;
double RESi[] = {1733200, 1630408, 1534477, 1444903, 1361220, 1283000, 1209327, 1140424, 1075949, 1015588, 959050, 906011.7, 856288.3, 809650.6, 765886.5, 724800, 685650.7, 648892.9, 614364.9, 581916.9, 551410, 522690.8, 495667.4, 470228.6, 446271.4, 423700, 402056, 381665.8, 362448.8, 344330.1, 327240, 311039.7, 295750.6, 281315.7, 267682, 254800, 242582.7, 231032.1, 220108, 209772.4, 199990, 190557.8, 181631.9, 173182.2, 165180.4, 157600, 150425.3, 143623.4, 137172.6, 131052.8, 125245, 119658.2, 114355.9, 109322.1, 104541.5, 100000, 95819.1, 91839.2, 88049.4, 84439.5, 81000, 77623.8, 74409.1, 71347.2, 68430.1, 65650, 62983.8, 60442, 58018.1, 55706, 53500, 51370.8, 49339.1, 47399.8, 45548.3, 43780, 42055.5, 40409.2, 38836.9, 37335, 35899.9, 34616, 33385.5, 32205.9, 31074.8, 29990, 28905.3, 27866, 26870, 25915.3, 25000, 24109.9, 23256.5, 22438.1, 21653.1, 20900, 20174.1, 19477.4, 18808.7, 18166.6, 17550, 16945.9, 16365.9, 15808.9, 15273.9, 14760, 14281.3, 13820.6, 13377.4, 12950.7, 12540, 12134.7, 11744.7, 11369.4, 11008, 10660, 10324.3, 10001, 9689.5, 9389.3, 9100, 8817.1, 8544.4, 8281.6, 8028.3, 7784, 7553.8, 7331.6, 7117.2, 6910, 6710, 6526.5, 6349, 6177.2, 6010.9, 5850, 5683.2, 5522.1, 5366.3, 5215.6, 5070, 4929.1, 4792.8, 4661, 4533.4, 4410, 4290.6, 4175.1, 4063.2, 3954.9, 3850, 3741, 3635.7, 3533.8, 3435.3, 3340, 3255, 3172.6, 3092.7, 3015.2, 2940, 2863.4, 2789.3, 2717.3, 2647.6, 2580, 2514.4, 2450.7, 2389, 2329.1, 2271, 2213.5, 2157.7, 2103.5, 2051, 2000, 1951.3, 1904, 1858, 1813.4, 1770, 1731.9, 1694.7, 1658.6, 1623.3, 1589, 1552, 1516, 1481.1, 1447.1, 1414, 1381.2, 1349.4, 1318.4, 1288.3, 1259, 1230.1, 1201.9, 1174.5, 1147.9, 1122, 1095.6, 1069.9, 1044.9, 1020.6, 997, 975.7, 955, 934.8, 915.1, 896, 875, 854.7, 834.9, 815.7, 797, 780.6, 764.6, 749, 733.8, 719, 702.9, 687.3, 672.1, 657.4, 643, 630.2, 617.7, 605.5, 593.6, 582, 571.7, 561.7, 551.9, 542.3, 533, 522.5, 512.2, 502.2, 492.5};




/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.


// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).

int brightnessach = 85;
volatile int brightness = 5000;

float brightnessF = 5000;
void ICACHE_RAM_ATTR PWM1_Rf() { //PWM /rising edge

  PWM1_H=micros();
  PWM1_P = PWM1_H-PWM1_R;
  PWM1_R = PWM1_H;
   attachInterrupt(PWM1Pin, PWM1_Ff, FALLING);
}

void ICACHE_RAM_ATTR PWM1_Ff() { //PWM Falling edge
  PWM1_H2=(micros() - PWM1_R);
  
  if (PWM1_P>100){
  PWM1 = double((micros() - PWM1_R) / double(PWM1_P));
  }
  attachInterrupt(PWM1Pin, PWM1_Rf, RISING);
  
}
void ICACHE_RAM_ATTR PWM2_Ff() { //PWM Falling edge
  PWM2_H2=(micros() - PWM2_R);
  if (PWM2_P>100){
  PWM2 = double((micros() - PWM2_R) / double(PWM2_P));}//PWM2_P
   attachInterrupt(PWM2Pin, PWM2_Rf, RISING);
}

void ICACHE_RAM_ATTR PWM2_Rf() { //PWM /rising edge

  PWM2_H=micros();
  PWM2_P = PWM2_H - PWM2_R;
  PWM2_R = PWM2_H;
   attachInterrupt(PWM2Pin, PWM2_Ff, FALLING);
}


void sort(double a[], int pos[], int size) {
  for (int i = 0; i < (size - 1); i++) {
    for (int o = 0; o < (size - (i + 1)); o++) {
      if (a[o] < a[o + 1]) {
        double t = a[o];
        int tp = pos[o];
        a[o] = a[o + 1];
        pos[o] = pos[o + 1];
        a[o + 1] = t;
        pos[o + 1] = tp;
      }
    }
  }
}



/*
void ICACHE_RAM_ATTR PWM1_CHG(){
  PWM1_L=micros()-PWM1_L;
  if(PWM1_L>90){
    
  
  if (digitalRead(PWM1Pin)){
    delayMicroseconds(30);
    PWM1_Rf();
  }
  else{
    delayMicroseconds(30);
    PWM1_Ff();
  }}
  PWM1_L=micros();
}

void ICACHE_RAM_ATTR PWM2_CHG(){
    PWM2_L=micros()-PWM2_L;
  if(PWM2_L>25){
  if (digitalRead(PWM2Pin)){
    PWM2_Rf();
  }
  else{
    PWM2_Ff();
  }}
   PWM2_L=micros();
}

*/

void ICACHE_RAM_ATTR ZXA() {
  CUR_CHAN = 0;
  for (int i = 0; i < Nchan; i++) {
    PIN_LAST[i] = 0;
    Bright[i] = BrightSet[i];
    Pin[i] = PinSet[i];
  }

  for (int i = 0; i < Nchan; i++) {
    if ((Bright[i] != 8160) && (Bright[i] > 50)) {
      digitalWrite(Pin[i], LOW);

      timer1_write_val = 80 * (8160 - Bright[i]); //12us
    }
    else if (Bright[i] == 8160) {
      digitalWrite(Pin[i], HIGH);
      timer1_write_val = 1000000;
    }
    else if (Bright[i] <= 50) {
      digitalWrite(Pin[i], LOW);
      timer1_write_val = 1000000;
    }

    if ((CUR_CHAN == 0) && (Bright[i] != 8160) && (Bright[i] > 50)) {
      PIN_LAST[i] = Pin[i];
    }
    if ((CUR_CHAN == 0) && (i < (Nchan - 1)) && (Bright[i] != Bright[i + 1]) && (Bright[i] != 8160) && (Bright[i] > 50)) {
      CUR_CHAN = i + 1;
      //     timerWrite(timer,0);
      //     timerAlarmWrite(timer, timer1_write_val, false);
      //      timerAlarmEnable(timer);

      timer1_write(timer1_write_val);
      lst_t_set = timer1_write_val;
    }
    else if ((CUR_CHAN == 0) && (i == (Nchan - 1))) {
      CUR_CHAN = i;
      //timerWrite(timer,0);
      //timerAlarmWrite(timer, timer1_write_val, false); // Should only happen if all are off or on
      //timerAlarmEnable(timer);
      timer1_write(timer1_write_val);
      lst_t_set = timer1_write_val;
    }
  }


}


void ICACHE_RAM_ATTR onTimerISR() {
  //Toggle LED Pin

  TT = micros() - ZX;
  TC++;
  for (int i = 0; i < Nchan; i++) {
    if (PIN_LAST[i] > 0) {
      digitalWrite(PIN_LAST[i], HIGH);
    }
    PIN_LAST[i] = 0;
  }

  if (CUR_CHAN == (Nchan - 1)) {
    //timerAlarmWrite(timer, 1000000, false);
    //timerAlarmEnable(timer);
    timer1_write(8000000);
  }
  for (int i = CUR_CHAN + 1; i < Nchan; i++) {
    if ((Bright[i] != 8160) && (Bright[i] != 50)) {
      timer1_write_val = (80 * (8160 - Bright[i]) ); //12us
      // timer1_write_val = (1 * (8160 - Bright[i]) - lst_t_set); //12us
    }
    else if (Bright[i] == 50) {
      timer1_write_val = 1000000;
    }
    else if (Bright[i] == 8160) { //This case should never happen as it should be already cought
      timer1_write_val = 1000000;
    }
    if ((Bright[i] != 8160) && (Bright[i] > 50)) {
      PIN_LAST[i] = Pin[i];
    }
    if ((i < (Nchan)) && (Bright[i] != Bright[i + 1])) {
      lst_t_set = 80 * (8160 - (Bright[i]));
      CUR_CHAN = i;
      timer1_write(timer1_write_val);
      //      timerAlarmWrite(timer, timer1_write_val, false);
      //      timerAlarmEnable(timer);
      break;
    }
  }
}


void ICACHE_RAM_ATTR TIMERC() {
  if (ZeroCross) {
    ZXA();
  }
  else {
    onTimerISR();
  }
  ZeroCross = 0;
}

void ICACHE_RAM_ATTR ZCISR() { //zero cross detect

  // input is sorted brightness values and pin assignements
  //memcpy(Bright, BrightSet, Nchan*4);
  //memcpy(Pin, PinSet, Nchan*4);

  unsigned long ch = micros() - ZX;

 //if (ch > 1500) {
    ZCCr=ZCCr+1;
    // Serial.print(" |ZeroXXX| ");
    // Serial.print(ch);
    ZXV = ch;
    delayMicroseconds(300);
    TIMERC();
    ZeroCross = 1;
    ZX = micros();
//}
}

void setup() {




pinMode(Relay, OUTPUT);
digitalWrite(Relay, LOW);
  pinMode(PWM1Pin, INPUT);//pwm1 15 in update
  pinMode(PWM2Pin, INPUT);//pwm2 13 in update
  pinMode(14, INPUT);     //zero cross detect

  for (int i = 0; i < Nchan; i++) {
    pinMode(GATE[i], OUTPUT);
    digitalWrite(GATE[i], HIGH);
  }

  Serial.begin(74880);
  delay(10);





  //Initialize Ticker every 0.5s


  ST = millis();
  attachInterrupt(14, ZCISR, FALLING);
  //attachInterrupt(PWM1Pin, PWM1_CHG, CHANGE);
  //attachInterrupt(PWM2Pin, PWM2_CHG, CHANGE);
  attachInterrupt(PWM1Pin, PWM1_Rf, RISING);
  attachInterrupt(PWM2Pin, PWM2_Rf, RISING);
  //attachInterrupt(PWM1Pin, PWM1_Rf, RISING);
 // attachInterrupt(PWM2Pin, PWM2_F, FALLING);
  //attachInterrupt(PWM2Pin, PWM2_Rf, RISING);
  // timer = timerBegin(0, 80, true);
  // timerAttachInterrupt(timer, &onTimerISR, false);
  // timerAlarmWrite(timer, 1000000, false);
  //timerAlarmEnable(timer);
  timer1_attachInterrupt(onTimerISR);
  timer1_enable(TIM_DIV1, TIM_EDGE, TIM_SINGLE);
  timer1_write(8000000);

  // Must roll into timer 0]
  /*
      timer1 = timerBegin(1, 80, true);
    timerAttachInterrupt(timer1, &ZXA, false);
    timerAlarmWrite(timer1, 1000000, false);
    timerAlarmEnable(timer); */
}



void loop() {

  currentMillis = millis();
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.



  if (currentMillis - CNTR1_LAST >= CNTR_ms) {
    CNTR1_LAST = millis();



    if ((PWM1_P != 1) || ((micros() - PWM1_R) > TIMEOUT)) {
      if ((micros() - PWM1_R) > TIMEOUT) {
        PWM1 = digitalRead(PWM1Pin);
      }
      BrightSetD[0] = PWM1 * 8160;
    }
    if ((PWM2_P != 1) || ((micros() - PWM2_R) > TIMEOUT)) {
      if ((micros() - PWM2_R) > TIMEOUT) {
        PWM2 = digitalRead(PWM2Pin);
      }
      BrightSetD[1] = PWM2 * 8160;
    }
  if ((PWM1>0)||(PWM2>0)){
    digitalWrite(Relay, HIGH);
  }
  else{
    digitalWrite(Relay, LOW);
  }

      Serial.print("PWM1_P: ");
      Serial.print(PWM1_P);
      Serial.print(" | PWM2_P: ");
      Serial.print(PWM2_P);
      Serial.print(" | PWM1_R: ");
      Serial.print(PWM1_R);
      Serial.print(" | PWM2_R: ");
      Serial.print(PWM2_R);
      Serial.print(" | PWM1_H2: ");
                  
      Serial.print((PWM1_H2));
      Serial.print(" | PWM2_H2: ");
      Serial.print((PWM2_H2));
      Serial.print(" | PWM1: ");
      Serial.print(PWM1);
      Serial.print(" | PWM2: ");
      Serial.print(PWM2);
            Serial.print(" | ZC: ");
      Serial.println(ZCCr);
    
  for (int i = 0; i < Nchan; i++){
    PinSet[i]=GATE[i];// Reset the pin order so they can be resorted based on duty cycle
    }
    
  sort(BrightSetD, PinSet, Nchan);// Sorts the Brightness and the pin numbers according to the channel that has the highest duty cycle
  for (int i = 0; i < Nchan; i++){
    BrightSet[i]=BrightSetD[i];// Rewrites as an integer
}
  }
}
