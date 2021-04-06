
#include "handle_pins.h"
#include "game_logic.h"
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
    init_neo();
    init_spiffs();


  reset_routine();
  printout_routine();

  normalize_data();
  printout_spiffs();

  init_pins();
  init_screen();

  init_game();
  next_move();



}

void loop() {
  // put your main code here, to run repeatedly:

  //show_eqq(5, 7, 32, 14, 35, 22);

  calculate_res();
  updat_pix();
  delay(16);

}


void printout_routine(){
pinMode(GUMB_DESNO_ZGORAJ, INPUT_PULLUP);
    if(digitalRead(GUMB_DESNO_ZGORAJ) == LOW){
        printout_stat_new();
    }
}

void reset_routine(){
  pinMode(GUMB_LEVO_SPODAJ, INPUT_PULLUP);
  pinMode(GUMB_DESNO_SPODAJ, INPUT_PULLUP);
  if(digitalRead(GUMB_LEVO_SPODAJ) == LOW && digitalRead(GUMB_DESNO_SPODAJ) == LOW){
    long start = millis();
    resetting_pix();
    while(digitalRead(GUMB_LEVO_SPODAJ) == LOW && digitalRead(GUMB_DESNO_SPODAJ) == LOW && millis() - start < 4000){
      delay(100);
    }
    if(digitalRead(GUMB_LEVO_SPODAJ) == LOW && digitalRead(GUMB_DESNO_SPODAJ) == LOW){
      reset_spiffs();
      correct_neo();
    }
  }
}
