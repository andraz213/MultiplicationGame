#include "game_logic.h"
#include "handle_screen.h"
#include "handle_neopix.h"
#include <Arduino.h>
#include "game_functions.h"

//                  1      2      3      4      5      6      7      8      9      10
bool enabled[10] = {false, true,  false, true,  true,  false, false, false, false, true};


DataList list[200];
DataList *first;

DataList *next;
long started_move = 0;
int answer = -1;
int pressed = -1;
int n_enabled = 0;

void init_game(){
  n_enabled = 0;
  for(int i = 0; i<10; i++){
    if(enabled[i]){
      n_enabled += 1;
    }
  }

  int iter = 0;
  first = &list[0];
  for(int i = 0; i<10; i++){
    if(enabled[i]){
      for(int j = 0; j<10; j++){
        if(iter > 0){
          list[iter-1].next = &list[iter];
        }
        list[iter].next = 0;
        list[iter].multiplication = true;
        list[iter].x = i;
        list[iter].y = j;
        list[iter].naucenost = get_naucenost_mult(i, j);

        iter++;
      }
    }
  }

  for(int i = 0; i<10; i++){
    if(enabled[i]){
      for(int j = 0; j<10; j++){
        if(iter > 0){
          list[iter-1].next = &list[iter];
        }
        list[iter].next = 0;
        list[iter].multiplication = false;
        list[iter].x = i;
        list[iter].y = j;
        list[iter].naucenost = get_naucenost_div(i, j);

        iter++;
      }
    }
  }
}



void get_next(){
  DataList *arr[20];
  int n = 0;
  float max = get_min_val();

  DataList *iter = (DataList*)first;

  while(n < 20 && iter != 0){
    arr[n] = iter;
    iter = (DataList*)iter->next;
    n++;

  }

  max = arr[get_max(arr)]->naucenost;

  while(iter != 0){
    if(iter->naucenost <= max){
      int pt = get_max(arr);
      arr[pt] = iter;
      max = arr[get_max(arr)]->naucenost;
    }
    iter = (DataList*)iter->next;
  }

  int r = random(20);

  Serial.println(arr[r]->naucenost);
  Serial.println(arr[r]->x);
  Serial.println(arr[r]->y);
  Serial.println();

  next = arr[r];

}


void next_move(){
  get_next();


  answer = display_next();
  started_move = millis();
  pressed = -1;

}



void calculate_res(){
  if(pressed != -1){
    long answer_time = millis() - started_move;
    if(pressed == answer){

      add_stat();
      correct_neo();

      Serial.println("BRAVO");
      float points = calc_naucenost(answer_time);

      update_time_nauc(points, answer_time);

      update_points(points);

      set_score(get_score() + 1);

      save_to_spiffs();

      update_list();
      next_move();
    } else {

      if(next->multiplication){
        set_naucenost_mult(next->x, next->y, next->naucenost - 0.5);
      }else{
        set_naucenost_div(next->x, next->y, next->naucenost - 0.5);
      }
      set_score(get_score() - 1);
      save_to_spiffs();

      update_list();
      answer = display_next();
      wrong_neo();

      pressed = -1;
    }


  }
}

void update_list(){
  DataList*iter = first;

  while(iter != 0){
    if(iter->multiplication){
      iter->naucenost = get_naucenost_mult(iter->x, iter->y);
    }else{
      iter->naucenost = get_naucenost_div(iter->x, iter->y);
    }

    iter = (DataList*)iter->next;
  }



}


int display_next(){

  int opcije[4] = {-1, -1, -1, -1};
  int res = random(100)%4;

  opcije[res] = 0;

  for(int i = 0; i<4; i++){

    while(opcije[i] < 0){
      int op = (random(1000)%9) +1;
      bool ok = true;
      for(int j = 0; j<i; j++){
        if(opcije[j] == op){
          ok = false;
        }
      }

      if(ok){
        opcije[i] = op;
      }
    }
  }

  Serial.println("hej okej");
  Serial.println(next->multiplication);
  int x = (next->x + 1);
  int y = (next->y + 1);
  DataList temp;
  memcpy(&temp, next, sizeof(DataList));
  int ans1 = get_displayed_num(opcije[0], temp);
  int ans2 = get_displayed_num(opcije[1], temp);
  int ans3 = get_displayed_num(opcije[2], temp);
  int ans4 = get_displayed_num(opcije[3], temp);
  if(next->multiplication){
    show_eqq_mult(x, y, ans1, ans2, ans3, ans4);
  }else{
    int res_res = x*y;
    show_eqq_div(res_res, x, ans1, ans2, ans3, ans4);
  }


  return res+1;
}





int get_max(DataList ** arr){
  float max = get_min_val();
  int res = 0;

  for(int i = 0; i<20; i++){
    if(arr[i]->naucenost > max){
      max = arr[i]->naucenost;
      res = i;
    }

  }
  return res;
}


float get_min_val(){
  float res = 10000.0;


  DataList*iter = first;

  while(iter != 0){
    if(iter->naucenost < res){
      res = iter->naucenost;
    }
    iter = (DataList*)iter->next;
  }
  return res;
}



int get_pressed(){
  return pressed;
}

void set_pressed(int p){
  pressed = p;
}


void update_time_nauc(float points, long answer_time){
  if(next->multiplication){
    update_time_mult(next->x, next->y, answer_time);
    set_naucenost_mult(next->x, next->y, next->naucenost + points);
    increase_count_mult(next->x, next->y);
  } else {
    update_time_div(next->x, next->y, answer_time);
    set_naucenost_div(next->x, next->y, next->naucenost + points);
    increase_count_div(next->x, next->y);
  }
}

void update_points(float points){
  float points_upd = points;
  points_upd *= 0.1;
  points_upd /= (float)(n_enabled * 4);
  DataList*iter = first;

  while(iter != 0){
    if(iter != next){
      if(iter->multiplication){
        set_naucenost_mult(iter->x, iter->y, iter->naucenost - points_upd);
      }else{
        set_naucenost_div(iter->x, iter->y, iter->naucenost - points_upd);
      }
      Serial.println(iter->naucenost);
    }
    iter = (DataList*)iter->next;
  }
}
