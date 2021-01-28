#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H
#include "handle_spiffs.h"


typedef struct Stanjeigre {
  float naucenost[10][10];
  float time[10][10];
  int count[10][10];
  int score;
};

typedef struct DataList {
  float naucenost;
  int x;
  int y;
  void * next;
};


void init_game();
void get_next();
int get_max(DataList ** arr);
void next_move();
int display_next();
int get_displayed_num(int mode);
void update_list();
void calculate_res();
int get_pressed();
void set_pressed(int p);
float get_min_val();
#endif
