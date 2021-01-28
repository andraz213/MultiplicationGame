#include "handle_pins.h"
#include "game_logic.h"
#include <Arduino.h>

bool dz = false;
bool ds = false;
bool lz = false;
bool ls = false;

long prev_ds = 0;
long prev_dz = 0;
long prev_ls = 0;
long prev_lz = 0;


void ICACHE_RAM_ATTR handle_desno_zgoraj(){
  if(millis() - prev_dz > 500 && get_pressed() == -1){
    prev_dz = millis();
    set_pressed(4);
  }
}

void ICACHE_RAM_ATTR handle_desno_spodaj(){
  if(millis() - prev_ds > 500 && get_pressed() == -1){
    prev_ds = millis();
    set_pressed(3);
  }
}

void ICACHE_RAM_ATTR handle_levo_zgoraj(){
  if(millis() - prev_lz > 500 && get_pressed() == -1){
    prev_lz = millis();
    set_pressed(1);
  }
}

void ICACHE_RAM_ATTR handle_levo_spodaj(){
  if(millis() - prev_ls > 500 && get_pressed() == -1){
    prev_ls = millis();
    set_pressed(2);
  }
}




void init_pins(){
  pinMode(GUMB_LEVO_ZGORAJ, INPUT_PULLUP);
  pinMode(GUMB_LEVO_SPODAJ, INPUT_PULLUP);
  pinMode(GUMB_DESNO_ZGORAJ, INPUT_PULLUP);
  pinMode(GUMB_DESNO_SPODAJ, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(GUMB_LEVO_ZGORAJ), handle_levo_zgoraj, FALLING);
  attachInterrupt(digitalPinToInterrupt(GUMB_LEVO_SPODAJ), handle_levo_spodaj, FALLING);
  attachInterrupt(digitalPinToInterrupt(GUMB_DESNO_ZGORAJ), handle_desno_zgoraj, FALLING);
  attachInterrupt(digitalPinToInterrupt(GUMB_DESNO_SPODAJ), handle_desno_spodaj, FALLING);
}


void handle_pins(){
  if(dz){
    Serial.println("dz");
    dz = false;
  }
  if(lz){
    Serial.println("lz");
    lz = false;
  }
  if(ds){
    Serial.println("ds");
    ds = false;
  }
  if(ls){
    Serial.println("ls");
    ls = false;
  }



}
