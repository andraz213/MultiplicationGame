#include "handle_eeprom.h"
#include <Arduino.h>
Stanjeigre si;


void init_eeprom(){
  EEPROM.begin(sizeof(Stanjeigre));
  EEPROM.get(0, si);
  EEPROM.end();
}

void save_to_eeprom(){

  EEPROM.begin(sizeof(Stanjeigre));
  EEPROM.put(0, si);
  EEPROM.commit();
  EEPROM.end();

}

void printout_eeprom(){
  init_eeprom();

  for(int i = 0; i<10; i++){
    for(int j = 0; j<10; j++){
      Serial.println();
      String prt = String(i+1) + " * " + String(j+1) + ": " + String(si.naucenost[i][j]);
      Serial.println(prt);
    }
  }


}


void reset_eeprom(){
  for(int i = 0; i<10; i++){
    for(int j = 0; j<10; j++){
      si.naucenost[i][j] = (float)0.0;//random(100);// (10 - i)*(10-j);//random(100);
    }
  }
  //si.score = 0;

  save_to_eeprom();

}


float get_naucenost(int x, int y){
  return si.naucenost[x][y];
}

void set_naucenost(int x, int y, float val){
  si.naucenost[x][y] = val;
  //save_to_eeprom();
}

int get_score(){
  return si.score;
}

void set_score(int val){
  si.score = val;
}
