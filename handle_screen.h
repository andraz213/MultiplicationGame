#ifndef HANDLE_SCREEN
#define HANDLE_SCREEN

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

void show_eqq(int x, int y, int ans1, int ans2, int ans3, int ans4);

void init_screen();

#endif
