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

    FSInfo fs_info;
    SPIFFS.info(fs_info);
    Serial.print("total bytes: ");
    Serial.print(fs_info.totalBytes);
    Serial.print("     used bytes: ");
    Serial.print(fs_info.usedBytes);

  }

  return inited_spiffs;
}


void add_stat(){
  if(get_score() % 100 == 0){
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
        //Serial.print(a);
        temp[i] = a;
        //Serial.print(temp[i]);
        //Serial.print(" ");
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
  SPIFFS.format();
  for(int i = 0; i<10; i++){
    for(int j = 0; j<10; j++){
      si_spiffs.naucenost_mult[i][j] = (float) 0.0;//random(100);// (10 - i)*(10-j);//random(100);
      si_spiffs.count_mult[i][j] = 0;
      si_spiffs.time_mult[i][j] = 0.0;

      si_spiffs.naucenost_div[i][j] = (float) 0.0;//random(100);// (10 - i)*(10-j);//random(100);
      si_spiffs.count_div[i][j] = 0;
      si_spiffs.time_div[i][j] = 0.0;
    }
  }
  si_spiffs.score = 0;

  save_to_spiffs();
}


int get_score(){

  return si_spiffs.score;
}

void set_score(int val){
  si_spiffs.score = val;

}
float get_naucenost_mult(int x, int y){
  return si_spiffs.naucenost_mult[x][y];
}
void set_naucenost_mult(int x, int y, float val){
  si_spiffs.naucenost_mult[x][y] = val;
}

float get_naucenost_div(int x, int y){
  return si_spiffs.naucenost_div[x][y];
}
void set_naucenost_div(int x, int y, float val){
  si_spiffs.naucenost_div[x][y] = val;
}











void printout_spiffs(){
  init_spiffs();

  for(int i = 0; i<10; i++){
    for(int j = 0; j<10; j++){
      Serial.println();
      String prt = String(i+1) + " * " + String(j+1) + ": " + String(si_spiffs.naucenost_mult[i][j]) + ", " + String(si_spiffs.count_mult[i][j]) + ", " + String(si_spiffs.time_mult[i][j]);
      Serial.println(prt);
       prt = String((i+1) * (j+1)) + " : " + String(i+1) + ": " + String(si_spiffs.naucenost_div[i][j]) + ", " + String(si_spiffs.count_div[i][j]) + ", " + String(si_spiffs.time_div[i][j]);
      Serial.println(prt);
    }
  }

}

void update_time_div(int x, int y, long val){
  if(val < 30000){
    if(si_spiffs.time_div[x][y] < 50.0){
      si_spiffs.time_div[x][y] = val;
    }
    si_spiffs.time_div[x][y] *= 0.90;
    si_spiffs.time_div[x][y] += ((float) val)*0.10;
  }
}


void update_time_mult(int x, int y, long val){
  if(val < 30000){
    if(si_spiffs.time_mult[x][y] < 50.0){
      si_spiffs.time_mult[x][y] = val;
    }
    si_spiffs.time_mult[x][y] *= 0.90;
    si_spiffs.time_mult[x][y] += ((float) val)*0.10;
  }
}

void increase_count_mult(int x, int y){
  si_spiffs.count_mult[x][y] += 1;
}

void increase_count_div(int x, int y){
  si_spiffs.count_div[x][y] += 1;
}

void normalize_data(){
  if(init_spiffs()){
    float min_nauc = si_spiffs.naucenost_mult[4][4];

    for(int j = 0; j<10; j++){
      for(int i = 0; i<10; i++){
        if(si_spiffs.naucenost_mult[j][i] < min_nauc){
          min_nauc = si_spiffs.naucenost_mult[j][i];
        }
        if(si_spiffs.naucenost_div[j][i] < min_nauc){
          min_nauc = si_spiffs.naucenost_div[j][i];
        }
      }
    }

    for(int j = 0; j<10; j++){
      for(int i = 0; i<10; i++){
        if(si_spiffs.naucenost_mult[j][i] != 0.0){
          si_spiffs.naucenost_mult[j][i] -= min_nauc;
        }
        if(si_spiffs.naucenost_div[j][i] != 0.0){
          si_spiffs.naucenost_div[j][i] -= min_nauc;
        }
      }
    }
    save_to_spiffs();
  }

}
