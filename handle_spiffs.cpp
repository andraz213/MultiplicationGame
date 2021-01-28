#include "handle_spiffs.h"
#include <Arduino.h>
Stanjeigre si_spiffs;


bool inited_spiffs = false;

bool init_spiffs(){
  if(!inited_spiffs){
    inited_spiffs = SPIFFS.begin();
    if(inited_spiffs){
      read_spiffs();
    }
  }

  return inited_spiffs;
}


void add_stat(){
  if(get_score_fs() % 100 == 0){
    File fileToAppend = SPIFFS.open("/stat.conf", "a");
    if(fileToAppend){
      unsigned char * data = reinterpret_cast<unsigned char*>(&si_spiffs); // use unsigned char, as uint8_t is not guarunteed to be same width as char...
      size_t bytes = fileToAppend.write((char * )&si_spiffs, sizeof(Stanjeigre)); // C++ way

      Serial.printf("END Position =%u \n", fileToAppend.position());
      fileToAppend.close();
    }
  }
}

void read_spiffs(){
  if (init_spiffs()) {
    inited_spiffs = true;
    File f = SPIFFS.open("gamedata.conf", "r");
    if(f){

      uint8_t * temp = (uint8_t * ) &si_spiffs;

      for(int i = 0; i< sizeof(Stanjeigre); i++){
        char a = f.read();
        Serial.print(a);
        temp[i] = a;
        Serial.print(temp[i]);
        Serial.print(" ");
      }
      f.close();
    }
  }


}

void save_to_spiffs(){
  if(init_spiffs()){
    File f = SPIFFS.open("gamedata.conf", "w+");

    if(f){
      Serial.printf("START Position =%u \n", f.position());
      unsigned char * data = reinterpret_cast<unsigned char*>(&si_spiffs); // use unsigned char, as uint8_t is not guarunteed to be same width as char...
      size_t bytes = f.write((char * )&si_spiffs, sizeof(Stanjeigre)); // C++ way

      Serial.printf("END Position =%u \n", f.position());
      f.close();
    }


  }


}
void reset_spiffs(){
  for(int i = 0; i<10; i++){
    for(int j = 0; j<10; j++){
      si_spiffs.naucenost[i][j] = (float) 0.0;//random(100);// (10 - i)*(10-j);//random(100);
      si_spiffs.count[i][j] = 0;
      si_spiffs.time[i][j] = 0.0;
    }
  }
  si_spiffs.score = 2410;

  save_to_spiffs();
}


int get_score_fs(){

  return si_spiffs.score;
}
float get_naucenost_fs(int x, int y){
  return si_spiffs.naucenost[x][y];
}
void set_naucenost_fs(int x, int y, float val){
  si_spiffs.naucenost[x][y] = val;
}
void set_score_fs(int val){
  si_spiffs.score = val;

}
void printout_spiffs(){
  init_spiffs();

  for(int i = 0; i<10; i++){
    for(int j = 0; j<10; j++){
      Serial.println();
      String prt = String(i+1) + " * " + String(j+1) + ": " + String(si_spiffs.naucenost[i][j]) + ", " + String(si_spiffs.count[i][j]) + ", " + String(si_spiffs.time[i][j]);
      Serial.println(prt);
    }
  }

}

void update_time_fs(int x, int y, long val){
  if(si_spiffs.time[x][y] < 50.0){
    si_spiffs.time[x][y] = val;
  }
  si_spiffs.time[x][y] *= 0.90;
  si_spiffs.time[x][y] += ((float) val)*0.10;
}

void increase_count(int x, int y){
  si_spiffs.count[x][y] += 1;
}
