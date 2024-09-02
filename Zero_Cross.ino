hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

hw_timer_t* timer1 = NULL;
portMUX_TYPE timerMux1 = portMUX_INITIALIZER_UNLOCKED;





int Nchan = 10;
int ZN = 0;
int divS[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
double RES[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
double Input[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
double Output[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
double Bright[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
double BrightSetD[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
;  // Writes the current settings
int BrightSet[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int Pin[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int PinSet[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int PIN_LAST[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int GATE[] = { 23, 16, 17, 18, 19, 4, 13, 12, 27, 5 };
//int THERM[] = {36, 39, 34, 35, 32, 33, 25, 26, 14, 15};
int CUR_CHAN = 0;

volatile unsigned long TT=0;
unsigned long ST=0;
volatile unsigned long ZX=0;
volatile unsigned long ZXV=0;
volatile int TC=0;
int brightnessach = 85;
volatile int brightness = 5000;
volatile int refire_count = 0;
int timer1_write_val;
float brightnessF = 5000;
int lst_t_set;


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



void ICACHE_RAM_ATTR ZCISR() {  //zero cross detect

  // input is sorted brightness values and pin assignements
  //memcpy(Bright, BrightSet, Nchan*4);
  //memcpy(Pin, PinSet, Nchan*4);

  unsigned long ch = micros() - ZX;
  if (ch > 1500) {
    ZXV = ch;
    timerWrite(timer1, 0);
    timerAlarmWrite(timer1, 4167, false);  // S
    timerAlarmEnable(timer1);
    ZX = micros();
    refire_count = 1;
  }
}





void ICACHE_RAM_ATTR ZXA() {
  CUR_CHAN = 0;


  if (refire_count > 0) {
    timerWrite(timer1, 0);
    timerAlarmWrite(timer1, 8333, false);  //
    timerAlarmEnable(timer1);
  }
  refire_count--;

  for (int i = 0; i < Nchan; i++) {
    PIN_LAST[i] = 0;
    Bright[i] = BrightSet[i];
    Pin[i] = PinSet[i];
  }

  for (int i = 0; i < Nchan; i++) {
    if ((Bright[i] != 8160) && (Bright[i] > 50)) {
      digitalWrite(Pin[i], LOW);

      timer1_write_val = 1 * (8160 - Bright[i]);  //12us
    } else if (Bright[i] == 8160) {
      digitalWrite(Pin[i], HIGH);
      timer1_write_val = 1000000;
    } else if (Bright[i] <= 50) {
      digitalWrite(Pin[i], LOW);
      timer1_write_val = 1000000;
    }

    if ((CUR_CHAN == 0) && (Bright[i] != 8160) && (Bright[i] > 50)) {
      PIN_LAST[i] = Pin[i];
    }
    if ((CUR_CHAN == 0) && (i < (Nchan - 1)) && (Bright[i] != Bright[i + 1]) && (Bright[i] != 8160) && (Bright[i] > 50)) {
      CUR_CHAN = i + 1;
      timerWrite(timer, 0);
      timerAlarmWrite(timer, timer1_write_val, false);
      timerAlarmEnable(timer);
      lst_t_set = timer1_write_val;
    } else if ((CUR_CHAN == 0) && (i == (Nchan - 1))) {
      CUR_CHAN = i;
      timerWrite(timer, 0);
      timerAlarmWrite(timer, timer1_write_val, false);  // Should only happen if all are off or on
      timerAlarmEnable(timer);
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
    timerAlarmWrite(timer, 1000000, false);
    timerAlarmEnable(timer);
  }
  for (int i = CUR_CHAN + 1; i < Nchan; i++) {
    if ((Bright[i] != 8160) && (Bright[i] != 50)) {
      timer1_write_val = (1 * (8160 - Bright[i]));  //12us
                                                    // timer1_write_val = (1 * (8160 - Bright[i]) - lst_t_set); //12us
    } else if (Bright[i] == 50) {
      timer1_write_val = 1000000;
    } else if (Bright[i] == 8160) {  //This case should never happen as it should be already cought
      timer1_write_val = 1000000;
    }
    if ((Bright[i] != 8160) && (Bright[i] > 50)) {
      PIN_LAST[i] = Pin[i];
    }
    if ((i < (Nchan)) && (Bright[i] != Bright[i + 1])) {
      lst_t_set = 1 * (8160 - (Bright[i]));
      CUR_CHAN = i;
      timerAlarmWrite(timer, timer1_write_val, false);
      timerAlarmEnable(timer);
      break;
    }
  }
}
