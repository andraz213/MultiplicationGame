
#include "handle_pins.h"
#include "game_logic.h"
#include "handle_eeprom.h"
#include "handle_screen.h"
#include "handle_neopix.h"
#include <ESP8266WiFi.h>
#include "handle_spiffs.h"

void setup() {
  // put your setup code here, to run once:
  WiFi.mode(WIFI_OFF);
wifi_fpm_set_sleep_type (LIGHT_SLEEP_T);
WiFi.forceSleepBegin();   // if you dont need wifi, ~22ma instead of ~75ma

  Serial.begin(115200);

  init_spiffs();
  printout_spiffs();
  //reset_spiffs();

  init_screen();
  init_pins();
  //reset_eeprom();
  init_game();
  next_move();
  init_neo();

}

void loop() {
  // put your main code here, to run repeatedly:

  //show_eqq(5, 7, 32, 14, 35, 22);

  calculate_res();
  updat_pix();
  delay(16);

}
