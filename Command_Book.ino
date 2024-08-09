case 1:
   //__  identify   __//
   offset=IntVals[1];
   count=IntVals[2];

   break;
case 2:
   //__  clear_shutdown   __//

   break;
case 3:
   //__  emergency_stop   __//

   break;
case 4:
   //__  get_uptime   __//

   break;
case 5:
   //__  get_clock   __//

   break;
case 6:
   //__  finalize_config   __//
   crc=IntVals[1];

   break;
case 7:
   //__  get_config   __//

   break;
case 8:
   //__  allocate_oids   __//
   count=IntVals[1];

   break;
case 9:
   //__  debug_nop   __//

   break;
case 10:
   //__  debug_ping   __//
   data=StrVals[1];

   break;
case 11:
   //__  debug_write   __//
   order=IntVals[1];
   addr=IntVals[2];
   val=IntVals[3];

   break;
case 12:
   //__  debug_read   __//
   order=IntVals[1];
   addr=IntVals[2];

   break;
case 13:
   //__  set_digital_out   __//
   pin=IntVals[1];
   value=IntVals[2];

   break;
case 14:
   //__  update_digital_out   __//
   oid=IntVals[1];
   value=IntVals[2];

   break;
case 15:
   //__  queue_digital_out   __//
   oid=IntVals[1];
   clock=IntVals[2];
   on_ticks=IntVals[3];

   break;
case 16:
   //__  set_digital_out_pwm_cycle   __//
   oid=IntVals[1];
   cycle_ticks=IntVals[2];

   break;
case 17:
   //__  config_digital_out   __//
   oid=IntVals[1];
   pin=IntVals[2];
   value=IntVals[3];
   default_value=IntVals[4];
   max_duration=IntVals[5];

   break;
case 18:
   //__  stepper_stop_on_trigger   __//
   oid=IntVals[1];
   trsync_oid=IntVals[2];

   break;
case 19:
   //__  stepper_get_position   __//
   oid=IntVals[1];

   break;
case 20:
   //__  reset_step_clock   __//
   oid=IntVals[1];
   clock=IntVals[2];

   break;
case 21:
   //__  set_next_step_dir   __//
   oid=IntVals[1];
   dir=IntVals[2];

   break;
case 22:
   //__  queue_step   __//
   oid=IntVals[1];
   interval=IntVals[2];
   count=IntVals[3];
   add=IntVals[4];

   break;
case 23:
   //__  config_stepper   __//
   oid=IntVals[1];
   step_pin=IntVals[2];
   dir_pin=IntVals[3];
   invert_step=IntVals[4];
   step_pulse_ticks=IntVals[5];

   break;
case 24:
   //__  endstop_query_state   __//
   oid=IntVals[1];

   break;
case 25:
   //__  endstop_home   __//
   oid=IntVals[1];
   clock=IntVals[2];
   sample_ticks=IntVals[3];
   sample_count=IntVals[4];
   rest_ticks=IntVals[5];
   pin_value=IntVals[6];
   trsync_oid=IntVals[7];
   trigger_reason=IntVals[8];

   break;
case 26:
   //__  config_endstop   __//
   oid=IntVals[1];
   pin=IntVals[2];
   pull_up=IntVals[3];

   break;
case 27:
   //__  trsync_trigger   __//
   oid=IntVals[1];
   reason=IntVals[2];

   break;
case 28:
   //__  trsync_set_timeout   __//
   oid=IntVals[1];
   clock=IntVals[2];

   break;
case 29:
   //__  trsync_start   __//
   oid=IntVals[1];
   report_clock=IntVals[2];
   report_ticks=IntVals[3];
   expire_reason=IntVals[4];

   break;
case 30:
   //__  config_trsync   __//
   oid=IntVals[1];

   break;
case 31:
   //__  query_analog_in   __//
   oid=IntVals[1];
   clock=IntVals[2];
   sample_ticks=IntVals[3];
   sample_count=IntVals[4];
   rest_ticks=IntVals[5];
   min_value=IntVals[6];
   max_value=IntVals[7];
   range_check_count=IntVals[8];

   break;
case 32:
   //__  config_analog_in   __//
   oid=IntVals[1];
   pin=IntVals[2];

   break;
case 33:
   //__  config_spi_shutdown   __//
   oid=IntVals[1];
   spi_oid=IntVals[2];
   shutdown_msg=StrVals[1];

   break;
case 34:
   //__  spi_send   __//
   oid=IntVals[1];
   data=StrVals[1];

   break;
case 35:
   //__  spi_transfer   __//
   oid=IntVals[1];
   data=StrVals[1];

   break;
case 36:
   //__  spi_set_bus   __//
   oid=IntVals[1];
   spi_bus=IntVals[2];
   mode=IntVals[3];
   rate=IntVals[4];

   break;
case 37:
   //__  config_spi_without_cs   __//
   oid=IntVals[1];

   break;
case 38:
   //__  config_spi   __//
   oid=IntVals[1];
   pin=IntVals[2];
   cs_active_high=IntVals[3];

   break;
case 39:
   //__  i2c_modify_bits   __//
   oid=IntVals[1];
   reg=StrVals[1];
   clear_set_bits=StrVals[2];

   break;
case 40:
   //__  i2c_read   __//
   oid=IntVals[1];
   reg=StrVals[1];
   read_len=IntVals[2];

   break;
case 41:
   //__  i2c_write   __//
   oid=IntVals[1];
   data=StrVals[1];

   break;
case 42:
   //__  i2c_set_bus   __//
   oid=IntVals[1];
   i2c_bus=IntVals[2];
   rate=IntVals[3];
   address=IntVals[4];

   break;
case 43:
   //__  config_i2c   __//
   oid=IntVals[1];

   break;
case 44:
   //__  set_pwm_out   __//
   pin=IntVals[1];
   cycle_ticks=IntVals[2];
   value=IntVals[3];

   break;
case 45:
   //__  queue_pwm_out   __//
   oid=IntVals[1];
   clock=IntVals[2];
   value=IntVals[3];

   break;
case 46:
   //__  config_pwm_out   __//
   oid=IntVals[1];
   pin=IntVals[2];
   cycle_ticks=IntVals[3];
   value=IntVals[4];
   default_value=IntVals[5];
   max_duration=IntVals[6];

   break;
case 47:
   //__  buttons_ack   __//
   oid=IntVals[1];
   count=IntVals[2];

   break;
case 48:
   //__  buttons_query   __//
   oid=IntVals[1];
   clock=IntVals[2];
   rest_ticks=IntVals[3];
   retransmit_count=IntVals[4];
   invert=IntVals[5];

   break;
case 49:
   //__  buttons_add   __//
   oid=IntVals[1];
   pos=IntVals[2];
   pin=IntVals[3];
   pull_up=IntVals[4];

   break;
case 50:
   //__  config_buttons   __//
   oid=IntVals[1];
   button_count=IntVals[2];

   break;
case 51:
   //__  tmcuart_send   __//
   oid=IntVals[1];
   write=StrVals[1];
   read=IntVals[2];

   break;
case 52:
   //__  config_tmcuart   __//
   oid=IntVals[1];
   rx_pin=IntVals[2];
   pull_up=IntVals[3];
   tx_pin=IntVals[4];
   bit_time=IntVals[5];

   break;
case 53:
   //__  neopixel_send   __//
   oid=IntVals[1];

   break;
case 54:
   //__  neopixel_update   __//
   oid=IntVals[1];
   pos=IntVals[2];
   data=StrVals[1];

   break;
case 55:
   //__  config_neopixel   __//
   oid=IntVals[1];
   pin=IntVals[2];
   data_size=IntVals[3];
   bit_max_ticks=IntVals[4];
   reset_min_ticks=IntVals[5];

   break;
case 56:
   //__  query_counter   __//
   oid=IntVals[1];
   clock=IntVals[2];
   poll_ticks=IntVals[3];
   sample_ticks=IntVals[4];

   break;
case 57:
   //__  config_counter   __//
   oid=IntVals[1];
   pin=IntVals[2];
   pull_up=IntVals[3];

   break;
case 58:
   //__  st7920_send_data   __//
   oid=IntVals[1];
   data=StrVals[1];

   break;
case 59:
   //__  st7920_send_cmds   __//
   oid=IntVals[1];
   cmds=StrVals[1];

   break;
case 60:
   //__  config_st7920   __//
   oid=IntVals[1];
   cs_pin=IntVals[2];
   sclk_pin=IntVals[3];
   sid_pin=IntVals[4];
   sync_delay_ticks=IntVals[5];
   cmd_delay_ticks=IntVals[6];

   break;
case 61:
   //__  hd44780_send_data   __//
   oid=IntVals[1];
   data=StrVals[1];

   break;
case 62:
   //__  hd44780_send_cmds   __//
   oid=IntVals[1];
   cmds=StrVals[1];

   break;
case 63:
   //__  config_hd44780   __//
   oid=IntVals[1];
   rs_pin=IntVals[2];
   e_pin=IntVals[3];
   d4_pin=IntVals[4];
   d5_pin=IntVals[5];
   d6_pin=IntVals[6];
   d7_pin=IntVals[7];
   delay_ticks=IntVals[8];

   break;
case 64:
   //__  spi_set_software_bus   __//
   oid=IntVals[1];
   miso_pin=IntVals[2];
   mosi_pin=IntVals[3];
   sclk_pin=IntVals[4];
   mode=IntVals[5];
   rate=IntVals[6];

   break;
case 65:
   //__  i2c_set_software_bus   __//
   oid=IntVals[1];
   scl_pin=IntVals[2];
   sda_pin=IntVals[3];
   rate=IntVals[4];
   address=IntVals[5];

   break;
case 66:
   //__  query_thermocouple   __//
   oid=IntVals[1];
   clock=IntVals[2];
   rest_ticks=IntVals[3];
   min_value=IntVals[4];
   max_value=IntVals[5];
   max_invalid_count=IntVals[6];

   break;
case 67:
   //__  config_thermocouple   __//
   oid=IntVals[1];
   spi_oid=IntVals[2];
   thermocouple_type=IntVals[3];

   break;
case 68:
   //__  query_adxl345_status   __//
   oid=IntVals[1];

   break;
case 69:
   //__  query_adxl345   __//
   oid=IntVals[1];
   rest_ticks=IntVals[2];

   break;
case 70:
   //__  config_adxl345   __//
   oid=IntVals[1];
   spi_oid=IntVals[2];

   break;
case 71:
   //__  spi_angle_transfer   __//
   oid=IntVals[1];
   data=StrVals[1];

   break;
case 72:
   //__  query_spi_angle   __//
   oid=IntVals[1];
   clock=IntVals[2];
   rest_ticks=IntVals[3];
   time_shift=IntVals[4];

   break;
case 73:
   //__  config_spi_angle   __//
   oid=IntVals[1];
   spi_oid=IntVals[2];
   spi_angle_type=IntVals[3];

   break;
case 74:
   //__  query_mpu9250_status   __//
   oid=IntVals[1];

   break;
case 75:
   //__  query_mpu9250   __//
   oid=IntVals[1];
   rest_ticks=IntVals[2];

   break;
case 76:
   //__  config_mpu9250   __//
   oid=IntVals[1];
   i2c_oid=IntVals[2];

   break;
case 77:
   //__  query_lis2dw_status   __//
   oid=IntVals[1];

   break;
case 78:
   //__  query_lis2dw   __//
   oid=IntVals[1];
   rest_ticks=IntVals[2];

   break;
case 79:
   //__  config_lis2dw   __//
   oid=IntVals[1];
   spi_oid=IntVals[2];

   break;
case 80:
   //__  query_status_ldc1612   __//
   oid=IntVals[1];

   break;
case 81:
   //__  query_ldc1612   __//
   oid=IntVals[1];
   rest_ticks=IntVals[2];

   break;
case 82:
   //__  query_ldc1612_home_state   __//
   oid=IntVals[1];

   break;
case 83:
   //__  ldc1612_setup_home   __//
   oid=IntVals[1];
   clock=IntVals[2];
   threshold=IntVals[3];
   trsync_oid=IntVals[4];
   trigger_reason=IntVals[5];
   error_reason=IntVals[6];

   break;
case 84:
   //__  config_ldc1612_with_intb   __//
   oid=IntVals[1];
   i2c_oid=IntVals[2];
   intb_pin=IntVals[3];

   break;
case 85:
   //__  config_ldc1612   __//
   oid=IntVals[1];
   i2c_oid=IntVals[2];

   break;
case 86:
   //__  query_hx71x_status   __//
   oid=IntVals[1];

   break;
case 87:
   //__  query_hx71x   __//
   oid=IntVals[1];
   rest_ticks=IntVals[2];

   break;
case 88:
   //__  config_hx71x   __//
   oid=IntVals[1];
   gain_channel=IntVals[2];
   dout_pin=IntVals[3];
   sclk_pin=IntVals[4];

   break;
case 89:
   //__  query_ads1220_status   __//
   oid=IntVals[1];

   break;
case 90:
   //__  query_ads1220   __//
   oid=IntVals[1];
   rest_ticks=IntVals[2];

   break;
case 91:
   //__  config_ads1220   __//
   oid=IntVals[1];
   spi_oid=IntVals[2];
   data_ready_pin=IntVals[3];

   break;
case 92:
   //__  reset   __//

   break;
case 93:
   //__  starting   __//

   break;
case 94:
   //__  is_shutdown   __//
   static_string_id=IntVals[1];

   break;
case 95:
   //__  shutdown   __//
   clock=IntVals[1];
   static_string_id=IntVals[2];

   break;
case -32:
   //__  stats   __//
   count=IntVals[1];
   sum=IntVals[2];
   sumsq=IntVals[3];

   break;
case -31:
   //__  uptime   __//
   high=IntVals[1];
   clock=IntVals[2];

   break;
case -30:
   //__  clock   __//
   clock=IntVals[1];

   break;
case -29:
   //__  config   __//
   is_config=IntVals[1];
   crc=IntVals[2];
   is_shutdown=IntVals[3];
   move_count=IntVals[4];

   break;
case -28:
   //__  pong   __//
   data=StrVals[1];

   break;
case -27:
   //__  debug_result   __//
   val=IntVals[1];

   break;
case -26:
   //__  stepper_position   __//
   oid=IntVals[1];
   pos=IntVals[2];

   break;
case -25:
   //__  endstop_state   __//
   oid=IntVals[1];
   homing=IntVals[2];
   next_clock=IntVals[3];
   pin_value=IntVals[4];

   break;
case -24:
   //__  trsync_state   __//
   oid=IntVals[1];
   can_trigger=IntVals[2];
   trigger_reason=IntVals[3];
   clock=IntVals[4];

   break;
case -23:
   //__  analog_in_state   __//
   oid=IntVals[1];
   next_clock=IntVals[2];
   value=IntVals[3];

   break;
case -22:
   //__  spi_transfer_response   __//
   oid=IntVals[1];
   response=StrVals[1];

   break;
case -21:
   //__  i2c_read_response   __//
   oid=IntVals[1];
   response=StrVals[1];

   break;
case -20:
   //__  buttons_state   __//
   oid=IntVals[1];
   ack_count=IntVals[2];
   state=StrVals[1];

   break;
case -19:
   //__  tmcuart_response   __//
   oid=IntVals[1];
   read=StrVals[1];

   break;
case -18:
   //__  neopixel_result   __//
   oid=IntVals[1];
   success=IntVals[2];

   break;
case -17:
   //__  counter_state   __//
   oid=IntVals[1];
   next_clock=IntVals[2];
   count=IntVals[3];
   count_clock=IntVals[4];

   break;
case -16:
   //__  thermocouple_result   __//
   oid=IntVals[1];
   next_clock=IntVals[2];
   value=IntVals[3];
   fault=IntVals[4];

   break;
case -15:
   //__  spi_angle_transfer_response   __//
   oid=IntVals[1];
   clock=IntVals[2];
   response=StrVals[1];

   break;
case -14:
   //__  ldc1612_home_state   __//
   oid=IntVals[1];
   homing=IntVals[2];
   trigger_clock=IntVals[3];

   break;
case -13:
   //__  sensor_bulk_status   __//
   oid=IntVals[1];
   clock=IntVals[2];
   query_ticks=IntVals[3];
   next_sequence=IntVals[4];
   buffered=IntVals[5];
   possible_overflows=IntVals[6];

   break;
case -12:
   //__  sensor_bulk_data   __//
   oid=IntVals[1];
   sequence=IntVals[2];
   data=StrVals[1];

   break;
Int[116]={2,0,0,0,0,1,0,1,0,0,3,2,2,2,3,2,5,2,1,2,2,4,5,1,8,3,2,2,4,1,8,2,2,1,1,4,1,3,1,1,1,4,1,3,3,6,2,5,4,2,1,5,1,2,5,4,3,1,1,6,1,1,8,6,5,6,3,1,2,2,1,4,3,1,2,2,1,2,2,1,2,1,6,3,2,1,2,4,1,2,3,0,0,1,2,3,2,1,4,0,1,2,4,4,3,1,1,2,1,2,4,4,2,3,6,2};
Int[116]={1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,2,1,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,0,0,0,1,0,0,1};
Int[116]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
