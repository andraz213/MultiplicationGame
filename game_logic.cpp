#include "game_logic.h"
#include "handle_screen.h"
#include "handle_neopix.h"
#include <Arduino.h>
//                  1     2     3     4     5     6     7      8     9     10
bool enabled[10] = {false, true, false, true, true, false, false, false, false, true};


DataList list[100];
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

        list[iter].x = i;
        list[iter].y = j;
        list[iter].naucenost = get_naucenost_fs(i, j);

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
      update_time_fs(next->x, next->y, answer_time);
      add_stat();
      correct_neo();
      float points = 1.0;
      Serial.println("BRAVO");
      if(answer_time < 3000){
        float add =  3.0;
        add *= 3000.0 - answer_time;
        add /= 3000.0;
        add *= 3000.0 - answer_time;
        add /= 3000.0;
        points += add;

      }
      if(answer_time > 3000){
        points -= ((float)(answer_time - 3000)) / 20000.0;
      }
      if(answer_time > 23000){
        points = 0.0;
      }
      set_naucenost_fs(next->x, next->y, next->naucenost + points);
      increase_count(next->x, next->y);
      points *= 0.1;
      points /= (float)n_enabled;
      DataList*iter = first;

      while(iter != 0){
        if(iter != next){
          set_naucenost_fs(iter->x, iter->y, iter->naucenost - points);
          Serial.println(iter->naucenost);
        }
        iter = (DataList*)iter->next;
      }

      set_score_fs(get_score_fs() + 1);
      save_to_spiffs();

      update_list();
      next_move();
    } else {
      set_naucenost_fs(next->x, next->y, next->naucenost - 0.5);
      set_score_fs(get_score_fs() - 1);
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
    iter->naucenost = get_naucenost_fs(iter->x, iter->y);
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

  int x = (next->x + 1);
  int y = (next->y + 1);
  int ans1 = get_displayed_num(opcije[0]);
  int ans2 = get_displayed_num(opcije[1]);
  int ans3 = get_displayed_num(opcije[2]);
  int ans4 = get_displayed_num(opcije[3]);

  show_eqq(x, y, ans1, ans2, ans3,ans4);

  return res+1;
}

int get_displayed_num(int mode){
  int res = 0;
  switch(mode){
    case 0:
      res = (next->x + 1)*(next->y + 1);
      break;
    case 1:
      res = ((next->x + 1)%10 +1)*(next->y + 1);
      break;
    case 2:
      res = (next->x + 1)*((next->y + 1)%10 +1);
      break;
    case 3:
      res = (next->x + 1)*((next->y - 1 + 10)%10 +1);
      break;
    case 4:
      res = ((next->x - 1 + 10)%10 +1) * (next->y + 1);
      break;
    case 5:
      res = (next->x + 1)*(next->y + 1) - 5 + random(10);
    break;
    case 6:
      res = random(100);
    break;
    case 7:
      res = (next->x + 1)*(next->y + 1) - 3 + random(7);
    break;
    case 8:
      res = ((next->x + 1)%10 +1)*(next->y + 1) - 3 + random(7);
    break;
    case 9:
      res = ((next->x - 1 + 10)%10 +1)*(next->y + 1) - 3 + random(7);
    break;
  }


  if(res == (next->x + 1)*(next->y + 1) && mode != 0 || res < 0 || res > 100){
    res = random(100);
  }
  return res;
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
