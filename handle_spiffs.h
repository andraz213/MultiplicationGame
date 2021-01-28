#ifndef HANDLE_SPIFFS
#define HANDLE_SPIFFS
#include "FS.h"

#include <EEPROM.h>
#include "game_logic.h"

bool init_spiffs();
void save_to_spiffs();
void reset_spiffs();


int get_score_fs();
float get_naucenost_fs(int x, int y);
void set_naucenost_fs(int x, int y, float val);
void set_score_fs(int val);
void printout_spiffs();
void read_spiffs();
void increase_count(int x, int y);
void add_stat();
void update_time_fs(int x, int y, long val);
void normalize_data();


#endif
