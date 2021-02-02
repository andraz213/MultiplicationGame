#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H
#include "handle_spiffs.h"



typedef struct Stanjeigre {
  float naucenost_mult[10][10];
  float time_mult[10][10];
  int count_mult[10][10];
  float naucenost_div[10][10];
  float time_div[10][10];
  int count_div[10][10];
  int score;
};

typedef struct DataList {
  float naucenost;
  bool multiplication;
  int x;
  int y;
  void * next;
};


void init_game();
void get_next();
int get_max(DataList ** arr);
void next_move();
int display_next();
void update_list();
void calculate_res();
int get_pressed();
void set_pressed(int p);
float get_min_val();
void update_points(float points);
void update_time_nauc(float points, long answer_time);

#endif
