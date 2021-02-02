#include "game_functions.h"



float calc_naucenost(long answer_time){
  float points = 1.0;
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
  return points;
}



int get_displayed_num(int mode, DataList next){
    int res = 0;
  if(next.multiplication){

  switch(mode){
    case 0:
      res = (next.x + 1)*(next.y + 1);
      break;
    case 1:
      res = ((next.x + 1)%10 +1)*(next.y + 1);
      break;
    case 2:
      res = (next.x + 1)*((next.y + 1)%10 +1);
      break;
    case 3:
      res = (next.x + 1)*((next.y - 1 + 10)%10 +1);
      break;
    case 4:
      res = ((next.x - 1 + 10)%10 +1) * (next.y + 1);
      break;
    case 5:
      res = (next.x + 1)*(next.y + 1) - 5 + random(10);
    break;
    case 6:
      res = random(100);
    break;
    case 7:
      res = (next.x + 1)*(next.y + 1) - 3 + random(7);
    break;
    case 8:
      res = ((next.x + 1)%10 +1)*(next.y + 1) - 3 + random(7);
    break;
    case 9:
      res = ((next.x - 1 + 10)%10 +1)*(next.y + 1) - 3 + random(7);
    break;
  }


  if(res == (next.x + 1)*(next.y + 1) && mode != 0 || res < 0 || res > 100){
    res = random(100);
  }
}else{
  int y = (next.y + 1);
  switch(mode){
    case 0:
      res = y;
      break;
    case 1:
      if(y - 1 > -1){
        res = y -1;
      }
      break;
    case 2:
    if(y - 2 > -1){
      res = y -2;
    }
      break;
    case 3:
    if(y - 3 > -1){
      res = y -3;
    }
      break;
    case 4:
    if(y + 1 < 11){
      res = y + 1;
    }
      break;
    case 5:
    if(y + 2 < 11){
      res = y + 2;
    }
    break;
    case 6:
    if(y + 3 < 11){
      res = y + 3;
    }
    break;
    case 7:
    if(y - 1 > -1){
      res = y -1;
    }
    break;
    case 8:
    if(y + 1 < 11){
      res = y + 1;
    }
    break;
    case 9:
    if(y + 2 < 11){
      res = y + 2;
    }
    break;
  }

}
  return res;
}
