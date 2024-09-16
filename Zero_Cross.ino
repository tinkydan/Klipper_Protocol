



void sort_vals (){
      for (int i = 0; i < Nchan; i++) {
      PinSethold[i] = GATE[i];  // Reset the pin order so they can be resorted based on duty cycle
    }

  for (int i = 0; i < Nchan; i++) {
    SerialPtDebug(" Pin Presort: " + String(PinSethold[i]));
    BrightSetDs[i]=BrightSetD[i];
  }
  SerialPtDebug(" \n");



    sort(BrightSetDs, PinSethold, Nchan);  // Sorts the Brightness and the pin numbers according to the channel that has the highest duty cycle
    for (int i = 0; i < Nchan; i++) {
      BrightSet[i] = BrightSetDs[i];  // Rewrites as an integer
      PinSet[i]=PinSethold[i];     
    }
    for (int i = 0; i < Nchan; i++) {
         SerialPtLnDebug("  Bright unsorted: "  +  String(BrightSetD[i])  + "Pin Set Sorted: " + String(PinSet[i]) + "  Brightness sort " + String(BrightSetDs[i]));
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
    timerWrite(timer1, 0);
    timerAlarmWrite(timer1, 1800, false);  // S
    timerAlarmEnable(timer1);
   // correction=correction*0.99+float(drift)*.01;
    //if (abs(correction)>100){correction=0;}
    ZX = micros();//-correction;
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
