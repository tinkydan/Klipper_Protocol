



void sort_vals() {
  for (int i = 0; i < Nchan; i++) {
    PinSethold[i] = GATE[i];  // Reset the pin order so they can be resorted based on duty cycle
  }

  for (int i = 0; i < Nchan; i++) {
    BrightSetDs[i] = BrightSetD[i];
  }
  SerialPtDebug(" \n");



  sort(BrightSetDs, PinSethold, Nchan);  // Sorts the Brightness and the pin numbers according to the channel that has the highest duty cycle
  for (int i = 0; i < Nchan; i++) {
    BrightSet[i] = BrightSetDs[i];  // Rewrites as an integer
    if (BrightSet[i] < 50) { BrightSet[i] = 50; }
    if (BrightSet[i] > 8160) { BrightSet[i] = 8160; }
    PinSet[i] = PinSethold[i];
  }


  for (int i = 0; i < Nchan; i++) {
    
    PIN_LAST[i] = 0;
    Bright[i] = BrightSet[i];
    Pin[i] = PinSet[i];
 
  timmer_width_temp[i] = 8160;
  }
  // arrays will be created that tell the interupt functions how long to set the timmer and if mutliple valuse are to be set simtoniouly
  //     int Nchan_on=0; // Number of zero cross shannels that are on (excludes the channels under 50 brightness)
  //     int Nchan_full=0; // number of channels at or above 8160 brightness
  //     int timmer_width[10]; // Number of micros scenond untill the next function trriger is required
  //     bool next_same[10]={0,0,0,0,0,0,0,0,0,0}; // boolian to determin if the next channel is at the same brightness setting
  int Nchan_on_temp = 10;
  int Nchan_full_temp = 0;
  int time_last = 0;
  int i = 0;

  while (i < Nchan) {

    if (Bright[i] >= 8160) {
      Nchan_full_temp++;
    } else if (Bright[i] >= 50) {
      timmer_width_temp[i] = (8160 - Bright[i]) - time_last;
      time_last += timmer_width_temp[i]-8;
     // while ((i + 1) < Nchan) {  // This section itterater over the number of channels that are at the same brighness level
      //  if (Bright[i + 1] == Bright[i]) {
     //     next_same[i] = 1;
      //    SerialPtLnDebug("Pin Set Sorted: " + String(PinSet[i]) + "  Bright " + String(Bright[i])  + "  NextS:" + String(next_same[i]) + " timmer width " + String(timmer_width[i]));
     //     i++;
     //   } 
     //   else {
      //    break;
     //   }
     // }
    } else if (Bright[i] <= 50) {
      Nchan_on_temp = i + 1;
      timmer_width_temp[i] = 1000000;
      break;
    }
    Nchan_on_temp = i + 1;
    SerialPtLnDebug("Pin Set Sorted: " + String(PinSet[i]) + "  Brightness sort " + String(Bright[i])  + "  NextS:" + String(next_same[i]) + " timmer width " + String(timmer_width_temp[i]));
    i++;
  }
  next_same[Nchan-1] = 0;
  timmer_width_temp[Nchan] = 100000;
   Nchan_on = Nchan_on_temp;
   Nchan_full = Nchan_full_temp;
  SerialPtLnDebug(" Nchan:" + String(Nchan)+  " Nchan_on:" + String(Nchan_on) + " Nchan_full:" + String(Nchan_full));


  for (int i = 0; i <= Nchan; i++) {
  timmer_width[i] = timmer_width_temp[i] ;
  }

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
  /*
  for (int i = 0; i < size; i++) {
    SerialPtDebug(" Pin Presort: " + String(PinSet[i]));
  PinSet[i]=pos[i];
  BrightSetDs[i]=a[i];
  SerialPtLnDebug("  Bright unsorted: "  +  String(BrightSetD[i])  + "Pin Set Sorted: " + String(PinSet[i]) + "  Brightness sort " + String(BrightSetDs[i]));
  }
  */
}



void ICACHE_RAM_ATTR ZCISR() {  //zero cross detect

  // input is sorted brightness values and pin assignements
  //memcpy(Bright, BrightSet, Nchan*4);
  //memcpy(Pin, PinSet, Nchan*4);

  ch = micros() - ZX;
  if (ch > 8000) {
    ZXV = ch;
    chac = micros() - ZX;
    //drift=chac-16666;
    // if (abs(drift) > 1000){drift=0;}
    if (Nchan_on > 0) {
      timerWrite(timer1, 0);
      timerAlarmWrite(timer1, 1800, false);  // S
      timerAlarmEnable(timer1);
    } else {
      for (int i = 0; i < 10; i++) {
        digitalWrite(Pin[i], LOW);
      }
    }

    // correction=correction*0.99+float(drift)*.01;
    //if (abs(correction)>100){correction=0;}
    ZX = micros();  //-correction;
    refire_count = 1;
    //for (int i = 0; i < Nchan; i++) {
    //
    //}
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
    if (i<Nchan_full){
      digitalWrite(Pin[i], HIGH);
    }
    else{
      digitalWrite(Pin[i], LOW);
    }
  }
  if (Nchan_full==(Nchan-1)){// All channels are fully on no second interupt is required
    timer1_write_val = 1000000;
  }
  else{
    timer1_write_val=timmer_width[Nchan_full];
  }
  timerWrite(timer, 0);
  timerAlarmWrite(timer, timer1_write_val, false);
  timerAlarmEnable(timer);
  CUR_CHAN = Nchan_full;
}



void ICACHE_RAM_ATTR onTimerISR() {
  //Toggle LED Pin
  tstart=micros();
  TT = micros() - ZX;

  timer1_write_val=timmer_width[CUR_CHAN+1]; //  only want the first if there are more than 1 that are the same
  digitalWrite(Pin[CUR_CHAN], HIGH);
  CUR_CHAN++;
  timerWrite(timer, 0);
  timerAlarmWrite(timer, timer1_write_val, false);
  timerAlarmEnable(timer);
  
  trec=micros()-tstart;

}



/*

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
    if ((Bright[i] < 8160) && (Bright[i] > 50)) {
      digitalWrite(Pin[i], LOW);
      timer1_write_val = 1 * (8160 - Bright[i]);  //12us
    } else if (Bright[i] >= 8160) {
      digitalWrite(Pin[i], HIGH);
      timer1_write_val = 1000000;
    } else if (Bright[i] <= 50) {
      digitalWrite(Pin[i], LOW);
      timer1_write_val = 1000000;
    }

    if ((CUR_CHAN == 0) && (Bright[i] < 8160) && (Bright[i] > 50)) {
      PIN_LAST[i] = Pin[i];
    }
    if ((CUR_CHAN == 0) && (i < (Nchan - 1)) && (Bright[i] != Bright[i + 1]) && (Bright[i] < 8160) && (Bright[i] > 50)) {
      CUR_CHAN = i;// + 1;
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
  tstart=micros();
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
  trec=micros()-tstart;

}
*/
