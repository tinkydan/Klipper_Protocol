


#ifdef DEBUG_Command
#define SerialPtCom(x) Serial2.print(x)
#define SerialPtLnCom(x) Serial2.println(x)
#else
#define SerialPtCom(x)
#define SerialPtLnCom(x)
#endif

void Run(int Command) {
  int Ch_num;
  int ZCC;
  int indc = 0;
  int ZeroCrossOID = -1;
  while ((responding == 1) && (indc < 2000)) {
    delayMicroseconds(1);
    indc++;
  }
  switch (Command) {
    case 1:
      //__  identify   __//
      //p//SerialPtLnCom("identify");
      offset = IntVals[1];
      //p////p//SerialPtCom("     offset=" + String(offset));
      count = IntVals[2];
      //p////p//SerialPtCom("     count=" + String(count));
      //p//SerialPtLnCom("   |");
      fm = millis();
      // while((millis()-fm)<2000){  }

      setup_reply();

      reply[2] = 0;

      EncodeVLQ(offset);
      for (int i = 0; i < VQL_len; i++) {
        rpl_j++;
        reply[rpl_j] = Encoded[i];
      }
      rpl_j++;
      reply[rpl_j] = min(count, ident_leng - offset);
      holdi = reply[rpl_j];
      rpl_j++;

      for (int i = offset; i < (offset + holdi); i++) {
        if (i <= ident_leng) {
          reply[rpl_j] = ident[i];
          rpl_j++;
        }
      }
      finish_reply();

      break;

    case 2:
      //__  clear_shutdown   __//
      //p//SerialPtLnCom("clear_shutdown");
      //p//SerialPtLnCom("   |");

      break;

    case 3:
      //__  emergency_stop   __//
      //p//SerialPtLnCom("emergency_stop");
      //p//SerialPtLnCom("   |");
      ESP.restart();

      break;

    case 4:
      //__  get_uptime   __//
      //p//SerialPtLnCom("get_uptime");
      //p//SerialPtLnCom("   |");

      setup_reply();
      EncodeIntoReply(-31);  // Function ID
      int upt;
      upt = uptime.getTotalSeconds();
      //p//SerialPtLnCom("Current Uptime " + String(upt));
      EncodeIntoReply(upt);       // Uptime time (seconds since restart)
      EncodeIntoReply(Offsey_micros());  // Clock time
      finish_reply();

      break;

    case 5:
      //__  get_clockint   __//
      EncodeVLQ(Offsey_micros());
      //p//SerialPtLnCom("get_clockint");
      //p//SerialPtLnCom("  |  micros " + String(Offsey_micros())+ "  Up and Down decoded " +String(VLQ(Encoded, VQL_len) ));



      setup_reply();
      EncodeIntoReply(-30);       // Function ID
      EncodeIntoReply(Offsey_micros());  // Clock time
      finish_reply();

      break;

    case 6:
      //__  finalize_config   __//
      //p//SerialPtLnCom("finalize_config");
      crc = IntVals[1];
      //p////p//SerialPtCom("     crc=" + String(crc));
      //p//SerialPtLnCom("   |");
      is_config = 1;


    //  is_shutdown static_string_id=%hu":94   send 5
      //setup_reply();
     // EncodeIntoReply(94);          // Function ID aka 99
     // EncodeIntoReply(5);          // is crc of the configuration
     // finish_reply();     // move count!   move_count

      break;

    case 7:
      //__  get_config   __//
      //p//SerialPtLnCom("get_config");
      //p//SerialPtLnCom("   |");

      setup_reply();
      EncodeIntoReply(-29);          // Function ID aka 99
      EncodeIntoReply(is_config);    // is configurred
      EncodeIntoReply(crc);          // is crc of the configuration
      EncodeIntoReply(is_shutdown);  // is shutdown
      EncodeIntoReply(1024);         // move count!   move_count
      finish_reply();


      break;

    case 8:
      //__  allocate_oids   __//
      //p//SerialPtLnCom("allocate_oids");
      count = IntVals[1];
      //p////p//SerialPtCom("     count=" + String(count));
      //p//SerialPtLnCom("   |");

      break;

    case 9:
      //__  debug_nop   __//
      //p//SerialPtLnCom("debug_nop");
      //p//SerialPtLnCom("   |");

      break;

    case 10:
      //__  debug_ping   __//
      //p//SerialPtLnCom("debug_ping");
      data = StrVals[1];
      //p////p//SerialPtCom("     data=" + data);
      //p//SerialPtLnCom("   |");

      break;

    case 11:
      //__  debug_write   __//
      //p//SerialPtLnCom("debug_write");
      order = IntVals[1];
      //p////p//SerialPtCom("     order=" + String(order));
      addr = IntVals[2];
      //p////p//SerialPtCom("     addr=" + String(addr));
      val = IntVals[3];
      //p////p//SerialPtCom("     val=" + String(val));
      //p//SerialPtLnCom("   |");

      break;

    case 12:
      //__  debug_read   __//
      //p//SerialPtLnCom("debug_read");
      order = IntVals[1];
      //p////p//SerialPtCom("     order=" + String(order));
      addr = IntVals[2];
      //p////p//SerialPtCom("     addr=" + String(addr));
      //p//SerialPtLnCom("   |");

      break;

    case 13:
      //__  set_digital_out   __//
      //p//SerialPtLnCom("set_digital_out");
      pin = IntVals[1];
      //p////p//SerialPtCom("     pin=" + String(pin));
      value = IntVals[2];
      //p////p//SerialPtCom("     value=" + String(value));
      //p//SerialPtLnCom("   |");
      pinMode(pin, OUTPUT);
      digitalWrite(pin, value);


      break;

    case 14:
      //__  update_digital_out   __//
      //p//SerialPtLnCom("update_digital_out");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      value = IntVals[2];
      //p////p//SerialPtCom("     value=" + String(value));
      //p//SerialPtLnCom("   |");

      for (int i = 0; i < DigitalPin; i++) {
        if (oid == DpinOut[i][0]) {
          Ch_num = i;
          break;
        }
      }
      DpinOut[Ch_num][5] = Offsey_micros();  // Change time
      DpinOut[Ch_num][2] = value;

      break;

    case 15:
      //__  queue_digital_out   __//
      //p//SerialPtLnCom("queue_digital_out");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      clockint = IntVals[2];
      //p////p//SerialPtCom("     clockint=" + String(clockint));
      on_ticks = IntVals[3];
      //p////p//SerialPtCom("     on_ticks=" + String(on_ticks));  //  ticks for software pwm otherwise 0 or 1 for value
      //p//SerialPtLnCom("   |");
      Ch_num=-1;
      for (int i = 0; i < DigitalPin; i++) {
        if (oid == DpinOut[i][0]) {
          Ch_num = i;
             DpinOut[Ch_num][5] = clockint;  // Change time
             DpinOut[Ch_num][2] = on_ticks;
              //p//SerialPtLnCom(" DpinSet  clockint " +String(clockint) +" on_ticks: " +String(DpinOut[Ch_num][2] ));
          break;
        }
      }
      //p//SerialPtLnCom("Ch_num: " +String(Ch_num) + " nchan " + String( Nchan));
      //ZeroCrossdata[10][7];// oid || clock || value || default_value || max_duration ||  change at tick || Cycle_ticks
      if (Ch_num == -1) {  //Check in the zero cross
        for (int iu = 0; iu < Nchan; iu++) {
// 0 oid ||1-clock || 2-value || 3-default_value || 4-max_duration ||  5-change at tick || 6-Cycle_ticks

           //p//SerialPtLnCom("OID ck: "+ String(ZeroCrossdata[iu][0]));
          if (oid == ZeroCrossdata[iu][0]) {
            ZeroCrossOID = iu;
            //p//SerialPtLnCom("Zeros Cross=" + String(ZeroCrossOID));
            ZeroCrossdata[iu][2] = int(float(on_ticks)/float(ZeroCrossdata[iu][6])*256);
            ZeroCrossdata[iu][5] = clockint;


        //        ZeroCrossdata[zc_c][2] = ZeroCrossdata[zc_c][3];
   // ZeroCrossdata[zc_c][5] = Offsey_micros() + ZeroCrossdata[zc_c][4];


            //p//SerialPtLnCom("iu " + String(iu) + " Zeros Cross val" + String(ZeroCrossdata[iu][2]) + " Micros " + String(Offsey_micros()) + " Value " + String(on_ticks) +  " clock " + String(clockint) +" | " +String(ZeroCrossdata[iu][5])+ " | " +String(Offsey_micros() > ZeroCrossdata[iu][5]) + " Brightness set: " + String(BrightSetD[iu]));
            break; 
          }
        }
      }
Ch_num = 0;


      break;

    case 16:
      //__  set_digital_out_pwm_cycle   __// Software PWN
      //p//SerialPtLnCom("set_digital_out_pwm_cycle");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      cycle_ticks = IntVals[2];
      //p////p//SerialPtCom("     cycle_ticks=" + String(cycle_ticks));
      //p//SerialPtLnCom("   |");
      Ch_num = -1;
      
      for (int i = 0; i < DigitalPin; i++) {

        if (oid == DpinOut[i][0]) {
          Ch_num = i;
          DpinOut[Ch_num][6] = cycle_ticks;  // Flag for software PWM
          DpinOut[Ch_num][7] = Offsey_micros();     // ticks last pwm
          break;
        }
      }
      if (Ch_num == -1) {  //Check in the zero cross

        for (int iu = 0; iu < Nchan; iu++) {
          if (oid == ZeroCrossdata[iu][0]) {
            ZeroCrossOID = iu;
            // 0 oid ||1-clock || 2-value || 3-default_value || 4-max_duration ||  5-change at tick || 6-Cycle_ticks
            //p//SerialPtLnCom("Zeros Cross=" + String(ZeroCrossOID));
            ZeroCrossdata[ZeroCrossOID][6] = cycle_ticks;
            break;
          }
        }
      }
 Ch_num = 0;

      break;

    case 17:
      //__  config_digital_out   __//


      //p//SerialPtLnCom("config_digital_out");
      if (IntVals[2] >= 50) {
        //p//SerialPtLnCom("this pin can only be hardware pwm");
        IntVals[6] = 10000000;
        IntVals[5] = IntVals[4];
        IntVals[4] = IntVals[3];
        IntVals[3] = 1000;
        Run(46);

      } else {
        oid = IntVals[1];
        //p////p//SerialPtCom("     oid=" + String(oid));
        pin = IntVals[2];
        //p////p//SerialPtCom("     pin=" + String(pin));
        value = IntVals[3];
        //p////p//SerialPtCom("     value=" + String(value));
        default_value = IntVals[4];
        //p////p//SerialPtCom("     default_value=" + String(default_value));
        max_duration = IntVals[5];
        //p////p//SerialPtCom("     max_duration=" + String(max_duration));
        //p//SerialPtLnCom("   |");


        DpinOut[DigitalPin][0] = oid;
        DpinOut[DigitalPin][1] = pin;
        DpinOut[DigitalPin][2] = value;
        DpinOut[DigitalPin][3] = default_value;
        DpinOut[DigitalPin][4] = max_duration;
        DpinOut[DigitalPin][5] = 0;  // Change time
        DpinOut[DigitalPin][6] = 0;  // Flag for software PWM
        DpinOut[DigitalPin][7] = 0;  // ticks last pwm
        DigitalPin++;
      }

      break;
  

    case 18:
      //__  stepper_stop_on_trigger   __//
      //p//SerialPtLnCom("stepper_stop_on_trigger");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      trsync_oid = IntVals[2];
      //p////p//SerialPtCom("     trsync_oid=" + String(trsync_oid));
      //p//SerialPtLnCom("   |");

      break;

    case 19:
      //__  stepper_get_position   __//
      //p//SerialPtLnCom("stepper_get_position");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      //p//SerialPtLnCom("   |");

      break;

    case 20:
      //__  reset_step_clockint   __//
      //p//SerialPtLnCom("reset_step_clockint");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      clockint = IntVals[2];
      //p////p//SerialPtCom("     clockint=" + String(clockint));
      //p//SerialPtLnCom("   |");

      break;

    case 21:
      //__  set_next_step_dir   __//
      //p//SerialPtLnCom("set_next_step_dir");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      dir = IntVals[2];
      //p////p//SerialPtCom("     dir=" + String(dir));
      //p//SerialPtLnCom("   |");

      break;

    case 22:
      //__  queue_step   __//
      //p//SerialPtLnCom("queue_step");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      interval = IntVals[2];
      //p////p//SerialPtCom("     interval=" + String(interval));
      count = IntVals[3];
      //p////p//SerialPtCom("     count=" + String(count));
      add = IntVals[4];
      //p////p//SerialPtCom("     add=" + String(add));
      //p//SerialPtLnCom("   |");

      break;

    case 23:
      //__  config_stepper   __//
      //p//SerialPtLnCom("config_stepper");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      step_pin = IntVals[2];
      //p////p//SerialPtCom("     step_pin=" + String(step_pin));
      dir_pin = IntVals[3];
      //p////p//SerialPtCom("     dir_pin=" + String(dir_pin));
      invert_step = IntVals[4];
      //p////p//SerialPtCom("     invert_step=" + String(invert_step));
      step_pulse_ticks = IntVals[5];
      //p////p//SerialPtCom("     step_pulse_ticks=" + String(step_pulse_ticks));
      //p//SerialPtLnCom("   |");

      break;

    case 24:
      //__  endstop_query_state   __//
      //p//SerialPtLnCom("endstop_query_state");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      //p//SerialPtLnCom("   |");

      break;

    case 25:
      //__  endstop_home   __//
      //p//SerialPtLnCom("endstop_home");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      clockint = IntVals[2];
      //p////p//SerialPtCom("     clockint=" + String(clockint));
      sample_ticks = IntVals[3];
      //p////p//SerialPtCom("     sample_ticks=" + String(sample_ticks));
      sample_count = IntVals[4];
      //p////p//SerialPtCom("     sample_count=" + String(sample_count));
      rest_ticks = IntVals[5];
      //p////p//SerialPtCom("     rest_ticks=" + String(rest_ticks));
      pin_value = IntVals[6];
      //p////p//SerialPtCom("     pin_value=" + String(pin_value));
      trsync_oid = IntVals[7];
      //p////p//SerialPtCom("     trsync_oid=" + String(trsync_oid));
      trigger_reason = IntVals[8];
      //p////p//SerialPtCom("     trigger_reason=" + String(trigger_reason));
      //p//SerialPtLnCom("   |");

      break;

    case 26:
      //__  config_endstop   __//
      //p//SerialPtLnCom("config_endstop");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      pin = IntVals[2];
      //p////p//SerialPtCom("     pin=" + String(pin));
      pull_up = IntVals[3];
      //p////p//SerialPtCom("     pull_up=" + String(pull_up));
      //p//SerialPtLnCom("   |");

      break;

    case 27:
      //__  trsync_trigger   __//
      //p//SerialPtLnCom("trsync_trigger");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      reason = IntVals[2];
      //p////p//SerialPtCom("     reason=" + String(reason));
      //p//SerialPtLnCom("   |");

      break;

    case 28:
      //__  trsync_set_timeout   __//
      //p//SerialPtLnCom("trsync_set_timeout");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      clockint = IntVals[2];
      //p////p//SerialPtCom("     clockint=" + String(clockint));
      //p//SerialPtLnCom("   |");

      break;

    case 29:
      //__  trsync_start   __//
      //p//SerialPtLnCom("trsync_start");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      report_clock = IntVals[2];
      //p////p//SerialPtCom("     report_clock=" + String(report_clock));
      report_ticks = IntVals[3];
      //p////p//SerialPtCom("     report_ticks=" + String(report_ticks));
      expire_reason = IntVals[4];
      //p////p//SerialPtCom("     expire_reason=" + String(expire_reason));
      //p//SerialPtLnCom("   |");

      break;

    case 30:
      //__  config_trsync   __//
      //p//SerialPtLnCom("config_trsync");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      //p//SerialPtLnCom("   |");

      break;

    case 31:
      //__  query_analog_in   __//


      SampleTicks = IntVals[3];

      //p//SerialPtLnCom("query_analog_in");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      clockint = IntVals[2];
      //p////p//SerialPtCom("     clockint=" + String(clockint));
      sample_ticks = IntVals[3];
      //p////p//SerialPtCom("     sample_ticks=" + String(SampleTicks));
      sample_count = IntVals[4];
      //p////p//SerialPtCom("     sample_count=" + String(sample_count));
      rest_ticks = IntVals[5];
      //p////p//SerialPtCom("     rest_ticks=" + String(rest_ticks));
      min_value = IntVals[6];
      //p////p//SerialPtCom("     min_value=" + String(min_value));
      max_value = IntVals[7];
      //p////p//SerialPtCom("     max_value=" + String(max_value));
      range_check_count = IntVals[8];
      //p////p//SerialPtCom("     range_check_count=" + String(range_check_count));
      //p//SerialPtLnCom("   |");

      if (M_off==0){
          if ((clockint+2000000)>micros()){
            M_off=clockint-micros()-500000;
            //p////p//SerialPtCom("     Adding offset to micros=" + String(M_off));
          }
      }
      for (int i = 0; i < 37; i++) {
        if (oid == AnalogMetaData[i][2]) {
          Ch_num = i;
          break;
        }
      }
      //p//SerialPtLnCom("Channel Number " + String(Ch_num));
      // Active // PIn Num // OID  // Index // Sample Ticks // Sample Count // Rest_Ticks //Min_value  // Max_Value //  Range Check Count
      // AnalogTimmingData[Ch_num][1] = Offsey_micros(); // Set the first timmer
      AnalogMetaData[Ch_num][0] = 1;           // Active
      AnalogMetaData[Ch_num][4] = IntVals[3];  // Sample Ticks
      AnalogMetaData[Ch_num][5] = IntVals[4];  // Sample Count
      AnalogMetaData[Ch_num][6] = IntVals[5];  // Rest_Ticks
      AnalogMetaData[Ch_num][7] = IntVals[6];  // Min_value
      AnalogMetaData[Ch_num][8] = IntVals[7];  // Max_Value
      AnalogMetaData[Ch_num][9] = IntVals[8];  // Range Check Count

      //p//SerialPtLnCom(String(AnalogMetaData[Ch_num][0]) + "  " + String(AnalogMetaData[Ch_num][4]) + "  " + String(AnalogMetaData[Ch_num][5]) + "  " + String(AnalogMetaData[Ch_num][6]) + "  " + String(AnalogMetaData[Ch_num][7]) + "  " + String(AnalogMetaData[Ch_num][8]));


      break;

    case 32:
      //__  config_analog_in   __//
      //p//SerialPtLnCom("config_analog_in");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      pin = IntVals[2];
      //p////p//SerialPtCom("     pin=" + String(pin));
      //p//SerialPtLnCom("   |");
      pinMode(pin, INPUT);
      AnalogMetaData[analogChannels][1] = pin;  // active  // PIn Num // OID  // Index //
      AnalogMetaData[analogChannels][2] = oid;  // active // PIn Num // OID  // Index //
      analogChannels++;
      break;

    case 33:
      //__  config_spi_shutdown   __//
      //p//SerialPtLnCom("config_spi_shutdown");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      spi_oid = IntVals[2];
      //p////p//SerialPtCom("     spi_oid=" + String(spi_oid));
      shutdown_msg = StrVals[1];
      //p////p//SerialPtCom("     shutdown_msg=" + shutdown_msg);
      //p//SerialPtLnCom("   |");

      break;

    case 34:
      //__  spi_send   __//
      //p//SerialPtLnCom("spi_send");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      data = StrVals[1];
      //p////p//SerialPtCom("     data=" + data);
      //p//SerialPtLnCom("   |");

      break;

    case 35:
      //__  spi_transfer   __//
      //p//SerialPtLnCom("spi_transfer");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      data = StrVals[1];
      //p////p//SerialPtCom("     data=" + data);
      //p//SerialPtLnCom("   |");

      break;

    case 36:
      //__  spi_set_bus   __//
      //p//SerialPtLnCom("spi_set_bus");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      spi_bus = IntVals[2];
      //p////p//SerialPtCom("     spi_bus=" + String(spi_bus));
      mode = IntVals[3];
      //p////p//SerialPtCom("     mode=" + String(mode));
      rate = IntVals[4];
      //p////p//SerialPtCom("     rate=" + String(rate));
      //p//SerialPtLnCom("   |");

      break;

    case 37:
      //__  config_spi_without_cs   __//
      //p//SerialPtLnCom("config_spi_without_cs");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      //p//SerialPtLnCom("   |");

      break;

    case 38:
      //__  config_spi   __//
      //p//SerialPtLnCom("config_spi");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      pin = IntVals[2];
      //p////p//SerialPtCom("     pin=" + String(pin));
      cs_active_high = IntVals[3];
      //p////p//SerialPtCom("     cs_active_high=" + String(cs_active_high));
      //p//SerialPtLnCom("   |");

      break;

    case 39:
      //__  i2c_modify_bits   __//
      //p//SerialPtLnCom("i2c_modify_bits");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      reg = StrVals[1];
      //p////p//SerialPtCom("     reg=" + reg);
      clear_set_bits = StrVals[2];
      //p////p//SerialPtCom("     clear_set_bits=" + clear_set_bits);
      //p//SerialPtLnCom("   |");

      break;

    case 40:
      //__  i2c_read   __//
      //p//SerialPtLnCom("i2c_read");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      reg = StrVals[1];
      //p////p//SerialPtCom("     reg=" + reg);
      read_len = IntVals[2];
      //p////p//SerialPtCom("     read_len=" + String(read_len));
      //p//SerialPtLnCom("   |");

      break;

    case 41:
      //__  i2c_write   __//
      //p//SerialPtLnCom("i2c_write");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      data = StrVals[1];
      //p////p//SerialPtCom("     data=" + data);
      //p//SerialPtLnCom("   |");

      break;

    case 42:
      //__  i2c_set_bus   __//
      //p//SerialPtLnCom("i2c_set_bus");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      i2c_bus = IntVals[2];
      //p////p//SerialPtCom("     i2c_bus=" + String(i2c_bus));
      rate = IntVals[3];
      //p////p//SerialPtCom("     rate=" + String(rate));
      address = IntVals[4];
      //p////p//SerialPtCom("     address=" + String(address));
      //p//SerialPtLnCom("   |");

      break;

    case 43:
      //__  config_i2c   __//
      //p//SerialPtLnCom("config_i2c");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      //p//SerialPtLnCom("   |");

      break;

    case 44:
      //__  set_pwm_out   __//
      //p//SerialPtLnCom("set_pwm_out");
      pin = IntVals[1];
      //p////p//SerialPtCom("     pin=" + String(pin));
      cycle_ticks = IntVals[2];
      //p////p//SerialPtCom("     cycle_ticks=" + String(cycle_ticks));
      value = IntVals[3];
      //p////p//SerialPtCom("     value=" + String(value));
      //p//SerialPtLnCom("   |");
      for (int iu = 0; iu < pwmChannelCur; iu++) {
        if (oid == pwmdata[iu][0]) {

          ledcSetup(iu, 1000000 / cycle_ticks, 8);
          ledcWrite(iu,value);
          pwmdata[iu][2] = pwmdata[iu][3];
          pwmdata[iu][6] = Offsey_micros() + pwmdata[iu][4];
          pwmdata[iu][7] = cycle_ticks;
          break;
        }
      }
      for (int iu = 0; iu < Nchan; iu++) {
        if (oid == ZeroCrossdata[iu][0]) {

          BrightSetD[iu] = (double(value)  / 256 * 8160);
          ZeroCrossdata[iu][2] = ZeroCrossdata[iu][3];
          ZeroCrossdata[iu][5] = Offsey_micros() + ZeroCrossdata[iu][4];
          ZeroCrossdata[iu][6] = cycle_ticks;
          break;
        }
      }
      break;

    case 45:
      //__  queue_pwm_out   __//
      //p//SerialPtLnCom("queue_pwm_out");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      clockint = IntVals[2];
      //p////p//SerialPtCom("     clockint=" + String(clockint));
      value = IntVals[3];
      //p////p//SerialPtCom("     value=" + String(value));

      //p////p//SerialPtCom("     nchan=" + String(Nchan));
      //p//SerialPtLnCom("   |");
      for (int iu = 0; iu < pwmChannelCur; iu++) {
        if (oid == pwmdata[iu][0]) {
          pwmdata[iu][2] = value;
          pwmdata[iu][6] = clockint;

          break;
        }
      }
      // 0 oid ||1-clock || 2-value || 3-default_value || 4-max_duration ||  5-change at tick || 6-Cycle_ticks
      for (int iu = 0; iu < Nchan; iu++) {
        if (oid == ZeroCrossdata[iu][0]) {
          ZeroCrossdata[iu][2] = value;
          ZeroCrossdata[iu][5] = clockint;
          //p//SerialPtLnCom("iu " + String(iu) + " Value " + String(value) + " clock " + String(clockint));
          break;
        }
      }


      break;

    case 46:





      //__  config_pwm_out   __//
      //p//SerialPtLnCom("config_pwm_out");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      pin = IntVals[2];
      //p////p//SerialPtCom("     pin=" + String(pin));
      cycle_ticks = IntVals[3];
      //p////p//SerialPtCom("     cycle_ticks=" + String(cycle_ticks));
      value = IntVals[4];
      //p////p//SerialPtCom("     value=" + String(value));
      default_value = IntVals[5];
      //p////p//SerialPtCom("     default_value=" + String(default_value));
      max_duration = IntVals[6];
      //p////p//SerialPtCom("     max_duration=" + String(max_duration));
      //p//SerialPtLnCom("   |");



      if (pin < 50) {  //Pin 50 - 59 are virtual zeros cross pins
        pwmdata[pwmChannelCur][0] = oid;
        pwmdata[pwmChannelCur][1] = pin;
      pwmdata[pwmChannelCur][2]=value;
      pwmdata[pwmChannelCur][3]=default_value;
      pwmdata[pwmChannelCur][4] = max_duration;
      pwmdata[pwmChannelCur][5] = Offsey_micros();
      //pwmdata[pwmChannelCur][6]=Change_ticks
      ledcSetup(pwmChannelCur, 1000000 / cycle_ticks, 8);
      ledcAttachPin(pin, pwmChannelCur);
      ledcWrite(pwmChannelCur,value);
      pwmChannelCur++;


      } else if (pin < 60) {  // Assign to a zero cross
      ZCC=-1;
       for (int iu = 0; iu < Nchan; iu++) {
        if (oid == ZeroCrossdata[iu][0]) {
          ZCC=iu;
        }
       }

        if (ZCC==-1){
          ZCC=Nchan;
         Nchan++;
        }
// 0 oid ||1-clock || 2-value || 3-default_value || 4-max_duration ||  5-change at tick || 6-Cycle_ticks
        BrightSetD[ZCC] = double(value) / 256 * 8160;
        GATE[ZCC] = GATE_MAP[pin - 50];
        pinMode(GATE[ZCC], OUTPUT);
        // memcpy(Bright, BrightSet, Nchan*4);
        sort_vals();
        ZeroCrossdata[ZCC][0] = oid;
        ZeroCrossdata[ZCC][1] = Offsey_micros();
        ZeroCrossdata[ZCC][2] = value;
        ZeroCrossdata[ZCC][3] = default_value;
        ZeroCrossdata[ZCC][4] = max_duration;

        // ZeroCrossdata[Nchan][5]=Change_ticks;
        //p//SerialPtLnCom(" Zero Cross Setup-> OID: " + String(oid) + "  Pin:" + String(GATE[ZCC]) + " Cur time: " + String(ZeroCrossdata[ZCC][1]) + " Value: " + String(ZeroCrossdata[ZCC][2]) + " Def Val: " + String(ZeroCrossdata[ZCC][3]) + " Chang T: " + String(ZeroCrossdata[ZCC][4]) + "  Chan num:" + String(Nchan));
        
      }


      break;

    case 47:
      //__  buttons_ack   __//
      //p//SerialPtLnCom("buttons_ack");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      count = IntVals[2];
      //p////p//SerialPtCom("     count=" + String(count));
      //p//SerialPtLnCom("   |");

      break;

    case 48:
      //__  buttons_query   __//
      //p//SerialPtLnCom("buttons_query");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      clockint = IntVals[2];
      //p////p//SerialPtCom("     clockint=" + String(clockint));
      rest_ticks = IntVals[3];
      //p////p//SerialPtCom("     rest_ticks=" + String(rest_ticks));
      retransmit_count = IntVals[4];
      //p////p//SerialPtCom("     retransmit_count=" + String(retransmit_count));
      invert = IntVals[5];
      //p////p//SerialPtCom("     invert=" + String(invert));
      //p//SerialPtLnCom("   |");

      break;

    case 49:
      //__  buttons_add   __//
      //p//SerialPtLnCom("buttons_add");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      pos = IntVals[2];
      //p////p//SerialPtCom("     pos=" + String(pos));
      pin = IntVals[3];
      //p////p//SerialPtCom("     pin=" + String(pin));
      pull_up = IntVals[4];
      //p////p//SerialPtCom("     pull_up=" + String(pull_up));
      //p//SerialPtLnCom("   |");

      break;

    case 50:
      //__  config_buttons   __//
      //p//SerialPtLnCom("config_buttons");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      button_count = IntVals[2];
      //p////p//SerialPtCom("     button_count=" + String(button_count));
      //p//SerialPtLnCom("   |");

      break;

    case 51:
      //__  tmcuart_send   __//
      //p//SerialPtLnCom("tmcuart_send");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      writestr = StrVals[1];
      //p////p//SerialPtCom("     writestr=" + writestr);
      readint = IntVals[2];
      //p////p//SerialPtCom("     readint=" + String(readint));
      //p//SerialPtLnCom("   |");

      break;

    case 52:
      //__  config_tmcuart   __//
      //p//SerialPtLnCom("config_tmcuart");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      rx_pin = IntVals[2];
      //p////p//SerialPtCom("     rx_pin=" + String(rx_pin));
      pull_up = IntVals[3];
      //p////p//SerialPtCom("     pull_up=" + String(pull_up));
      tx_pin = IntVals[4];
      //p////p//SerialPtCom("     tx_pin=" + String(tx_pin));
      bit_time = IntVals[5];
      //p////p//SerialPtCom("     bit_time=" + String(bit_time));
      //p//SerialPtLnCom("   |");

      break;

    case 53:
      //__  neopixel_send   __//
      //p//SerialPtLnCom("neopixel_send");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      //p//SerialPtLnCom("   |");

      break;

    case 54:
      //__  neopixel_update   __//
      //p//SerialPtLnCom("neopixel_update");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      pos = IntVals[2];
      //p////p//SerialPtCom("     pos=" + String(pos));
      data = StrVals[1];
      //p////p//SerialPtCom("     data=" + data);
      //p//SerialPtLnCom("   |");

      break;

    case 55:
      //__  config_neopixel   __//
      //p//SerialPtLnCom("config_neopixel");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      pin = IntVals[2];
      //p////p//SerialPtCom("     pin=" + String(pin));
      data_size = IntVals[3];
      //p////p//SerialPtCom("     data_size=" + String(data_size));
      bit_max_ticks = IntVals[4];
      //p////p//SerialPtCom("     bit_max_ticks=" + String(bit_max_ticks));
      reset_min_ticks = IntVals[5];
      //p////p//SerialPtCom("     reset_min_ticks=" + String(reset_min_ticks));
      //p//SerialPtLnCom("   |");

      break;

    case 56:
      //__  query_counter   __//
      //p//SerialPtLnCom("query_counter");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      clockint = IntVals[2];
      //p////p//SerialPtCom("     clockint=" + String(clockint));
      poll_ticks = IntVals[3];
      //p////p//SerialPtCom("     poll_ticks=" + String(poll_ticks));
      sample_ticks = IntVals[4];
      //p////p//SerialPtCom("     sample_ticks=" + String(sample_ticks));
      //p//SerialPtLnCom("   |");

      break;

    case 57:
      //__  config_counter   __//
      //p//SerialPtLnCom("config_counter");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      pin = IntVals[2];
      //p////p//SerialPtCom("     pin=" + String(pin));
      pull_up = IntVals[3];
      //p////p//SerialPtCom("     pull_up=" + String(pull_up));
      //p//SerialPtLnCom("   |");

      break;

    case 58:
      //__  st7920_send_data   __//
      //p//SerialPtLnCom("st7920_send_data");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      data = StrVals[1];
      //p////p//SerialPtCom("     data=" + data);
      //p//SerialPtLnCom("   |");

      break;

    case 59:
      //__  st7920_send_cmds   __//
      //p//SerialPtLnCom("st7920_send_cmds");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      cmds = StrVals[1];
      //p////p//SerialPtCom("     cmds=" + cmds);
      //p//SerialPtLnCom("   |");

      break;

    case 60:
      //__  config_st7920   __//
      //p//SerialPtLnCom("config_st7920");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      cs_pin = IntVals[2];
      //p////p//SerialPtCom("     cs_pin=" + String(cs_pin));
      sclk_pin = IntVals[3];
      //p////p//SerialPtCom("     sclk_pin=" + String(sclk_pin));
      sid_pin = IntVals[4];
      //p////p//SerialPtCom("     sid_pin=" + String(sid_pin));
      sync_delay_ticks = IntVals[5];
      //p////p//SerialPtCom("     sync_delay_ticks=" + String(sync_delay_ticks));
      cmd_delay_ticks = IntVals[6];
      //p////p//SerialPtCom("     cmd_delay_ticks=" + String(cmd_delay_ticks));
      //p//SerialPtLnCom("   |");

      break;

    case 61:
      //__  hd44780_send_data   __//
      //p//SerialPtLnCom("hd44780_send_data");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      data = StrVals[1];
      //p////p//SerialPtCom("     data=" + data);
      //p//SerialPtLnCom("   |");

      break;

    case 62:
      //__  hd44780_send_cmds   __//
      //p//SerialPtLnCom("hd44780_send_cmds");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      cmds = StrVals[1];
      //p////p//SerialPtCom("     cmds=" + cmds);
      //p//SerialPtLnCom("   |");

      break;

    case 63:
      //__  config_hd44780   __//
      //p//SerialPtLnCom("config_hd44780");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      rs_pin = IntVals[2];
      //p////p//SerialPtCom("     rs_pin=" + String(rs_pin));
      e_pin = IntVals[3];
      //p////p//SerialPtCom("     e_pin=" + String(e_pin));
      d4_pin = IntVals[4];
      //p////p//SerialPtCom("     d4_pin=" + String(d4_pin));
      d5_pin = IntVals[5];
      //p////p//SerialPtCom("     d5_pin=" + String(d5_pin));
      d6_pin = IntVals[6];
      //p////p//SerialPtCom("     d6_pin=" + String(d6_pin));
      d7_pin = IntVals[7];
      //p////p//SerialPtCom("     d7_pin=" + String(d7_pin));
      delay_ticks = IntVals[8];
      //p////p//SerialPtCom("     delay_ticks=" + String(delay_ticks));
      //p//SerialPtLnCom("   |");

      break;

    case 64:
      //__  spi_set_software_bus   __//
      //p//SerialPtLnCom("spi_set_software_bus");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      miso_pin = IntVals[2];
      //p////p//SerialPtCom("     miso_pin=" + String(miso_pin));
      mosi_pin = IntVals[3];
      //p////p//SerialPtCom("     mosi_pin=" + String(mosi_pin));
      sclk_pin = IntVals[4];
      //p////p//SerialPtCom("     sclk_pin=" + String(sclk_pin));
      mode = IntVals[5];
      //p////p//SerialPtCom("     mode=" + String(mode));
      rate = IntVals[6];
      //p////p//SerialPtCom("     rate=" + String(rate));
      //p//SerialPtLnCom("   |");

      break;

    case 65:
      //__  i2c_set_software_bus   __//
      //p//SerialPtLnCom("i2c_set_software_bus");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      scl_pin = IntVals[2];
      //p////p//SerialPtCom("     scl_pin=" + String(scl_pin));
      sda_pin = IntVals[3];
      //p////p//SerialPtCom("     sda_pin=" + String(sda_pin));
      rate = IntVals[4];
      //p////p//SerialPtCom("     rate=" + String(rate));
      address = IntVals[5];
      //p////p//SerialPtCom("     address=" + String(address));
      //p//SerialPtLnCom("   |");

      break;

    case 66:
      //__  query_thermocouple   __//
      //p//SerialPtLnCom("query_thermocouple");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      clockint = IntVals[2];
      //p////p//SerialPtCom("     clockint=" + String(clockint));
      rest_ticks = IntVals[3];
      //p////p//SerialPtCom("     rest_ticks=" + String(rest_ticks));
      min_value = IntVals[4];
      //p////p//SerialPtCom("     min_value=" + String(min_value));
      max_value = IntVals[5];
      //p////p//SerialPtCom("     max_value=" + String(max_value));
      max_invalid_count = IntVals[6];
      //p////p//SerialPtCom("     max_invalid_count=" + String(max_invalid_count));
      //p//SerialPtLnCom("   |");

      break;

    case 67:
      //__  config_thermocouple   __//
      //p//SerialPtLnCom("config_thermocouple");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      spi_oid = IntVals[2];
      //p////p//SerialPtCom("     spi_oid=" + String(spi_oid));
      thermocouple_type = IntVals[3];
      //p////p//SerialPtCom("     thermocouple_type=" + String(thermocouple_type));
      //p//SerialPtLnCom("   |");

      break;

    case 68:
      //__  query_adxl345_status   __//
      //p//SerialPtLnCom("query_adxl345_status");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      //p//SerialPtLnCom("   |");

      break;

    case 69:
      //__  query_adxl345   __//
      //p//SerialPtLnCom("query_adxl345");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      rest_ticks = IntVals[2];
      //p////p//SerialPtCom("     rest_ticks=" + String(rest_ticks));
      //p//SerialPtLnCom("   |");

      break;

    case 70:
      //__  config_adxl345   __//
      //p//SerialPtLnCom("config_adxl345");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      spi_oid = IntVals[2];
      //p////p//SerialPtCom("     spi_oid=" + String(spi_oid));
      //p//SerialPtLnCom("   |");

      break;

    case 71:
      //__  spi_angle_transfer   __//
      //p//SerialPtLnCom("spi_angle_transfer");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      data = StrVals[1];
      //p////p//SerialPtCom("     data=" + data);
      //p//SerialPtLnCom("   |");

      break;

    case 72:
      //__  query_spi_angle   __//
      //p//SerialPtLnCom("query_spi_angle");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      clockint = IntVals[2];
      //p////p//SerialPtCom("     clockint=" + String(clockint));
      rest_ticks = IntVals[3];
      //p////p//SerialPtCom("     rest_ticks=" + String(rest_ticks));
      time_shift = IntVals[4];
      //p////p//SerialPtCom("     time_shift=" + String(time_shift));
      //p//SerialPtLnCom("   |");

      break;

    case 73:
      //__  config_spi_angle   __//
      //p//SerialPtLnCom("config_spi_angle");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      spi_oid = IntVals[2];
      //p////p//SerialPtCom("     spi_oid=" + String(spi_oid));
      spi_angle_type = IntVals[3];
      //p////p//SerialPtCom("     spi_angle_type=" + String(spi_angle_type));
      //p//SerialPtLnCom("   |");

      break;

    case 74:
      //__  query_mpu9250_status   __//
      //p//SerialPtLnCom("query_mpu9250_status");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      //p//SerialPtLnCom("   |");

      break;

    case 75:
      //__  query_mpu9250   __//
      //p//SerialPtLnCom("query_mpu9250");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      rest_ticks = IntVals[2];
      //p////p//SerialPtCom("     rest_ticks=" + String(rest_ticks));
      //p//SerialPtLnCom("   |");

      break;

    case 76:
      //__  config_mpu9250   __//
      //p//SerialPtLnCom("config_mpu9250");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      i2c_oid = IntVals[2];
      //p////p//SerialPtCom("     i2c_oid=" + String(i2c_oid));
      //p//SerialPtLnCom("   |");

      break;

    case 77:
      //__  query_lis2dw_status   __//
      //p//SerialPtLnCom("query_lis2dw_status");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      //p//SerialPtLnCom("   |");

      break;

    case 78:
      //__  query_lis2dw   __//
      //p//SerialPtLnCom("query_lis2dw");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      rest_ticks = IntVals[2];
      //p////p//SerialPtCom("     rest_ticks=" + String(rest_ticks));
      //p//SerialPtLnCom("   |");

      break;

    case 79:
      //__  config_lis2dw   __//
      //p//SerialPtLnCom("config_lis2dw");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      spi_oid = IntVals[2];
      //p////p//SerialPtCom("     spi_oid=" + String(spi_oid));
      //p//SerialPtLnCom("   |");

      break;

    case 80:
      //__  query_status_ldc1612   __//
      //p//SerialPtLnCom("query_status_ldc1612");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      //p//SerialPtLnCom("   |");

      break;

    case 81:
      //__  query_ldc1612   __//
      //p//SerialPtLnCom("query_ldc1612");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      rest_ticks = IntVals[2];
      //p////p//SerialPtCom("     rest_ticks=" + String(rest_ticks));
      //p//SerialPtLnCom("   |");

      break;

    case 82:
      //__  query_ldc1612_home_state   __//
      //p//SerialPtLnCom("query_ldc1612_home_state");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      //p//SerialPtLnCom("   |");

      break;

    case 83:
      //__  ldc1612_setup_home   __//
      //p//SerialPtLnCom("ldc1612_setup_home");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      clockint = IntVals[2];
      //p////p//SerialPtCom("     clockint=" + String(clockint));
      threshold = IntVals[3];
      //p////p//SerialPtCom("     threshold=" + String(threshold));
      trsync_oid = IntVals[4];
      //p////p//SerialPtCom("     trsync_oid=" + String(trsync_oid));
      trigger_reason = IntVals[5];
      //p////p//SerialPtCom("     trigger_reason=" + String(trigger_reason));
      error_reason = IntVals[6];
      //p////p//SerialPtCom("     error_reason=" + String(error_reason));
      //p//SerialPtLnCom("   |");

      break;

    case 84:
      //__  config_ldc1612_with_intb   __//
      //p//SerialPtLnCom("config_ldc1612_with_intb");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      i2c_oid = IntVals[2];
      //p////p//SerialPtCom("     i2c_oid=" + String(i2c_oid));
      intb_pin = IntVals[3];
      //p////p//SerialPtCom("     intb_pin=" + String(intb_pin));
      //p//SerialPtLnCom("   |");

      break;

    case 85:
      //__  config_ldc1612   __//
      //p//SerialPtLnCom("config_ldc1612");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      i2c_oid = IntVals[2];
      //p////p//SerialPtCom("     i2c_oid=" + String(i2c_oid));
      //p//SerialPtLnCom("   |");

      break;

    case 86:
      //__  query_hx71x_status   __//
      //p//SerialPtLnCom("query_hx71x_status");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      //p//SerialPtLnCom("   |");

      break;

    case 87:
      //__  query_hx71x   __//
      //p//SerialPtLnCom("query_hx71x");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      rest_ticks = IntVals[2];
      //p////p//SerialPtCom("     rest_ticks=" + String(rest_ticks));
      //p//SerialPtLnCom("   |");

      break;

    case 88:
      //__  config_hx71x   __//
      //p//SerialPtLnCom("config_hx71x");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      gain_channel = IntVals[2];
      //p////p//SerialPtCom("     gain_channel=" + String(gain_channel));
      dout_pin = IntVals[3];
      //p////p//SerialPtCom("     dout_pin=" + String(dout_pin));
      sclk_pin = IntVals[4];
      //p////p//SerialPtCom("     sclk_pin=" + String(sclk_pin));
      //p//SerialPtLnCom("   |");

      break;

    case 89:
      //__  query_ads1220_status   __//
      //p//SerialPtLnCom("query_ads1220_status");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      //p//SerialPtLnCom("   |");

      break;

    case 90:
      //__  query_ads1220   __//
      //p//SerialPtLnCom("query_ads1220");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      rest_ticks = IntVals[2];
      //p////p//SerialPtCom("     rest_ticks=" + String(rest_ticks));
      //p//SerialPtLnCom("   |");

      break;

    case 91:
      //__  config_ads1220   __//
      //p//SerialPtLnCom("config_ads1220");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      spi_oid = IntVals[2];
      //p////p//SerialPtCom("     spi_oid=" + String(spi_oid));
      data_ready_pin = IntVals[3];
      //p////p//SerialPtCom("     data_ready_pin=" + String(data_ready_pin));
      //p//SerialPtLnCom("   |");

      break;

    case 92:
      //__  reset   __//
      //p//SerialPtLnCom("reset");
      //p//SerialPtLnCom("   |");
      ESP.restart();
      break;

    case 93:
      //__  starting   __//
      //p//SerialPtLnCom("starting");
      //p//SerialPtLnCom("   |");

      break;

    case 94:
      //__  is_shutdown   __//
      //p//SerialPtLnCom("is_shutdown");
      static_string_id = IntVals[1];
      //p////p//SerialPtCom("     static_string_id=" + String(static_string_id));
      //p//SerialPtLnCom("   |");

      break;

    case 95:
      //__  shutdown   __//
      //p//SerialPtLnCom("shutdown");
      clockint = IntVals[1];
      //p////p//SerialPtCom("     clockint=" + String(clockint));
      static_string_id = IntVals[2];
      //p////p//SerialPtCom("     static_string_id=" + String(static_string_id));
      //p//SerialPtLnCom("   |");

      is_shutdown = 1;

      break;

    case -32:
      //__  stats   __//
      //p//SerialPtLnCom("stats");
      count = IntVals[1];
      //p////p//SerialPtCom("     count=" + String(count));
      sum = IntVals[2];
      //p////p//SerialPtCom("     sum=" + String(sum));
      sumsq = IntVals[3];
      //p////p//SerialPtCom("     sumsq=" + String(sumsq));
      //p//SerialPtLnCom("   |");

      break;

    case -31:
      //__  uptime   __//
      //p//SerialPtLnCom("uptime");
      high = IntVals[1];
      //p////p//SerialPtCom("     high=" + String(high));
      clockint = IntVals[2];
      //p////p//SerialPtCom("     clockint=" + String(clockint));
      //p//SerialPtLnCom("   |");

      break;

    case -30:
      //__  clock   __//
      //p//SerialPtLnCom("clockint");
      clockint = IntVals[1];
      //p////p//SerialPtCom("     clockint=" + String(clockint));
      //p//SerialPtLnCom("   |");

      break;

    case -29:
      //__  config   __//
      //p//SerialPtLnCom("config");
      is_config = IntVals[1];
      //p////p//SerialPtCom("     is_config=" + String(is_config));
      crc = IntVals[2];
      //p////p//SerialPtCom("     crc=" + String(crc));
      is_shutdown = IntVals[3];
      //p////p//SerialPtCom("     is_shutdown=" + String(is_shutdown));
      move_count = IntVals[4];
      //p////p//SerialPtCom("     move_count=" + String(move_count));
      //p//SerialPtLnCom("   |");



      break;

    case -28:
      //__  pong   __//
      //p//SerialPtLnCom("pong");
      data = StrVals[1];
      //p////p//SerialPtCom("     data=" + data);
      //p//SerialPtLnCom("   |");

      break;

    case -27:
      //__  debug_result   __//
      //p//SerialPtLnCom("debug_result");
      val = IntVals[1];
      //p////p//SerialPtCom("     val=" + String(val));
      //p//SerialPtLnCom("   |");

      break;

    case -26:
      //__  stepper_position   __//
      //p//SerialPtLnCom("stepper_position");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      pos = IntVals[2];
      //p////p//SerialPtCom("     pos=" + String(pos));
      //p//SerialPtLnCom("   |");

      break;

    case -25:
      //__  endstop_state   __//
      //p//SerialPtLnCom("endstop_state");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      homing = IntVals[2];
      //p////p//SerialPtCom("     homing=" + String(homing));
      next_clock = IntVals[3];
      //p////p//SerialPtCom("     next_clock=" + String(next_clock));
      pin_value = IntVals[4];
      //p////p//SerialPtCom("     pin_value=" + String(pin_value));
      //p//SerialPtLnCom("   |");

      break;

    case -24:
      //__  trsync_state   __//
      //p//SerialPtLnCom("trsync_state");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      can_trigger = IntVals[2];
      //p////p//SerialPtCom("     can_trigger=" + String(can_trigger));
      trigger_reason = IntVals[3];
      //p////p//SerialPtCom("     trigger_reason=" + String(trigger_reason));
      clockint = IntVals[4];
      //p////p//SerialPtCom("     clockint=" + String(clockint));
      //p//SerialPtLnCom("   |");

      break;

    case -23:
      //__  analog_in_state   __//
      //p//SerialPtLnCom("analog_in_state");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      next_clock = IntVals[2];
      //p////p//SerialPtCom("     next_clock=" + String(next_clock));
      value = IntVals[3];
      //p////p//SerialPtCom("     value=" + String(value));
      //p//SerialPtLnCom("   |");

      break;

    case -22:
      //__  spi_transfer_response   __//
      //p//SerialPtLnCom("spi_transfer_response");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      response = StrVals[1];
      //p////p//SerialPtCom("     response=" + response);
      //p//SerialPtLnCom("   |");

      break;

    case -21:
      //__  i2c_read_response   __//
      //p//SerialPtLnCom("i2c_read_response");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      response = StrVals[1];
      //p////p//SerialPtCom("     response=" + response);
      //p//SerialPtLnCom("   |");

      break;

    case -20:
      //__  buttons_state   __//
      //p//SerialPtLnCom("buttons_state");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      ack_count = IntVals[2];
      //p////p//SerialPtCom("     ack_count=" + String(ack_count));
      state = StrVals[1];
      //p////p//SerialPtCom("     state=" + state);
      //p//SerialPtLnCom("   |");

      break;

    case -19:
      //__  tmcuart_response   __//
      //p//SerialPtLnCom("tmcuart_response");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      readstr = StrVals[1];
      //p////p//SerialPtCom("     readstr=" + readstr);
      //p//SerialPtLnCom("   |");

      break;

    case -18:
      //__  neopixel_result   __//
      //p//SerialPtLnCom("neopixel_result");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      success = IntVals[2];
      //p////p//SerialPtCom("     success=" + String(success));
      //p//SerialPtLnCom("   |");

      break;

    case -17:
      //__  counter_state   __//
      //p//SerialPtLnCom("counter_state");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      next_clock = IntVals[2];
      //p////p//SerialPtCom("     next_clock=" + String(next_clock));
      count = IntVals[3];
      //p////p//SerialPtCom("     count=" + String(count));
      count_clock = IntVals[4];
      //p////p//SerialPtCom("     count_clock=" + String(count_clock));
      //p//SerialPtLnCom("   |");

      break;

    case -16:
      //__  thermocouple_result   __//
      //p//SerialPtLnCom("thermocouple_result");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      next_clock = IntVals[2];
      //p////p//SerialPtCom("     next_clock=" + String(next_clock));
      value = IntVals[3];
      //p////p//SerialPtCom("     value=" + String(value));
      fault = IntVals[4];
      //p////p//SerialPtCom("     fault=" + String(fault));
      //p//SerialPtLnCom("   |");

      break;

    case -15:
      //__  spi_angle_transfer_response   __//
      //p//SerialPtLnCom("spi_angle_transfer_response");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      clockint = IntVals[2];
      //p////p//SerialPtCom("     clockint=" + String(clockint));
      response = StrVals[1];
      //p////p//SerialPtCom("     response=" + response);
      //p//SerialPtLnCom("   |");

      break;

    case -14:
      //__  ldc1612_home_state   __//
      //p//SerialPtLnCom("ldc1612_home_state");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      homing = IntVals[2];
      //p////p//SerialPtCom("     homing=" + String(homing));
      trigger_clock = IntVals[3];
      //p////p//SerialPtCom("     trigger_clock=" + String(trigger_clock));
      //p//SerialPtLnCom("   |");

      break;

    case -13:
      //__  sensor_bulk_status   __//
      //p//SerialPtLnCom("sensor_bulk_status");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      clockint = IntVals[2];
      //p////p//SerialPtCom("     clockint=" + String(clockint));
      query_ticks = IntVals[3];
      //p////p//SerialPtCom("     query_ticks=" + String(query_ticks));
      next_sequence = IntVals[4];
      //p////p//SerialPtCom("     next_sequence=" + String(next_sequence));
      buffered = IntVals[5];
      //p////p//SerialPtCom("     buffered=" + String(buffered));
      possible_overflows = IntVals[6];
      //p////p//SerialPtCom("     possible_overflows=" + String(possible_overflows));
      //p//SerialPtLnCom("   |");

      break;

    case -12:
      //__  sensor_bulk_data   __//
      //p//SerialPtLnCom("sensor_bulk_data");
      oid = IntVals[1];
      //p////p//SerialPtCom("     oid=" + String(oid));
      sequence = IntVals[2];
      //p////p//SerialPtCom("     sequence=" + String(sequence));
      data = StrVals[1];
      //p////p//SerialPtCom("     data=" + data);
      //p//SerialPtLnCom("   |");

      break;
    default:
      //p//SerialPtLnCom("Function " + String(Command) + " Does not exist in library");

      break;
  }
}
