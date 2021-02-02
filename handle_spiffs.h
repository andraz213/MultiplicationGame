#ifndef HANDLE_SPIFFS
#define HANDLE_SPIFFS
#include "FS.h"

#include <EEPROM.h>
#include "game_logic.h"

bool init_spiffs();
void save_to_spiffs();
void reset_spiffs();


int get_score();
float get_naucenost_div(int x, int y);
void set_naucenost_div(int x, int y, float val);
float get_naucenost_mult(int x, int y);
void set_naucenost_mult(int x, int y, float val);
void set_score(int val);
void printout_spiffs();
void read_spiffs();
void increase_count_mult(int x, int y);
void increase_count_div(int x, int y);
void add_stat();
void update_time_div(int x, int y, long val);
void update_time_mult(int x, int y, long val);
void normalize_data();


#endif
